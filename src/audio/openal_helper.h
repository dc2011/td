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

namespace td
{
/**
 * Sleep the current thread for a duration of seconds.
 *
 * This function will work cross platform
 *
 * @param duration of sleep in floating point.
 * @return true on success, false otherwise.
 */
ALboolean alSleep (ALfloat duration);

/**
 * Check the current context for being initialized with
 * no errors currently
 *
 *
 * @return true on success, false otherwise.
 */
ALboolean _alutSanityCheck();

/**
 * Initialize the openal Context
 *
 * This function must be called before any openal
 * functions will work.
 *
 * @return true on success, false otherwise.
 */
ALboolean alInit();

/**
 * Destroy the openal Context
 *
 * @return true on success, false otherwise.
 */
ALboolean alExit();
}

#endif 
