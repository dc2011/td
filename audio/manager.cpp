#include "manager.h"

AudioManager::AudioManager()
{
     alInit();
}

AudioManager::~AudioManager()
{
     alExit();
}

bool AudioManager::setEffectsVolume(float gain)
{
     mutex_.lock()
     if( gain > 0 and gain <= 1) {
	  sfxGain = gain; 
     }
     mutex_.unlock()
}

bool AudioManager::setMusicVolume(float gain)
{
     mutex_.lock()
     if( gain > 0 and gain <= 1) {
	  musicGain = gain; 
     }
     mutex_.unlock()
}

void playSfx(QString filename)
{
     //place holder for now
     //Spawn thread for streaming here
     checkError();
}

void checkError()
{
     ALuint error = alGetError();

     if (error != AL_NO_ERROR) {
	  cerr << alGetString(error) << endl;
	  alExit();
     }
}
