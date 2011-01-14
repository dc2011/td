#ifndef _sound_
#define _sound_
#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <vector>
#include <AL/alut.h>
#include <vorbis/vorbisfile.h>

#define BUFFER_SIZE (1024 * 32) //32kB Buffer

ALuint loadFile(const char* fileName);
ALuint loadOgg(const char *fileName);
int playSound(ALuint buffer);
int playSound(ALuint buffer, const int duration);
int playLoop(const std::string fileName, const int duration);
int playFile(const std::string fileName);
void checkError();

#endif
