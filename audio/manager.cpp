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
     AudioManager::mutex_.lock();
     if( gain > 0 and gain <= 1) {
	  AudioManager::sfxGain_ = gain; 
	  return true;
     }
     AudioManager::mutex_.unlock();
     
     return false;
}

bool AudioManager::setMusicVolume(float gain)
{
     AudioManager::mutex_.lock();
     if( gain > 0 and gain <= 1) {
	  AudioManager::musicGain_ = gain; 
	  return true;
     }
     AudioManager::mutex_.unlock();
     
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
