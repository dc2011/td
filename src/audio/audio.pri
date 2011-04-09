AUDIO_HDRS +=   ./audio/SfxManager.h

AUDIO_SRCS +=   ./audio/SfxManager.cpp


AUDIO_HDRS_C += $$AUDIO_HDRS \
                ./audio/manager.h \
                ./audio/openal_helper.h

AUDIO_SRCS_C += $$AUDIO_SRCS \
                ./audio/manager.cpp \
                ./audio/openal_helper.cpp
