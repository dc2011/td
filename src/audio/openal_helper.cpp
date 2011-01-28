#include "openal_helper.h"

namespace td {
/**
 * Enum for the possible states of the openal context
 */
static enum {
    Unintialized, /* not been initialized yet or has been de-initialised */
    ALDeviceAndContext, /* alutInit has been called successfully */
    ExternalDeviceAndContext /* alutInitWithoutContext has been called */
} initialisationState = Unintialized;

/**
 * static context for the current context
 * don't touch this. I have no idea what it does
 * all this code came from freeAlut
 */
static ALCcontext* alContext;

ALboolean alSleep(ALfloat duration)
{
    if (duration < 0) {
        return AL_FALSE;
    }

    ALuint seconds = (ALuint) duration;
    ALfloat rest = duration - (ALfloat) seconds;
#if defined(__WINDOWS__) || defined(_WIN32)

    while (seconds > 0) {
        Sleep(1000);
        seconds--;
    }

    Sleep((DWORD)(rest * 1000));
#else

    while (seconds > 0) {
        usleep(1000000);
        seconds--;
    }

    usleep((unsigned int)(rest * 1000000));
#endif
    return AL_TRUE;
}

ALboolean _alutSanityCheck()
{
    ALCcontext* context;

    if (initialisationState == Unintialized) {
        return AL_FALSE;
    }

    context = alcGetCurrentContext();

    if (context == NULL) {
        return AL_FALSE;
    }

    if (alGetError() != AL_NO_ERROR) {
        return AL_FALSE;
    }

    if (alcGetError(alcGetContextsDevice(context)) != ALC_NO_ERROR) {
        return AL_FALSE;
    }

    return AL_TRUE;
}

/**
 * originally took int* argcp and char **argv
 * as parameters unused so I've removed them.
 */
ALboolean alInit()
{
    ALCdevice* device;
    ALCcontext* context;

    if (initialisationState != Unintialized) {
        return AL_FALSE;
    }

    /** Completely usesless So it's been removed
     *
     *if ((argcp == NULL) != (argv == NULL)) {
     *return AL_FALSE;
     *}
     */
    device = alcOpenDevice(NULL);

    if (device == NULL) {
        return AL_FALSE;
    }

    context = alcCreateContext(device, NULL);

    if (context == NULL) {
        alcCloseDevice(device);
        return AL_FALSE;
    }

    if (!alcMakeContextCurrent(context)) {
        alcDestroyContext(context);
        alcCloseDevice(device);
        return AL_FALSE;
    }

    initialisationState = ALDeviceAndContext;
    alContext = context;
    return AL_TRUE;
}

ALboolean alExit()
{
    ALCdevice* device;

    if (initialisationState == Unintialized) {
        return AL_FALSE;
    }

    if (initialisationState == ExternalDeviceAndContext) {
        return AL_TRUE;
    }

    if (!_alutSanityCheck()) {
        return AL_FALSE;
    }

    if (!alcMakeContextCurrent(NULL)) {
        return AL_FALSE;
    }

    device = alcGetContextsDevice(alContext);
    alcDestroyContext(alContext);

    if (alcGetError(device) != ALC_NO_ERROR) {
        return AL_FALSE;
    }

    if (!alcCloseDevice(device)) {
        return AL_FALSE;
    }

    initialisationState = Unintialized;
    return AL_TRUE;
}

}
