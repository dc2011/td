#include "manager.h"
#include "../network/netclient.h"

namespace td {

AudioManager* AudioManager::instance_ = NULL;
QMutex AudioManager::mutex_;
bool AudioManager::capturePause_ = true;
bool AudioManager::captureStop_ = false;
QMap<QString,QByteArray> AudioManager::sfxCache_;
QQueue<Stream *> AudioManager::netQueue_;
float AudioManager::gainScale[] = {0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 
                                   0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0};

AudioManager::AudioManager()
{
    sfxGain_ = 9;
    musicGain_ = 5;
    notiGain_ = 12;
    voiceGain_ = 10;
}

AudioManager::~AudioManager()
{
    AudioManager::shutdown();
}

void AudioManager::shutdown()
{
    if (inited_) {
        inited_ = false;
        alExit();
    }
}

void AudioManager::startup()
{
    if(!inited_) {
	alInit();
	initSpeex();
	inited_ = true;
	playing_ = 0;
	
	QtConcurrent::run(this, &AudioManager::streamVoice);
	QtConcurrent::run(this, &AudioManager::captureMic);
    }
}

void AudioManager::initSpeex() {
    speex_.sampleRate = 8000; 
    speex_.quality = 4;

    speex_bits_init(&speex_.bits);

    speex_.encState = speex_encoder_init(&speex_nb_mode);
    speex_.decState = speex_decoder_init(&speex_nb_mode);

    speex_encoder_ctl(speex_.encState,
            SPEEX_GET_FRAME_SIZE, &speex_.frameSize);
    speex_encoder_ctl(speex_.encState,
            SPEEX_SET_SAMPLING_RATE, &speex_.sampleRate);
    speex_encoder_ctl(speex_.encState,
            SPEEX_SET_QUALITY, &speex_.quality);
}

void AudioManager::startCapture()
{
    QFuture<void> future =
        QtConcurrent::run(this, &AudioManager::captureMic);
}

void AudioManager::playSfx(QStringList files, SoundType type) {
    
    int rdNum;
    
    if(files.size() < 1) {
        qCritical("AudioManager::playSfx(): Empty Vector");
        return;
    }
    
    rdNum = rand() % files.size();
    playSfx(files[rdNum],type);
}

void AudioManager::playSfx(QString filename, SoundType type)
{

    filename = SFXPATH + filename + SFXFILEEXTENSION;
    
    if(playing_ >= 55) { return;}

    if(sfxCache_.contains(filename)) {
        QFuture<void> future =
            QtConcurrent::run(this, &AudioManager::playCached,
                              filename, type);
    } else {
 
        QFuture<void> future =
            QtConcurrent::run(this, &AudioManager::streamFile,
                              filename, type, true);
    }

    return;

}

void AudioManager::captureMic()
{
    ALCdevice* captureDevice;
    ALint samplesAvailable;
    ALint format, frequency;

    format = AL_FORMAT_MONO16;
    frequency = 8000;

    ALCsizei buffersize = frequency * 2 * 4; /* 2 for 16-bit, 4 for time */
    captureDevice = alcCaptureOpenDevice(NULL, frequency, format, buffersize);

    if (captureDevice) {
        alcCaptureStart(captureDevice);

        while(!checkError()) {
            alcGetIntegerv(captureDevice, ALC_CAPTURE_SAMPLES,
                    1, &samplesAvailable);

            while(capturePause_ == true && captureStop_ == false 
                  && !checkError()) {
                alSleep(0.1f);
            }

            if(captureStop_ == true) {
                break;
            } else if (samplesAvailable > (speex_.frameSize * 5)) {
                int nframes = (int)(samplesAvailable / speex_.frameSize);
                int total = nframes * speex_.frameSize;

                short* buf = new short[total];
                alcCaptureSamples(captureDevice, buf, total);

                Stream s;
                int numframes = total / speex_.frameSize;

                encode(buf, numframes, &s);
                
                NetworkClient::instance()->send(
                        network::kVoiceMessage, s.data());
            }
        }
    }

    alcCaptureCloseDevice(captureDevice);
}

QQueue<QString> AudioManager::musicDir(QString dir)
{
    int i;
    int iter;
    QDir mDir(dir);
    mDir.setFilter(QDir::Files);
    QList<QString> musicList = mDir.entryList();
    QQueue<QString> musicQueue;

    if (musicList.length() == 0) {
        qCritical("AudioManager::musicDir(): No Files or Directory");
        return musicQueue;
    }

    iter = rand() % musicList.length();

    for (i = 0; i < musicList.length(); i++) {
        if (++iter >= musicList.length()) {
            iter = 0;
        }

        musicQueue.enqueue(dir + musicList[iter]);
    }

    return musicQueue;
}

void AudioManager::playMusic(QQueue<QString> filenameQueue)
{
    QFuture<void> future =
        QtConcurrent::run(this, &AudioManager::playMusicQueue, filenameQueue);
    return;
}

bool AudioManager::checkError()
{
    ALuint error = alGetError();
    const ALchar* err = alGetString(error);

    if (inited_ == false) {
        return true;
    } else if (error != AL_NO_ERROR) {
        qCritical("AudioManager::checkError(): %d:%s", error, err);
        alExit();
        inited_=false;
        return true;
    }

    return false;
}

void AudioManager::playMusicQueue(QQueue<QString> filenameQueue)
{
    QString filename;

    while (!filenameQueue.empty() && inited_) {
        filename = filenameQueue.dequeue();
        AudioManager::streamFile(filename, msk);
        /*Sleep for 0.3 sec so playback doesn't overlap*/
        alSleep(0.3f);

        if (errno != ENOENT) {
            filenameQueue.enqueue(filename);
        }

        errno = 0;
    }
}


void AudioManager::streamVoice()
{
    short *buf;
    int buffersize=0;
    Stream *temp;
    int frames;
    int buffersAvailable = QUEUESIZE;
    long size = 0;
    long result = 0;
    ALuint buffer[QUEUESIZE];
    ALuint source;
    ALint queued = 0;
    ALint queue = 0;
    ALint play = AL_TRUE;
    ALint playing = AL_TRUE;
    ALenum format = AL_FORMAT_MONO16;
    ALuint freq = 8000;


    /* Created the source and Buffers */
    alGenBuffers(QUEUESIZE, buffer);
    alGenSources(1, &source);

    do {

        alSourcef(source, AL_GAIN, gainScale[voiceGain_]);
        clearProcessedBuffers(&source, buffersAvailable, &playing, &play);

        if (buffersAvailable > 0) {
            size = 0;
                      
            while(getQueueSize() < 1 && !checkError()) {
                alSleep(0.1f);
            }

            if(checkError()) {
                break;
            }

            temp = getNextInQueue();
            frames = temp->readInt();
            buffersize = frames*speex_.frameSize;
            buf = new short[buffersize];
            decode(temp, frames, buf); 
            result = buffersize*sizeof(short);

            if (result == 0) {
                break;
            }

            size += result;

            if (result < 0) {
                qCritical() << "AudioManager::streamFile(): Read Failed ";
                break;
            }

            alBufferData(buffer[queue], format, buf, size, freq);
            alSourceQueueBuffers(source, 1, &buffer[queue]);
            queue = (++queue == QUEUESIZE ? 0 : queue);
            buffersAvailable--;

            /**Check the amount of buffers queued to see if
             * we should be playing the track right now.
             * If play is false it means it's playing already
             */
            alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);

            if(queued > 1 && play) {
                alSourcePlay(source);
                play = AL_FALSE;
            }
        } else {
            alSleep(0.1f);
        }

/* result == 0 when file is completely read */
    } while (result > 0 && !checkError());

