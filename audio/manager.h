#ifndef _manager_
#define _manager_

#include <QMutex>
#include <QObject>
#include <QString>
#include <QThread>
#include <QtDebug>
#include <QtConcurrentRun>
#include <queue>
#include <vorbis/vorbisfile.h>

#define QUEUESIZE 8
#define BUFFERSIZE (1024*32)

namespace td
{

class AudioManager : public QObject {
    Q_OBJECT

private:
    /**
     * The static singleton instance of the AudioManager.
     *
     * It should only be retrieved using the instance() method, which
     * will initialize it the first time that it is retrieved.
     */
    static AudioManager* instance_;

    /**
     * A Mutex to protect instance data from multiple threads.
     *
     * This must be used any time instance data is read or updated,
     * as well as when the singleton object is checked and initialized.
     *
     * This is static because it needs to be used in the instance()
     * method.
     */
    static QMutex mutex_;

    /**
     * The number of sound files currently playing.
     *
     * This is also equal to the number of threads currently running to
     * stream sound files.
     */
    int playing_;

    /**
     * The volume/gain of the sound effects.
     */
    float sfxGain_;

    /**
     * The volume/gain of the background music.
     */
    float musicGain_;

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
     * Return the number of sound files currently being played.
     *
     * @author Darryl Pogue
     * @return The number of currently playing sounds.
     */
    int playing() const {
        mutex_.lock();
        int ret = playing_;
        mutex_.unlock();

        return ret;
    }
    
    /**
     * Set the effects volume.
     *
     * @author Terence Stenvold
     * @param gain The volume of the sound effects, between 0.0 and 1.0.
     * @return true on success, false otherwise.
     */
    bool setEffectsVolume(float gain);

    /**
     * Get the current effects volume.
     *
     * @author Darryl Pogue
     * @return The current volume of sound effects, ranging 0.0 to 1.0. 
     */
    float getEffectsVolume() const {
        mutex_.lock();
        float gain = sfxGain_;
        mutex_.unlock();

        return gain;
    }

    /**
     * Set the background music volume.
     * @author Terence Stenvold
     *
     * @param gain The volume of the background music, between 0.0 and 1.0.
     * @return true on success, false otherwise.
     */
    bool setMusicVolume(float gain);

    /**
     * Get the current background music volume.
     *
     * @author Darryl Pogue
     * @return The current volume of background music, ranging 0.0 to 1.0. 
     */
    float getMusicVolume() const {
        mutex_.lock();
        float gain = musicGain_;
        mutex_.unlock();

        return gain;
    }
    
    /**
     * Plays an Ogg Vorbis sound file.
     *
     * @author Terence Stenvold
     * @param filename The path to the .ogg file.
     */
    void playSfx(QString filename);

    /**
     * Play an Ogg Vorbis sound file, looping when it reaches the end.
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
    void playMusic(std::queue<QString> filenameQueue);
    
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
     */
    void streamOgg(QString filename);

    /**
     * Goes through all the filenames in the queue
     * it continously loops all filenames
     *
     * @param filenameQueue queue<QString> of filenames of ogg files.     *
     */
    void playMusicQueue(std::queue<QString> filenameQueue);
};

} /* end namespace td */

#endif
