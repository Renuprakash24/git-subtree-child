/**
 * \file     IXcallService.h
 * \brief    This is the IXcallService interface.
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
 
#ifndef IXCALLSERVICE_H
#define IXCALLSERVICE_H

#include "Poco/OSP/Service.h"
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"
#include "PublicXcall.h"

static const std::string InterfaceXCallService {"stla.tcu.xcall.service.base"};

namespace Stla {
namespace Xcall {


            /**
             * @brief Interface of the XCall Service
             */
            class IXcallService: public Poco::OSP::Service , public PublicEcall
            {
            public:
                /**
                @brief  Ptr is an auto pointer of IXcallServiceclass service
                */
                typedef Poco::AutoPtr<IXcallService> Ptr;

                /**
                 * @brief Constructor declaration
                 */
                IXcallService() {}

                /**
                 * @brief Destructor declaration
                 */
                virtual ~IXcallService() {}

            };
}
}
#endif