    cleanUp(&source, buffer);

}

void AudioManager::playCached(QString filename, SoundType sType)
{
    ALuint buffer;
    ALuint tmpBuffer;
    ALuint source;
    ALenum format;
    ALuint freq;
    QByteArray tmp;
    ALint playing;
    int gain;
    int processed;

    alGenBuffers(1,&buffer);
    alGenSources(1,&source);

    if(sType == sfx) {
        gain = sfxGain_ - (playing_ / 2);
        if (gain < 0) { gain = 0;}
    } else if(sType == ntf) {
        gain = notiGain_;
    } else {
        gain = musicGain_ - (playing_ / 8);
        if (gain < 0) { gain = 0;}
    }

    SAFE_OPERATION(playing_++);

    mutex_.lock();
    tmp = sfxCache_[filename];
    mutex_.unlock();

    getSpecs(tmp.at(0),&format,&freq);
    alBufferData(buffer, format, tmp.mid(1).constData(), tmp.size()-1, freq);
    alSourceQueueBuffers(source, 1, &buffer);

    alSourcePlay(source);

    do {
        alSourcef(source, AL_GAIN, gainScale[gain]);
        alGetSourcei(source, AL_SOURCE_STATE, &playing);
        alSleep(0.1f);
    } while(playing != AL_STOPPED && !checkError());

    alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

    while (processed && !checkError()) {
	alSourceUnqueueBuffers(source, 1, &tmpBuffer);
        processed--;
    }

    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    SAFE_OPERATION(playing_--);
}

