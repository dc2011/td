#include "sound.h"

using namespace std;

ALuint loadWav(const char* fileName)
{
    ALuint buffer;
    /* Create an AL buffer from the given sound file. */
    buffer = alutCreateBufferFromFile(fileName);

    if (buffer == AL_NONE) {
        checkError();
    }

    return buffer;
}

ALuint loadOgg(const char* fileName)
{
    int endian = 0;
    int bitStream;
    long bytes;
    char array[BUFFER_SIZE];
    vector<char> bufferData;
    ALuint buffer;
    ALenum format;
    ALsizei freq;
    FILE* f;
    vorbis_info* pInfo;
    OggVorbis_File oggFile;
    alGenBuffers(1, &buffer);
    f = fopen(fileName, "rb");

    if (f == NULL) {
        cerr << "Cannot open " << fileName << " for reading..." << endl;
        return -1;
    }

    // Try opening the given file
    if (ov_open(f, &oggFile, NULL, 0) != 0) {
        cerr << "Error opening " << fileName << " for decoding..." << endl;
        return -1;
    }

    // Get some information about the OGG file
    pInfo = ov_info(&oggFile, -1);

    // Check the number of channels... always use 16-bit samples
    if (pInfo->channels == 1) {
        format = AL_FORMAT_MONO16;
    } else {
        format = AL_FORMAT_STEREO16;
    }

    // The frequency of the sampling rate
    freq = pInfo->rate;

    // Keep reading until all is read
    do {
        // Read up to a buffer's worth of decoded sound data
        bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);

        if (bytes < 0) {
            ov_clear(&oggFile);
            cerr << "Error decoding " << fileName << "..." << endl;
            return -1;
        }

        // end if
        // Append to end of buffer
        bufferData.insert(bufferData.end(), array, array + bytes);
    } while (bytes > 0);

    // Clean up!
    ov_clear(&oggFile);
    alBufferData(buffer, format, &bufferData[0],
                 static_cast<ALsizei>(bufferData.size()), freq);
    checkError();
    return buffer;
}


int playSound(ALuint buffer)
{
    ALint status;
    ALuint source;
    /* Generate a single source, attach the buffer to it and start playing. */
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
    checkError();

    do {
        alutSleep(0.1f);
        alGetSourcei(source, AL_SOURCE_STATE, &status);
    } while (status == AL_PLAYING);

    return 0;
}

int playSound(ALuint buffer, const int duration)
{
    ALuint source;
    time_t startTime;
    time(&startTime);
    /* Generate a single source, attach the buffer to it and start playing. */
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcei(source, AL_LOOPING, AL_TRUE); //Set looping on
    alSourcePlay(source);
    checkError();

    do {
        alutSleep(0.1f);
    } while (time(NULL) < (startTime + duration));

    return 0;
}


int playFile(const string fileName)
{
    ALuint buffer;
    buffer = loadOgg(fileName.c_str());

    if (buffer == AL_NONE) {
        checkError();
        return -1;
    }

    if (playSound(buffer) != 0) {
        checkError();
        return -2;
    }

    return 0;
}

int playLoop(const string fileName, const int duration)
{
    ALuint buffer;
    buffer = loadOgg(fileName.c_str());

    if (buffer == AL_NONE) {
        checkError();
        return -1;
    }

    if (playSound(buffer, duration) != 0) {
        checkError();
        return -2;
    }

    return 0;
}

void checkError()
{
    ALuint error = alGetError();

    if (error != ALUT_ERROR_NO_ERROR) {
        cerr << alGetString(error) << endl;
        alutExit();
    }
}
