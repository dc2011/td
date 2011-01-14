#include "record.h"

using namespace std;

//These need to be fooled around with
#define QUEUEBUFFERSIZE  1024
#define QUEUEBUFFERCOUNT 8


void listDevices()
{
    const ALCchar* defaultCaptureDevice;
    // Get list of available Capture Devices
    const ALchar* deviceLst = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);

    if (deviceLst) {
        cout << "Available Capture Devices are:-" << endl;

        while (*deviceLst) {
            cout << deviceLst << endl;
            deviceLst += strlen(deviceLst) + 1;
        }
    }

    defaultCaptureDevice = alcGetString(NULL, 
					ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
    cout << "\nDefault Capture Device is " << defaultCaptureDevice << endl;
}

void capturePlay(void)
{
    ALCdevice* captureDevice;
    ALint samplesAvailable;
    ALchar buffer[QUEUEBUFFERSIZE];
    ALuint sourceID, tempBufferID;
    ALuint bufferID[QUEUEBUFFERCOUNT];
    ALuint buffersAvailable = QUEUEBUFFERCOUNT;
    ALuint unqueueCount, queueCount;
    ALint  loop, format, frequency, blockAlignment, processed, playin;
    ALboolean playing = AL_FALSE;
    ALboolean play = AL_FALSE;
    long totalProcessed = 0;
    long oldSamplesAvailable = 0;
    long oldTotalProcessed = 0;
   
    // Generate a Source and QUEUEBUFFERCOUNT Buffers for Queuing
    alGenSources(1, &sourceID);
    for (loop = 0; loop < QUEUEBUFFERCOUNT; loop++) {
        alGenBuffers(1, &bufferID[loop]);
    }

    if (alGetError() != AL_NO_ERROR) {
        cerr << "Failed to generate Source and / or Buffers\n" << endl;
        return;
    }

    unqueueCount = 0;
    queueCount = 0;

    //we can mess with these as well
    format = AL_FORMAT_MONO16;
    frequency = 44100;

    //if format switched to ...MONO8 or STEREO8 this is 1
    blockAlignment = 2;

    //NULL sets it to use default device
    captureDevice = alcCaptureOpenDevice(NULL, frequency, format, frequency);

    if (captureDevice) {
        cout << "Opened Capture Device " << endl;
        alcCaptureStart(captureDevice);
        play = AL_TRUE;

        while (1) {
            alGetError();
            alcGetIntegerv(captureDevice, ALC_CAPTURE_SAMPLES, 1, 
			   &samplesAvailable);

            if ((oldSamplesAvailable != samplesAvailable) || 
		(oldTotalProcessed != totalProcessed)) {
		oldSamplesAvailable = samplesAvailable;
		oldTotalProcessed = totalProcessed;
	    }


            // If the Source is (or should be) playing, get
            // and check play status
            if (playing) {
                alGetSourcei(sourceID, AL_BUFFERS_PROCESSED, &processed);

                while (processed) {
                    totalProcessed++;
                    // Unqueue the buffer
                    alSourceUnqueueBuffers(sourceID, 1, &tempBufferID);

                    // Update unqueue count
                    if (++unqueueCount == QUEUEBUFFERCOUNT) {
                        unqueueCount = 0;
                    }

                    buffersAvailable++;
                    processed--;
                }

                alGetSourcei(sourceID, AL_SOURCE_STATE, &playin);

                if (playin == AL_STOPPED) {
		     play = AL_TRUE;
                }
            }

            if ((samplesAvailable > (QUEUEBUFFERSIZE / blockAlignment)) && 
		!(buffersAvailable)) {
                cerr << "underrun!\n";
            } else {
                // When we have enough data to fill our
                if ((samplesAvailable > (QUEUEBUFFERSIZE / blockAlignment)) &&
		    (buffersAvailable)) {
                    // Consume Samples
                    alcCaptureSamples(captureDevice, buffer, 
				      QUEUEBUFFERSIZE / blockAlignment);
                    alBufferData(bufferID[queueCount], format, buffer, 
				 QUEUEBUFFERSIZE, frequency);
                    // Queue the buffer, and mark buffer asqueued
                    alSourceQueueBuffers(sourceID, 1, &bufferID[queueCount]);

                    if (++queueCount == QUEUEBUFFERCOUNT) {
                        queueCount = 0;
                    }

                    // Decrement buffers available
                    buffersAvailable--;
		    
                    if ((play) && (buffersAvailable <= 
				   (QUEUEBUFFERCOUNT - 2))) {
                        alSourcePlay(sourceID);
			playing = AL_TRUE;
                        play = AL_FALSE;
                    }
                }
            }
        }
    }

    alcCaptureCloseDevice(captureDevice);
    alSourceStop(sourceID);
    alDeleteSources(1, &sourceID);

    for (loop = 0; loop < QUEUEBUFFERCOUNT; loop++) {
        alDeleteBuffers(1, &bufferID[loop]);
    }
}
