#include "manager.h"
#include "openal_helper.h"
#include <iostream>

namespace td
{

AudioManager* AudioManager::instance_ = NULL;

QMutex AudioManager::mutex_;

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
     if( gain > 0 && gain <= 1) {
	  mutex_.lock();
	  this->sfxGain_ = gain; 
	  mutex_.unlock();
	  return true;
     }
     
     return false;
}

bool AudioManager::setMusicVolume(float gain)
{
     if( gain > 0 && gain <= 1) {
	  mutex_.lock();
	  this->musicGain_ = gain; 
	  mutex_.unlock();
	  return true;
     }
     
     return false;
}

void AudioManager::playSfx(QString filename)
{
     //place holder for now
     //Spawn thread for streaming here
     checkError();
}

void AudioManager::checkError()
{
     ALuint error = alGetError();

     if (error != AL_NO_ERROR) {
	  std::cerr << alGetString(error) << std::endl;
      td::alExit();
     }
}

} /* End namespace td */
