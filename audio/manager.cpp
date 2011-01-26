#include "manager.h"
#include "openal_helper.h"
#include <iostream>

namespace td
{
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
     if( gain > 0 and gain <= 1) {
	  AudioManager::mutex_.lock();
	  this->sfxGain_ = gain; 
	  AudioManager::mutex_.unlock();
	  return true;
     }
     
     return false;
}

bool AudioManager::setMusicVolume(float gain)
{
     if( gain > 0 and gain <= 1) {
	  AudioManager::mutex_.lock();
	  this->musicGain_ = gain; 
	  AudioManager::mutex_.unlock();
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
	  alExit();
     }
}

} /* End namespace td */
