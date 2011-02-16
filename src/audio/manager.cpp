#include "manager.h"
#include "openal_helper.h"


namespace td {

AudioManager* AudioManager::instance_ = NULL;

QMutex AudioManager::mutex_;

AudioManager::AudioManager()
{
    AudioManager::startup();
    this->sfxGain_ = 0.9;
    this->musicGain_ = 0.65;
}

AudioManager::~AudioManager()
{
    AudioManager::shutdown();
}

void AudioManager::shutdown()
{
    if (inited_) {
        alExit();
        inited_ = false;
    }
}

void AudioManager::startup()
{
    alInit();
    inited_ = true;
}

bool AudioManager::setEffectsVolume(float gain)
{
    if (gain > 0 && gain <= 1) {
        SAFE_OPERATION(this->sfxGain_ = gain);
        return true;
    }

    return false;
}

bool AudioManager::setMusicVolume(float gain)
{
    if (gain > 0 && gain <= 1) {
        SAFE_OPERATION(this->musicGain_ = gain)
        return true;
    }

    return false;
}

void AudioManager::playSfx(QString filename)
{
    QFuture<void> future =
        QtConcurrent::run(this, &AudioManager::streamOgg,
                          filename, this->sfxGain_);
    return;
}

QQueue<QString> AudioManager::musicDir(QString dir)
{
    int i;
    QDir mDir(dir);
    mDir.setFilter(QDir::Files);
    QList<QString> musicList = mDir.entryList();
    QQueue<QString> musicQueue;

    for (i = 0; i < musicList.length(); i++) {
        musicQueue.enqueue(dir + musicList[i]);
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
	qDebug("AudioManager Error: %s", err);
        alExit();
        return true;
    }

    return false;
}

void AudioManager::playMusicQueue(QQueue<QString> filenameQueue)
{
    QString filename;

    while (!filenameQueue.empty() && inited_) {
        filename = filenameQueue.dequeue();
        AudioManager::streamOgg(filename, this->musicGain_);
        /*Sleep for 0.3 sec so playback doesn't overlap*/
        alSleep(0.3f);

        if (errno != ENOENT) {
            filenameQueue.enqueue(filename);
        }

        errno = 0;
    }
}

void AudioManager::streamOgg(QString filename, float gain)
{
    FILE* file;
    char array[BUFFERSIZE];
    int bitStream;
    int buffersAvailable = QUEUESIZE;
    long size = 0;
    long result = 0;
    ALuint buffer[QUEUESIZE];
    ALuint tempBuffer;
    ALuint source;
    ALint processed;
    ALint queued;
    ALint queue = 0;
    ALint play = AL_TRUE;
    ALint playing = AL_TRUE;
    ALenum format = AL_FORMAT_STEREO16;
    ALsizei freq = 44100;
    OggVorbis_File oggFile;
    /* Created the source and Buffers */
    alGenBuffers(QUEUESIZE, buffer);
    alGenSources(1, &source);
    /*set the Gain for Music or Sfx*/
    alSourcef(source, AL_GAIN, gain);

    if ((file = fopen(filename.toAscii().constData(), "rb")) == NULL) {
        qCritical() << "Cannot open " << filename << " for reading...";
        return;
    }

    /* Try opening the given ogg file */
    if (ov_open(file, &oggFile, NULL, 0) != 0) {
        qCritical() << "Error opening " << filename << " for decoding...";
        return;
    }

    do {
        alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

        while (processed) {
            alSourceUnqueueBuffers(source, 1, &tempBuffer);
            processed--;

            /* ensures buffers don't get larger than QUEUESIZE */
            if (buffersAvailable < QUEUESIZE - 1) {
                buffersAvailable++;
            }

            /* Restarts playing if buffer emptied too quickly */
            alGetSourcei(source, AL_SOURCE_STATE, &playing);

            if (playing == AL_STOPPED) {
                play = AL_TRUE;
            }
        }

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
                    qCritical() << "Ogg Read Failed " << endl;
                    break;
                }
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

            if (queued > 0 && play) {
                alSourcePlay(source);
                play = AL_FALSE;
            }
        } else {
            alSleep(0.1f);
        }

        /* result == 0 when file is completely read */
    } while (result > 0 && !checkError());

    ov_clear(&oggFile);

    alDeleteBuffers(QUEUESIZE,buffer);
    alDeleteSources(1, &source);
}

} /* End namespace td */
