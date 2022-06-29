/**
 * \file
 *         IAudioService.h
 * \brief
 *         This is the IAudioService interface
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
 
#ifndef IAUDIOSERVICE_H
#define IAUDIOSERVICE_H

#include "Poco/OSP/Service.h"
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"
#include "PublicAudio.h"

static const std::string InterfaceAudioService {"stla.tcu.audio.service.base"};

namespace Stla {
namespace Xcall {

            /**
             * @brief Interface of the XCall Service
             */
            class IAudioService: public Poco::OSP::Service , public PublicAudio
            {
            public:
                /**
                @brief  Ptr is an auto pointer of IAudioServiceclass service
                */
                typedef Poco::AutoPtr<IAudioService> Ptr;

                /**
                 * @brief Constructor declaration
                 */
                IAudioService() {}

                /**
                 * @brief Destructor declaration
                 */
                virtual ~IAudioService() {}

            };
        }
}
#endif
