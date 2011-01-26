#include "openal_helper.h"

static enum {
    Unintialized,                 /* not been initialized yet or has been de-initialised */
    ALDeviceAndContext,         /* alutInit has been called successfully */
    ExternalDeviceAndContext      /* alutInitWithoutContext has been called */
} initialisationState = Unintialized;

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

ALboolean _alutSanityCheck(void)
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

ALboolean alInit(int* argcp, char** argv)
{
    ALCdevice* device;
    ALCcontext* context;

    if (initialisationState != Unintialized) {
        return AL_FALSE;
    }

    if ((argcp == NULL) != (argv == NULL)) {
        return AL_FALSE;
    }

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

ALboolean alExit(void)
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
