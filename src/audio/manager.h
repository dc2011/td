#ifndef _manager_
#define _manager_

#include <QDebug>

#include <QMutex>
#include <QObject>
#include <QString>
#include <QThread>
#include <QtDebug>
#include <QtConcurrentRun>
#include <QQueue>
#include <QByteArray>
#include <QDir>
#include <vorbis/vorbisfile.h>
#include <speex/speex.h>
#include <errno.h>
#include <sys/types.h>
#include "../util/mutex_magic.h"
#include "openal_helper.h"
#include "../network/stream.h"

#define QUEUESIZE 8
#define BUFFERSIZE (1024*32)
#define SFXPATH "./sound/sfx/"
#define SFXFILEEXTENSION ".ogg"

enum SoundType {
     sfx,
     ntf,
     msk
};

namespace td
{

/**
 * The client-side audio manager class.
 * A client must call the instance() method first to create and  
 * initialize the singleton instance. Once a call to instance() has been made,
 * this class is thread-safe.
 *
 * Internally in the class everytime playSfx is called, It creates
 * a thread specifically to play that file to completion.
 * To play music You can build a QQueue of filenames and pass that
 * to playMusic(). playMusic() loops through the queue, Meaning after 
 * finishing a song it puts it in the back of the queue. 
 *
 * The only way to stop a sound from playing is by calling shutdown().
 * After this is called if you wish to play sounds again you 
 * need to call startup();
 *
 * A typical use of the AudioManager class looks like this:
 * @code
 *   QString filename = "fire.ogg";
 *   QQueue musicList = td::AudioManager::instance()->musicDir("sound/music");
 *
 *   //This is the same call as playSfx(filename, sfx);
 *   td::AudioManager::instance()->playSfx(filename);
 *   //If the sound is a notification add ntf to the argument list
 *   td::AudioManager::instance()->playSfx(filename, ntf);
 *
 *   td::AudioManager::instance()->playMusic(musicList);
 *
 *   //call when you wish all sounds to stop
 *   td::AudioManager::instance()->shutdown();
 * @endcode
 *
 * @author Darryl Pogue
 * @author Terence Stenvold
 */
class AudioManager : public QObject {
    Q_OBJECT

    THREAD_SAFE_SINGLETON

private:
    /**
     * A structure to contain values needed by Speex for encoding and decoding
     * voice data.
     *
     * @author Darryl Pogue
     */
    struct SpeexState {
        SpeexBits bits; /**< The Speex bits. */
        void* encState; /**< The Speex encoder. */
        void* decState; /**< The Speex decoder. */
        int frameSize;  /**< The size of a frame. */
        int quality;    /**< The quality of resulting data. */
        int sampleRate; /**< The sampling rate for Speex. */

    };

private:
    /**
     * The static singleton instance of the AudioManager.
     *
     * It should only be retrieved using the instance() method, which
     * will initialize it the first time that it is retrieved.
     */
    static AudioManager* instance_;

    /**
     * Array containing possible Gain levels
     */
    static float gainScale[];

    /**
     * Map for the cached sound effects
     */
    static QMap<QString,QByteArray> sfxCache_;

    /**
     * The volume/gain of the sound effects.
     */
    int sfxGain_;

    /**
     * The volume/gain of the notifications.
     */
    int notiGain_;

    /**
     * The volume/gain of the background music.
     */
    int musicGain_;

    /**
     * The volume/gain of the voice chat.
     */
    int voiceGain_;

    /**
     * The number of audio tracks playing
     */
    int playing_;

    /**
     * Pauses the capturing from micx
     */
    static bool capturePause_;

    /**
     * stops the capture thread
     */
    static bool captureStop_;
 
    /**
     * The queue for network audio data
     */ 
    static QQueue<Stream *> netQueue_; 
   
    /**
     * Whether the AudioManager has been initialized.
     *
     * In practice, this should only be used when checking whether OpenAL is
     * initialized. Code that actually deals with OpenAL should call the
     * checkError() method instead of using this value!
     */
    bool inited_;

    /** The Speex state for the audio manager. */
    SpeexState speex_;

private:
    explicit AudioManager();
    ~AudioManager();

    /**
     * Initializes the Speex encoder/decoder for voice data.
     *
     * @author Darryl Pogue
     * @author Terence Stenvold
     */
    void initSpeex();
    
    /**
     * Stream the voice data
     *
     * @author Terence Stenvold
     */
    void streamVoice();

