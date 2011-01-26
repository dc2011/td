#include <QMutex>
#include <QObject>
#include <QString>
#include <QThread>
#include <queue>

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
     * @return A pointer to the AudioManager instance.
     */
    static AudioManager* instance() {
        mutex_.lock()
        if (instance_ == NULL) {
            instance_ = new AudioManager();
        }
        mutex_.unlock();

        return instance_;
    }

    /**
     * Return the number of sound files currently being played.
     *
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
     * @param gain The volume of the sound effects, between 0.0 and 1.0.
     * @return true on success, false otherwise.
     */
    bool setEffectsVolume(float gain);

    /**
     * Get the current effects volume.
     *
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
     *
     * @param gain The volume of the background music, between 0.0 and 1.0.
     * @return true on success, false otherwise.
     */
    bool setMusicVolume(float gain);

    /**
     * Get the current background music volume.
     *
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
     * @param filename The path to the .ogg file.
     */
    void playSfx(QString filename);

    /**
     * Play an Ogg Vorbis sound file, looping when it reaches the end.
     *
     * @param filename The path to the .ogg file.
     * @param loop The number of times to loop the sound file. The default 
     * of -1 results in infinite looping.
     */
    void loopSfx(QString filename, int loop = -1);

    /**
     * Play the Queue of Ogg Vorbis sound files as background music.
     *
     * @param filenameQueue queue<QString> of filenames of ogg files.
     */    
    void playMusic(std::queue<QString> filenameQueue);
    
    /**
     * Does a check for openal errors and destroys the openal 
     * context if any are found
     * printf to stderr right now.
     */
    void checkError()
};

} /* end namespace td */
