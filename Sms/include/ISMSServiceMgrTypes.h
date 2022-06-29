/**
 * \file 
 *  ISMSServiceMgrTypes.h
 *
 * \brief
 *   Interface Types of SMS Services
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

#ifndef ISMSSERVICESMGRTYPES_H
#define ISMSSERVICESMGRTYPES_H

/**
 *@brief SMS_MGR_MAX_DATA_LEN - Define the max number of Data bytes for SMS message.
 */
#define SMS_MGR_MAX_DATA_LEN 161
/**
 *@brief SMS_MGR_MAX_ADDR_LEN - Define the max number of Data bytes for phone number.
 */
#define SMS_MGR_MAX_ADDR_LEN 33


/**
 * \brief enReturnSMS_t: Return values for SMS manager
 *
 */
 //@serialize
enum enReturnSMS_t
{
    SMS_MGR_RET_SUCCESS,                 /*!< Operation executed successfully */
    SMS_MGR_RET_CLIENT_REG_ERROR,        /*!< Registration error */
    SMS_MGR_RET_INVALID_HEADER,          /*!< Incoming SMS doesn't have a valid PSA header */
    SMS_MGR_RET_NO_NETWORK,              /*!< Network is not available at the moment */
    SMS_MGR_RET_SIM_FAILURE,             /*!< SIM is not detected or not functional */
    SMS_MGR_RET_CORRUPTED,               /*!< Message is corrupted */
    SMS_MGR_RET_SERVICE_NOT_AVAILABLE,   /*!< SMS manager is not available */
    SMS_MGR_RET_INVALID_ARGUMENT,        /*!< Request was performed with an incorrect parameter */
    SMS_MGR_RET_UNKNWON_ERROR            /*!< Operation failed due to unknown reason */
};

/**
 * \brief enECUSMS_t: ECUs that can send or receive a SMS
 *
 */
 //@serialize
enum enECUSMS_t
{
    SMS_MGR_ECU_TCU, /*!< TCU unit */
    SMS_MGR_ECU_IVI,  /*!< IVI HU unit */
    SMS_MGR_ECU_LAST  /*!< Invalid ECU value */
};

/**
 * @brief  enServiceSMS_t: Possible service types for the SMS messages
 *
 */
 //@serialize
enum enServiceSMS_t
{
    SMS_MGR_SRV_GENERIC = 0,  /*!< Service type: Generic */
    SMS_MGR_SRV_ACALL,        /*!< Service type: Assistance Call */
    SMS_MGR_SRV_ECALL,        /*!< Service type: Emergency Call */
    SMS_MGR_SRV_LC,           /*!< Service type: Life cycle */
    SMS_MGR_SRV_DM,           /*!< Service type: Device Manager */
    SMS_MGR_SRV_APPFWK,       /*!< Service type: Application Framework */
    SMS_MGR_SRV_RMS,          /*!< Service type: Remote Monitoring Service */
    SMS_MGR_SRV_UNKNOWN,      /*!< Service type is not defined in the message */
    SMS_MGR_SRV_LAST          /*!< Invalid service type */
};

/**
 * @brief enObjTypeSMS_t: Possible object types available in PSA specs for SMS service
 *
 */
 //@serialize
enum enObjTypeSMS_t
{
    SMS_MGR_OT_WU          = 0,  /*!< LC Object Type - Wake up request */
    SMS_MGR_OT_GP          = 0,  /*!< AppFrmk Object Type - General purpose binary object */
    SMS_MGR_OT_RU          = 0,  /*!< Dev Management Service Object Type - Registration Update */
    SMS_MGR_OT_MSG_REQ     = 0,  /*!< ACall & ECall Object Type - Message Request  */
    SMS_MGR_OT_MSG1        = 1,  /*!< ACall & ECall Object Type - Message 1 */
    SMS_MGR_OT_MSG2        = 2,  /*!< ACall & ECall Object Type - Message 2 */
    SMS_MGR_OT_STOP        = 3,  /*!< ACall Object Type - Stopped procedure */
    SMS_MGR_OT_UNKNOWN     = 4,  /*!< Unknown Object Type */
    SMS_MGR_OT_LAST        = 5   /*!< Invalid Object type  */
};
/**
 * @brief enStatusSMS_t: SMS message status
 *
 */
 //@serialize
enum enStatusSMS_t
{
    SMS_MGR_ST_UNREAD,       /*!< Unread incoming message */
    SMS_MGR_ST_READ,         /*!< Read incoming message */
    SMS_MGR_ST_UNSENT,       /*!< Outgoing message not sent */
    SMS_MGR_ST_SENT,         /*!< Outgoing message sent */
    SMS_MGR_ST_DELETED,      /*!< Stored message was deleted */
    SMS_MGR_ST_NOTDELETED,   /*!< Stored message deletion failed */
    SMS_MGR_ST_LAST          /*!< Invalid message status */
};

/**
 * @brief enFormatSMS_t: SMS message format
 *
 */
 //@serialize
enum enFormatSMS_t
{
    SMS_MGR_FR_UNKNOWN,  /*!< Unknown message format */
    SMS_MGR_FR_RAW,      /*!< Raw message */
    SMS_MGR_FR_TEXT,     /*!< GSM 7-bit default alphabet*/
    SMS_MGR_FR_UCTEXT,   /*!< UCS-2 text encoding 16 bit per char*/
    SMS_MGR_FR_BINARY,   /*!< Binary format */
    SMS_MGR_FR_LAST      /*!< Invalid format value */
};

/**
 * @brief stSMSDataRec_t: SMS data for incoming message information
 *
 */
struct stSMSDataRec_t
{
    uint16_t      msgID;                        /*!< Id for incoming message, used to acknowledge reception */
    uint8_t       size;                         /*!< Size of received message, valid info inside data */
    uint8_t       data[SMS_MGR_MAX_DATA_LEN];   /*!< Payload of SMS message containing the PSA header*/

    /*Parsed data of PSA header*/
    enECUSMS_t     ECUType;                     /*!< Message ECU type */
    enServiceSMS_t serviceType;                 /*!< Message Service type */
    enObjTypeSMS_t objType;                     /*!< Message object type */
    uint8_t        objVersion;                  /*!< Message object version */
    uint8_t        objID;                       /*!< Message object id */

    enFormatSMS_t format;                       /*!< Format of the message */
    char phone[SMS_MGR_MAX_ADDR_LEN];           /*!< Source phone address */
};

/**
 * @brief stSMSDataSend_t: SMS data for outgoing message information
 *
 */
struct stSMSDataSend_t
{
     uint8_t       data[SMS_MGR_MAX_DATA_LEN];   /*!< input payload for outgoing message provided by client and forwarded by SMS mgr */
     uint8_t       size;                         /*!< Size of the outgoing message, valid info inside data */
     char          phone[SMS_MGR_MAX_ADDR_LEN];  /*!< Destination phone address provided by client */
     enStatusSMS_t status;                       /*!< Delivery status, used in send status stage managed by SMS mgr */
};

#endif //ISMSSERVICESMGRTYPES_H