    /**
     * Captures audio from the microphone
     * eventually transfer across the network
     *
     * @author Terence Stenvold
     */
    void captureMic();

    /**
     * Does a check for openal errors and destroys the openal 
     * context if any are found
     * 
     * @author Terence Stenvold
     * @return bool if True and error occured
     */
    bool checkError();

    /**
     * Streams and plays an Ogg File.
     *
     * This is meant to be called in it's own thread.
     *
     * @author Terence Stenvold
     * @param filename the path to file.
     * @param sType is the type of the sound file
     * @param cacheThis is whether to cache the sfx or not
     */
    void streamFile(QString filename, SoundType sType, bool cacheThis = false);

    /**
     * Goes through all the filenames in the queue
     * it continously loops all filenames
     *
     * @author Terence Stenvold
     * @param filenameQueue queue<QString> of filenames of ogg files.     *
     */
    void playMusicQueue(QQueue<QString> filenameQueue);

    /**
     * cleans up the buffers and source 
     *
     * @author Terence Stenvold
     * @param source is the openal playable source
     * @param buffer is the array of buffers
     */
    void cleanUp(ALuint *source, ALuint *buffer);

    /**
     * Clears buffers that have been played already
     *
     * @author Terence Stenvold
     * @param source is the openal playable source
     * @param buffersAvailable reference to the number of buffers to fill
     * @param playing boolean whether the track in playing
     * @param play boolean to set if it needs to be played or not
     */
    void clearProcessedBuffers
	(ALuint *source, int &buffersAvailable, ALint *playing, ALint* play);

    /**
     * Opens an ogg file and sets the format
     *
     * @author Terence Stenvold
     * @param file is the file pointer
     * @param oggFile is the ogg vorbis file descriptor
     * @param format is the openal output format
     * @param freq is the frequency to play at
     */
    void openOgg(FILE *, OggVorbis_File *, ALenum *, ALsizei *);

    /**
     * Plays the cached buffers back
     *
     * @author Terence Stenvold
     * @param filename is the filename 
     * @param sType is the type of the sound file
     */
    void playCached(QString filename, SoundType sType);

    /**
     * Encode voice data using Speex.
     *
     * @author Darryl Pogue
     * @author Terence Stenvold
     * @param data The buffer of microphone data to be encoded.
     * @param nframes The number of frames of microphone data.
     * @param out The stream to which the compressed data is written.
     */
    void encode(short* data, int nframes, Stream* out);

    /**
     * Decode voice data using Speex.
     *
     * @author Darryl Pogue
     * @author Terence Stenvold
     * @param data The stream of compressed voice data.
     * @param nframes The number of frames of voice data.
     * @param out The buffer to which to write decompressed data.
     */
    void decode(Stream* data, int nframes, short* out);


public:

    /**
     * Return the instance of the AudioManager.
     * This creates a new instance the first time that it is called and 
     * always returns that instance when called further in the program's 
     * execution.
     *
     * @author Darryl Pogue
     * @return A pointer to the AudioManager instance.
     */
    static AudioManager* instance() {
        mutex_.lock();
        if (instance_ == NULL) {
            instance_ = new AudioManager();
        }
        mutex_.unlock();

        return instance_;
    }

    /**
     * Toggles pausing of the capture
     * thread
     * 
     * @author Terence Stenvold
     */
    static void toggleCapturePause() {
	mutex_.lock();
	capturePause_ = !capturePause_;
	mutex_.unlock();
    }

    /**
     * toggles the stopping of the capture
     * thread
     * 
     * @author Terence Stenvold
     */
    static void toggleCaptureStop() {
	mutex_.lock();
	captureStop_ = !captureStop_;
	mutex_.unlock();
    }
    
    /**
     * Set the music volume
     *
     * @author Terence Stenvold
     */
    void setMusicVol(int vol) {
	setVol(vol,&musicGain_);
    }

    /**
     * Set the sfx volume
     *
     * @author Terence Stenvold
     */
    void setSfxVol(int vol) {
	setVol(vol,&sfxGain_);
	if(vol<80 && vol != 0) {
	    setVol(vol+20,&notiGain_);
	} else {
	    setVol(vol,&notiGain_);
	}
    }

    /**
     * Set the voice volume
     *
     * @author Terence Stenvold
     */
    void setVoiceVol(int vol) {
	setVol(vol,&voiceGain_);
    }

    /**
     * Set the generic volume
     *
     * @author Terence Stenvold
     */
    void setVol(int vol, int *gain) {

        if(vol<=100 && vol >= 0) {
	    *gain = (int)(vol/5);
        }
    }

