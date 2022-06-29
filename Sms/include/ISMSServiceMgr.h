/**
 * \file
 *          ISMSServiceMgr.h
 * \brief
 *          Interface of SMS Service Manager for Applications to send and receive messages.
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
 
#ifndef ISMSSERVICESMGR_H
#define ISMSSERVICESMGR_H

#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Service.h"
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"
#include "Poco/RefCountedObject.h"

#include "ISMSServiceMgrTypes.h"

using Poco::BasicEvent;

namespace Stla {
namespace Connectivity {
        /**
         * @brief Interface of the SMS Manager Service - Provides Send and receive functionality
         */
        #ifdef DOXYGEN_WORKING
        class ISMSServiceMgr:public Poco::RefCountedObject
        #else
        class __attribute__((visibility("default"))) ISMSServiceMgr:public Poco::RefCountedObject
        #endif
        {
        public:

            /**
            * \brief SMSGetMsg: Interface to trigger message forwarding for the requesting App.
            *
            * \param [in] AppName: Application name for which pending messages will be forwarded.
            * \return enSMSReturn_t: SMS_RET_SUCCESS - correct execution, otherwise an error occured.
            *
            * \pre : Client app is registered for SMS service, client app delegated a valid function for
            * \post : After a successful call, SMS manager will start forwarding pending messages to the client App. By triggering smsMsgReceived event.
            * \msc
            * hscale="1.5";
            * psaapp [label=""],
            * srvbase [label=""],
            * srvmgr [label=""],
            * smsremote [label=""];
            * psaapp box psaapp [label="ClientApp"],
            * srvbase box srvbase [label="SMSServiceBase"],
            * srvmgr box srvmgr [label="SMSServicesMgr"],
            * smsremote box smsremote [label="ISmsServices"];
            * |||;
            * psaapp note smsremote [label="SMSRegister"];
            * |||;
            * ---[label="if (poSMSMgr != null)", linecolor="#E09024"];
            * psaapp => srvmgr[label="SMSGetMsg(AppName)"];
            * ---[label="if (AppName is registered as Client)", linecolor="#7f7fff"];
            * srvmgr => smsremote[label="getMsg4client(SMS_SRV_APPFWK)"];
            * smsremote box smsremote [label="Forward pending messages "];
            * srvmgr >> psaapp[label="SMS_RET_SUCCESS"];
            * ---[label="else", linecolor="#7f7fff"];
            * srvmgr >> psaapp[label="SMS_RET_CLIENT_REG_ERROR"];
            * ---[label="", linecolor="#7f7fff"];
            * ---[label="", linecolor="#E09024"];
            * psaapp note smsremote [label="SMSReceive"];
            * |||;
            * \endmsc
            * \link smsMsgReceived \endlink
            * \note Use this interface after registering and having delegated a function for the SMS reception event.
            */
            virtual enReturnSMS_t SMSGetMsg(std::string AppName) = 0;

            /**
            * \brief SMSSend: Interface to send SMS msg from client App.
            *
            * \param [in] stSmsSend_data: structure with message data to send.
            * \return enSMSReturn_t: SMS_RET_SUCCESS - correct execution, otherwise an error occured.
            *
            * \pre : Client provides SMS send data structure with valid payload and phone destination address
            * \post : SMS Manager will attempt the delivery of the message, using the Encoding format configured in the system, and will report the status of the operation with event smsSendStatus.
            * \msc
            * hscale="2";
            * psaapp [label=""],
            * srvbase [label=""],
            * srvmgr [label=""],
            * smsremote [label=""];
            * psaapp box psaapp [label="ClientApp"],
            * srvbase box srvbase [label="SMSServiceBase"],
            * srvmgr box srvmgr [label="SMSServicesMgr"],
            * smsremote box smsremote [label="ISmsServices"];
            * |||;
            * psaapp note srvmgr [label="SMSRegister"];
            * |||;
            * psaapp => srvmgr[label="SMSSend(stSMSSendData_t)"];
            * srvmgr => smsremote[label="smsSend(stSMSSendData_t)"];
            * smsremote box smsremote [label="Send SMS"];
            * ---[label="Successful Request", linecolor="#7f7fff", textcolor="#7f7fff"];
            * smsremote >> srvmgr[label="SMS_RET_SUCCESS"];
            * srvmgr >> psaapp[label="SMS_RET_SUCCESS"];
            * ---[label="else", linecolor="#7f7fff", textcolor="#7f7fff"];
            * smsremote >> srvmgr[label="SMS_RET_INVALID_ARGUMENT"];
            * srvmgr >> psaapp[label="SMS_RET_INVALID_ARGUMENT"];
            * ---[label="", linecolor="#7f7fff", textcolor="#7f7fff"];
            * |||;
            * smsremote =>> srvbase[label="smsAPPFWKMsgSendEvent.notifyAsync(this,pstSmsSendData)"];
            * ---[label="App for sent message found", linecolor="#00AAAA" ];
            * srvbase box srvbase [label="stSMSSendData_t smsSendDataEx = convert(pstSmsSendData);"];
            * srvbase =>> srvmgr[label="smsSendStatus.notify(stSMSSendData_t)"];
            * srvmgr =>> psaapp[label="onSendStatus(stSMSSendData_t)"];
            * ---[label="", linecolor="#00AAAA" ];
            * \endmsc
            * \link smsSendStatus \endlink
            * \note Due to network status reports, it is recommended to send messages one by one.
            */
            virtual enReturnSMS_t SMSSend(stSMSDataSend_t& stSmsSend_data) = 0;

            /**
            * \brief  SMSAckMsg: Interface to acknowledge the reception of a SMS from client apps.
            * \param [in] msgID - Message Id to acknowledge. Use the ID from received message, contained in event data stSMSDataRec_t.
            * \return enSMSReturn_t: SMS_RET_SUCCESS - correct execution, otherwise an error occured.
            *
            * \pre : A message was notified for the app with event smsMsgReceived
            * \post : If the acknowledged message ID is valid, the message will be deleted from storage.
            * \msc
            * hscale="1.5";
            * psaapp [label=""],
            * srvbase [label=""],
            * srvmgr [label=""],
            * smsremote [label=""],
            * platf [label=""];
            * psaapp box psaapp [label="ClientApp"],
            * srvbase box srvbase [label="SMSServiceBase"],
            * srvmgr box srvmgr [label="SMSServicesMgr"],
            * smsremote box smsremote [label="ISmsServices"],
            * platf box platf [label="NAD"];
            * |||;
            * platf =>> smsremote [label="onNadIfSMSRead"];
            * smsremote box smsremote [label="parse PSA header and validate SMS"];
            * ---[label="message is valid and ServiceType == AppFwk", linecolor="#00AAAA" ];
            * smsremote =>> srvbase [label="onsmsAPPFWKMsgEvent(this, stSMSData_t)"];
            * srvbase box srvbase [label="parse message content and validate AppName"];
            * ---[label="AppName is a client", linecolor="#EEAA00" ];
            * srvbase =>> srvmgr[label="smsMsgReceived.notifyAsync(stSMSData_t)"];
            * srvmgr =>> psaapp[label="onReceivedSMS(stSMSData_t)"];
            * psaapp box psaapp [label="Process message"];
            * psaapp => srvmgr[label="SMSAckMsg(msgID)"];
            * srvmgr => smsremote[label="smsAckMsg(msgID)"];
            * smsremote box platf [label="Delete SMS"];
            * ---[label="Successful ACK", linecolor="#7f7fff", textcolor="#7f7fff"];
            * smsremote >> srvmgr[label="SMS_RET_SUCCESS"];
            * srvmgr >> psaapp[label="SMS_RET_SUCCESS"];
            * ---[label="else", linecolor="#7f7fff", textcolor="#7f7fff"];
            * smsremote >> srvmgr[label="SMS_RET_INVALID_ARGUMENT"];
            * srvmgr >> psaapp[label="SMS_RET_INVALID_ARGUMENT"];
            * ---[label="", linecolor="#7f7fff", textcolor="#7f7fff"];
            * ---[label="else", linecolor="#EEAA00" ];
            * srvbase box smsremote [label="keep message stored"];
            * ---[label="", linecolor="#EEAA00" ];
            * ---[label="", linecolor="#00AAAA" ];
            * |||;
            * \endmsc
            * \link smsMsgReceived \endlink.
            */
            virtual enReturnSMS_t SMSAckMsg(uint16_t msgID) = 0;

            /**
            * \brief smsMsgReceived: Event used to notify about incoming messages.
            * \note Event includes all data of the SMS in struct stSMSDataRec_t.
            *  Client needs to delegate a function to handle this event.
            */
            Poco::BasicEvent<stSMSDataRec_t> smsMsgReceived;

            /**
            * \brief smsSendStatus: Event used to notify the delivery status of outgoing messages.
            * \note Status and payload included in event in struct stSMSDataSend_t.
            *  Client needs to delegate a function to handle this event.
            */
            Poco::BasicEvent<stSMSDataSend_t> smsSendStatus;

            /**
            @brief  Ptr is an auto pointer of ISMSServiceMgr class service
            */
            typedef Poco::AutoPtr<ISMSServiceMgr> Ptr;

        };
    }
}
#endif //ISMSSERVICESMGR_H