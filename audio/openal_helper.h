#ifndef _openal_helper_
#define _openal_helper_

#if defined(__WINDOWS__) || defined(_WIN32)
#include <alc.h>
#include <al.h>
#include <windows.h>
#elif defined(__APPLE__) & defined(__MACH__)
#include <OpenAL/alc.h>
#include <OpenAL/al.h>
#include <unistd.h>
#elif defined(linux) || defined(__linux)
#include <AL/al.h>
#include <AL/alc.h>
#include <unistd.h>
#endif

ALboolean alSleep (ALfloat duration);
ALboolean _alutSanityCheck(void);
ALboolean alInit(int* argcp, char** argv);
ALboolean alExit(void);

#endif 
