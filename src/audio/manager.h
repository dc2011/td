#ifndef _manager_
#define _manager_

#include <QMutex>
#include <QObject>
#include <QString>
#include <QThread>
#include <QtDebug>
#include <QtConcurrentRun>
#include <QQueue>
#include <QDir>
#include <vorbis/vorbisfile.h>
#include <errno.h>
#include <sys/types.h>
#include "../util/mutex_magic.h"

#define QUEUESIZE 8
#define BUFFERSIZE (1024*32)

enum SoundType {
     sfx,
     ntf,
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
     * The number of audio tracks playing
     */
    int playing_;
 
    /**
     * Whether the AudioManager has been initialized.
     *
     * In practice, this should only be used when checking whether OpenAL is
     * initialized. Code that actually deals with OpenAL should call the
     * checkError() method instead of using this value!
     */
    bool inited_;

private:
    explicit AudioManager();
    ~AudioManager();
    
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
     * @param gain is a float with a default param of 1.0
     */
    void streamOgg(QString filename, float gain = 1);

    /**
     * Goes through all the filenames in the queue
     * it continously loops all filenames
     *
     * @author Terence Stenvold
     * @param filenameQueue queue<QString> of filenames of ogg files.     *
     */
    void playMusicQueue(QQueue<QString> filenameQueue);

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
     * Plays an Ogg Vorbis sound file.
     *
     * @author Terence Stenvold
     * @param filename The path to the .ogg file.
     * @param SoundType either ntf for notifcation or sfx. defaults sfx. 
     */
    void playSfx(QString filename, SoundType type=sfx);

    /**
     * Play an Ogg Vorbis sound file, looping when it reaches the end.
     * !!!NOT IMPLEMENTED!!!
     *
     * @author Terence Stenvold
     * @param filename The path to the .ogg file.
     * @param loop The number of times to loop the sound file. The default 
     * of -1 results in infinite looping.
     */
    void loopSfx(QString filename, int loop = -1);

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
