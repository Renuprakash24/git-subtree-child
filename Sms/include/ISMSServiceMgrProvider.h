/**
 * \file
 *          ISMSServiceMgrProvider.h
 * \brief
 *          Interface of SMS Service Manager Provider for Applications to get an object of ISMSServiceMgr class.
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
 
#ifndef ISMSSERVICESMGRPROVIDER_H
#define ISMSSERVICESMGRPROVIDER_H

#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Service.h"
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"

#include "ISMSServiceMgr.h"
#include "ISMSServiceMgrTypes.h"

#define SMS_SRV_BS_BUNDLE_NAME "stla.connectivity.sms.service.base"

using Poco::BasicEvent;

namespace Stla {
namespace Connectivity {
        /**
         * @brief Interface of the SMS Manager Service - Provides registration and unregistration functionality, gives access to SMS Manager
         */
        #ifdef DOXYGEN_WORKING
        class ISMSServiceMgrProvider:public Poco::OSP::Service
        #else
        class __attribute__((visibility("default"))) ISMSServiceMgrProvider:public Poco::OSP::Service
        #endif
        {
        public:

            /**
            @brief  Ptr is an auto pointer of ISMSServiceMgrProvider class service
            */
            typedef Poco::AutoPtr<ISMSServiceMgrProvider> Ptr;

            /**
             * @brief   Returns the service information for the object's class.
             */
            const std::type_info& type() const
            {
                return typeid(ISMSServiceMgrProvider);
            }

            /**
             * @brief   Returns true if the class is a subclass of the class given by obj.
             */
            bool isA(const std::type_info& obj) const
            {
                std::string name(type().name());
                return name == obj.name();
            }

            /**
            * \brief SMSRegister: Interface to register for SMS service, it provides an SMSMgr Obj to call SMS manager interfaces.
            *
            * \param [in] AppName - Application symbolic name.
            * \return ISMSServiceMgr::Ptr: Instance of CSMSServiceMgr type. NULL in case service is not available.
            *
            * \pre : SMS service is available.
            * \post : Client will be registered for SMS service, if incoming messages arrive, the client will be notified.
            * \msc
            * hscale="2";
            * psaapp [label=""],
            * srvbase [label=""],
            * srvmgr [label=""];
            * psaapp box psaapp [label="ClientApp"],
            * srvbase box srvbase [label="SMSServiceBase"],
            * srvmgr box srvmgr [label="SMSServicesMgr"];
            * psaapp => srvbase[label="ISMSServiceMgr::Ptr poSMSMgr = SMSRegister(AppName=Context->thisBundle()->symbolicName())"];
            * srvbase box srvbase [label="requester = AppName; "];
            * ---[label="if (SMS service is available)", linecolor="#0000FF"];
            * ---[label="if (requester is not a client)", linecolor="#1BC745"];
            * srvbase =>> srvmgr[label="poSMSMgr = new CSMSServiceMgr(m_pSMSRemoteService,AppName);"];
            * srvmgr =>> srvmgr[label="init()"];
            * srvmgr >> srvbase[label="poSMSMgr"];
            * srvbase box srvbase [label="client[requester] = poSMSMgr;"];
            * ---[label="else", linecolor="#1BC745"];
            * srvbase box srvbase [label="poSMSMgr = client[requester];"];
            * ---[label="", linecolor="#1BC745"];
            * --- [label="else", linecolor="#0000FF"];
            * srvbase box srvbase [label="poSMSMgr = NULL", textcolor="#FF0000"];
            * ---[label="", linecolor="#0000FF"];
            * srvbase >> psaapp[label="poSMSMgr"];
            * psaapp box psaapp [label="poSMSMgr->smsMsgReceived += Poco::delegate(this,&ClientApp::onReceivedSMS)"];
            * psaapp box psaapp [label="poSMSMgr->smsSendStatus += Poco::delegate(this,&ClientApp::onSendStatus)"];
            * |||;
            * \endmsc
            * \note The client must use the Symbolic name of the bundle to register.
            * The client needs to check the validity of the returned object. After obtaining the object,
            * the client should delegate functions for SMS manager events.
            */
            virtual ISMSServiceMgr::Ptr SMSRegister(std::string AppName) = 0;

            /**
            * \brief SMSUnregister: Interface to unregister a client App from SMS service.
            *
            * \param [in] AppName - Application symbolic name to be unregistered
            * \return ISMSServiceMgr::Ptr: Instance of CSMSServiceMgr type. NULL in case service is not available.
            *
            * \pre : Client is registered to SMS service.
            * \post : Client will be unregistered from SMS service.
            * \msc
            * hscale="2";
            * psaapp [label=""],
            * srvbase [label=""];
            * psaapp box psaapp [label="ClientApp"],
            * srvbase box srvbase [label="SMSServiceBase"];
            * |||;
            * psaapp box psaapp [label="poSMSMgr->smsMsgReceived -= Poco::delegate(this,&ClientApp::onReceivedSMS)"];
            * psaapp box psaapp [label="poSMSMgr->smsSendStatus -= Poco::delegate(this,&ClientApp::onSendStatus)"];
            * psaapp =>> srvbase[label="SMSUnregister(AppName)"];
            * ---[label="if (AppName is a client)", linecolor="#7f7fff", textcolor="#7f7fff"];
            * srvbase box srvbase [label="remove client"];
            * srvbase >> psaapp[label="SMS_RET_SUCCESS"];
            * ---[label="else", linecolor="#7f7fff", textcolor="#7f7fff"];
            * srvbase >> psaapp[label="SMS_RET_CLIENT_REG_ERROR"];
            * |||;
            * \endmsc
            * \note When client is unregistered messages will not be forwarded, but they will be kept in storage.
            */
            virtual enReturnSMS_t SMSUnregister(std::string AppName) = 0;

        };
    }
}
#endif //ISMSSERVICESMGRPROVIDER_H