    /**
     * Set the music volume
     *
     * @author Terence Stenvold
     * @return volume scale of music
     */
    int getMusicVol() {
        return (int)(gainScale[musicGain_] * 100);
    }

    /**
     * Set the sfx volume
     *
     * @author Terence Stenvold
     * @return volume scale of sfx
     */
    int getSfxVol() {
        return (int)(gainScale[sfxGain_] * 100);
    }

    /**
     * get the voice volume
     *
     * @author Terence Stenvold
     * @return volume scale of voice
     */
    int getVoiceVol() {
        return (int)(gainScale[voiceGain_] * 100);
    }


    /**
     * Adds the buffer into the cached map
     *
     * @author Terence Stenvold
     * @param filename is the files name
     * @param buf is the PCM data buffer
     * @param size is the size of the data buffer
     * @param bitmask contains the freq and format of the audio
     */
    static void cacheBuffer(QString filename, char *buf, 
			    long size, char bitmask) {
	
	QByteArray tmp(buf,size);

	mutex_.lock();
	if(sfxCache_.contains(filename)) {
	    sfxCache_[filename].append(tmp);
	} else {
	    tmp.prepend(bitmask);
	    sfxCache_.insert(filename,tmp);
	}
	mutex_.unlock();
    }

    /**
     * get the next buffer in the queue
     *
     * @author Terence Stenvold
     * @return the next buffer
     */
    static Stream* getNextInQueue() {
	Stream *temp;
	mutex_.lock();
        if(netQueue_.count() > 0) {
	    temp = netQueue_.dequeue();
	}
	mutex_.unlock();
	return temp;
    }
    
    /**
     * gets the size of the queue
     *
     * @author Terence Stenvold
     * @return the size of the queue
     */
    static int getQueueSize() {
	return netQueue_.count();
    }

    /**
     * add a buffer to the queue
     *
     * @author Terence Stenvold
     * @param buffer is the buffer
     */
    static void addToQueue(Stream *s) {
	mutex_.lock();
	netQueue_.enqueue(s);
	mutex_.unlock();
    }


    /**
     * set the bitmask from the format and freq
     *
     * @author Terence Stenvold
     * @param format is like stereo16 or mono8 etc
     * @param freq is the frequency to play at
     */
    char getBitmask(ALenum format, ALuint freq);

    /**
     * get the bitmask for the format and freq
     *
     * @author Terence Stenvold
     * @param bitmask is the bitmask of the format freq
     * @param *format is like stereo16 or mono8 etc
     * @param *freq is the frequency to play at
     */
    void getSpecs(char bitmask, ALenum *format, ALuint *freq);

    /**
     * Destroy the OpenAL context and try to clean up any resources.
     * This must be called manually when the main application exits to ensure
     * that OpenAL is properly deinitialized and that all open sound files
     * are closed.
     *
     * @author Darryl Pogue
     */
    void shutdown();

    /**
     * Creates the OpenAL context. This does not need to be called except 
     * this must be called manually when you want to continue using
     * sounds but have called shutdown() already
     *
     * @author Terence Stenvold
     */
    void startup();
    
    /**
     * Starts the thread for captureing
     * the mic
     *
     * @author Terence Stenvold
     */
    void startCapture();

    /**
     * Plays an Ogg Vorbis sound file.
     *
     * @author Terence Stenvold
     * @param filename The path to the .ogg file.
     * @param type is a Enum either ntf for notifcation or sfx. defaults sfx. 
     */
    void playSfx(QString filename, SoundType type=sfx);

    /**
     * Overloaded function that randomly picks and 
     * Plays an Ogg Vorbis sound file.
     *
     * @author Terence Stenvold
     * @param files the list of filesname paths to the .ogg files.
     * @param type is a Enum either ntf for notifcation or sfx. defaults sfx. 
     */
    void playSfx(QStringList files, SoundType type=sfx);

    /**
     * Play the Queue of Ogg Vorbis sound files as background music.
     *
     * @author Terence Stenvold
     * @param filenameQueue queue<QString> of filenames of ogg files.
     */    
    void playMusic(QQueue<QString> filenameQueue);

    /**
     * Returns a randomized QQueue of files to be used for playMusic()
     * 
     * @author Terence Stenvold
     * @param dir The directory containing ogg files.
     * @return A queue of filenames to be passed to playMusic().
     */
    QQueue<QString> musicDir(QString dir);

};

} /* end namespace td */

#endif