void AudioManager::streamFile(QString filename, SoundType sType, bool cacheThis)
{
    FILE* file;
    char array[BUFFERSIZE];
    int bitStream;
    int buffersAvailable = QUEUESIZE;
    long size = 0;
    long result = 0;
    ALuint buffer[QUEUESIZE];
    ALuint source;
    ALint queued = 0;
    ALint queue = 0;
    ALint play = AL_TRUE;
    ALint playing = AL_TRUE;
    ALenum format;
    ALsizei freq = 44100;
    OggVorbis_File oggFile;
    char bitmask;
    int gain;

    /* Created the source and Buffers */
    alGenBuffers(QUEUESIZE, buffer);
    alGenSources(1, &source);
    SAFE_OPERATION(playing_++);

    if ((file = fopen(filename.toAscii().constData(), "rb")) == NULL) {
        qCritical() << "AudioManager::streamFile(): Cannot open " 
                    << filename << " for reading...";
        return;
    }

    openOgg(file, &oggFile, &format, &freq);

    do {

        clearProcessedBuffers(&source, buffersAvailable, &playing, &play);

        if(sType == sfx) {
            gain = sfxGain_ - (playing_ / 2);
            if (gain < 0) { gain = 0;}
        } else if(sType == ntf) {
            gain = notiGain_;
        } else {
            gain = musicGain_ - (playing_ / 8);
            if (gain < 0) { gain = 0;}
        }

        alSourcef(source, AL_GAIN, gainScale[gain]);
        
        if (buffersAvailable > 0) {
            size = 0;
            /* Read file to we reached a BUFFERSIZE chunk */
            while (size < BUFFERSIZE) {
                result = ov_read(&oggFile, array + size,
                        BUFFERSIZE - size, 0, 2, 1, &bitStream);

                if (result == 0) {
                    break;
                }

                size += result;

                if (result < 0) {
                    qCritical() << "AudioManager::streamFile(): Ogg Read Failed "
                                                                << endl;
                    break;
                }
            }

            if(cacheThis) {
                bitmask = getBitmask(format,freq);
                cacheBuffer(filename,array,size,bitmask);
            }

            alBufferData(buffer[queue], format, array, size, freq);
            alSourceQueueBuffers(source, 1, &buffer[queue]);
            queue = (++queue == QUEUESIZE ? 0 : queue);
            buffersAvailable--;
            /**Check the amount of buffers queued to see if
             * we should be playing the track right now.
             * If play is false it means it's playing already
             */
            alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);

            if ((queued > 2 || result == 0) && play) {
                alSourcePlay(source);
                play = AL_FALSE;
            }
        } else {
            alSleep(0.1f);
        }

        /* result == 0 when file is completely read */
    } while (result > 0 && !checkError());

    ov_clear(&oggFile);

    cleanUp(&source, buffer);
    SAFE_OPERATION(playing_--);
}

void AudioManager::cleanUp(ALuint *source, ALuint *buffer)
{
    ALint processed;
    ALuint tempBuffer;
    ALint playing;

    do {
        alGetSourcei(*source, AL_SOURCE_STATE, &playing);
        alSleep(0.1f);
    } while (playing != AL_STOPPED && !checkError());

    alGetSourcei(*source, AL_BUFFERS_PROCESSED, &processed);

    while (processed && !checkError()) {
        alSourceUnqueueBuffers(*source, 1, &tempBuffer);
        processed--;
    }

    alDeleteSources(1, source);
    alDeleteBuffers(QUEUESIZE, buffer);
}

