/**
 * \file
 *         PublicAudio.h
 * \brief
 *         This is the PublicAudio interface. Needs to be aligned with the PublicAudio.h in SW Package XCallApp
 *
 * \par Copyright Notice:
 * \verbatim
 * Copyright (c) 2021 Stellantis N.V.
 * All Rights Reserved.
 * The reproduction, transmission or use of this document or its contents is
 * not permitted without express written authority.
 * Offenders will be liable for damages. All rights, including rights created
 * by patent grant or registration of a utility model or design, are reserved.
 * \endverbatim
 */
 
#ifndef PUBLICAUDIO_H
#define PUBLICAUDIO_H

#include <chrono>
#include <string>

#define AUDIO_SRV_BUNDLE_NAME "stla.tcu.xcall.app"
#define AUDIO_SRV_ROUTER_REMOTE_SERVICE_SERVICE_NAME "Stla.TCU.Xcall.PublicAudio"
#define AUDIO_SRV_ROUTER_REMOTE_SERVICE_ADDRESS "127.0.0.1"
#define AUDIO_SRV_ROUTER_REMOTE_SERVICE_PORT "835"
#define AUDIO_SRV_ROUTER_REMOTE_SERVICE_OBJECT_NAME "PublicAudioRemoteObject"

namespace Stla {
namespace Xcall {

/**
 * \brief The PublicAudio class provides an interface to use Xcall audio functionality
 * from outside.
 */
//@ remote
class PublicAudio {
public:
    /**
     * \brief playAudioFile starts playback of the AudioFile
     * @param name path of audio file to be played
     * @return true if conditions are ok to start a playback (no ecall or acall ongoing)
     */
    virtual bool playAudioFile(const std::string& name) = 0;

    virtual ~PublicAudio() { }
};

} // namespace Xcall
} // namespace Stla

#endif // PUBLICAUDIO_H