void AudioManager::clearProcessedBuffers
(ALuint *source, int &buffersAvailable, ALint *playing, ALint* play)
{
    ALint processed;
    ALuint tempBuffer;

    alGetSourcei(*source, AL_BUFFERS_PROCESSED, &processed);

    while (processed && !checkError()) {
        alSourceUnqueueBuffers(*source, 1, &tempBuffer);
        processed--;

        /* ensures buffers don't get larger than QUEUESIZE */
        if (buffersAvailable < QUEUESIZE - 1) {
            buffersAvailable++;
        }

        /* Restarts playing if buffer emptied too quickly */
        alGetSourcei(*source, AL_SOURCE_STATE, playing);

        if (*playing == AL_STOPPED) {
            *play = AL_TRUE;
        }
    }
}

void AudioManager::openOgg(FILE *file, OggVorbis_File *oggFile, 
                           ALenum *format, ALsizei *freq)
{
    vorbis_info* vorbisInfo;
    if (ov_open(file, oggFile, NULL, 0) != 0) {
        qCritical() << "AudioManager::openOgg(): Error opening file for decoding...";
        return;
    }

    vorbisInfo = ov_info(oggFile, -1);

    if(vorbisInfo->channels == 1) {
        *format = AL_FORMAT_MONO16;
    }
    else {
        *format = AL_FORMAT_STEREO16;
    }

    *freq = vorbisInfo->rate;
}

void AudioManager::getSpecs(char bitmask, ALenum *format, ALuint *freq) {
    if(bitmask & 0x10) {
        *freq = 22050;
    } else if (bitmask & 0x20) {
        *freq = 44100;
    } else if (bitmask & 0x40) {
        *freq = 48000;
    }

    bitmask &= 0xF;

    if (bitmask == 0x5) {
        *format = AL_FORMAT_MONO8;
    } else if (bitmask == 0x6) {
        *format = AL_FORMAT_MONO16;
    } else if (bitmask == 0x9) {
        *format = AL_FORMAT_STEREO8;
    } else if (bitmask == 0xA) {
        *format = AL_FORMAT_STEREO16;
    }
}

char AudioManager::getBitmask(ALenum format, ALuint freq) {
    char bitmask = 0;

    switch(freq)
    {
        case 22050:
            bitmask |= 0x10;
            break;
        case 44100:
            bitmask |= 0x20;
            break;
        case 48000:
            bitmask |= 0x40;
            break;
    }

    if(format == AL_FORMAT_MONO8) {
        bitmask |= 0x5;
    } else if(format == AL_FORMAT_MONO16) {
        bitmask |= 0x6;
    } else if(format == AL_FORMAT_STEREO8) {
        bitmask |= 0x9;
    } else if(format == AL_FORMAT_STEREO16) {
        bitmask |= 0xA;
    }

    return bitmask;
}

void AudioManager::encode(short* data, int nframes, Stream* out) {
    int frameSize = speex_.frameSize;

    float* input = new float[frameSize];
    char flength;
    char* fdata = new char[frameSize];
    short* pData = data;

    out->writeInt(nframes);

    for (int i = 0; i < nframes; i++) {
        /* Convert to float because speex likes floats */
        for (int j = 0; j < frameSize; j++) {
            input[j] = pData[j];
        }

        speex_bits_reset(&speex_.bits);

        speex_encode(speex_.encState, input, &speex_.bits);
        flength = speex_bits_write(&speex_.bits, (char*)fdata, frameSize);

        out->writeInt(flength);
        out->write(fdata, flength);

        pData += frameSize;
    }

    delete[] fdata;
    delete[] input;
}

void AudioManager::decode(Stream* data, int nframes, short* out) {
    int frameSize = speex_.frameSize;

    float* speexout = new float[frameSize];
    short* pOut = out;
    
    for (int i = 0; i < nframes; i++) {
        int flength = data->readInt();
        char* fdata = data->read(flength).data();

        memset(speexout, 0, frameSize * sizeof(short));
        speex_bits_read_from(&speex_.bits, fdata, flength);
        speex_decode(speex_.decState, &speex_.bits, speexout);

        for (int j = 0; j < frameSize; j++) {
            pOut[j] = (short)(speexout[j]);
        }

        pOut += frameSize;
    }
}

} /* End namespace td */
