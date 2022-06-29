/**
 * \file
 *         IConnManagerServiceTypes.h
 * \brief
 *         Interface file for common types for IConnManagerService
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
 
#ifndef ICONNMANAGERSERVICETYPES_H
#define ICONNMANAGERSERVICETYPES_H

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#define MAX_NETWORK_NAME_LEN 30 /*Maximum length of the network_name, including the NULL*/
#define MAX_CID_LEN 16          /*Maximum length of the CID field, including the NULL*/
#define MAX_LAC_LEN 5           /*Maximum length of the LAC field, including the NULL*/

using namespace std;


namespace Stla {
namespace Connectivity {

/**
 * \brief The ConApnName defines different apn interface.
 */
//@serialize
enum ConApnName
{
    ApnName_Public = 0, /**< Name of the public apn interface */
    ApnName_Telematic   /**< Name of the telematic apn interface */
};

/**
 * @brief Structure contains information about the state of APN
 * - interface Name of the interface
 *   Values can be
 *   - ApnName_Public
 *   - ApnName_Telematic
 * - available Status of the interface
 *   Values can be
 *   - true Connected
 *   - false Not connected
 */
#ifdef DOXYGEN_WORKING
struct APNConnectionState_s
#else
struct __attribute__((visibility("default"))) APNConnectionState_s
#endif
{
    ConApnName interface; //<< Name of the apn interface as enum
    bool available;   //<< Availability of the interface (connected/not connected)
};

/**
 * @brief APNConnState defines the type for the APN Connection State
 */
typedef APNConnectionState_s APNConnState;
/**
 * \brief The ConMgrErrno defines different Error types.
 */
//@serialize
enum ConMgrErrno
{
    ConMgrErr_OK = 0,              /**<  No error */
    ConMgrErr_Fail,                /**< Failure, internal error */
    ConMgrErr_InvalidArgument,     /**< Invalid argument received */
    ConMgrErr_UnavailableService,  /**< Service is unavailablee */
    ConMgrErr_Last                 /**< Guard, add errors before this line */
};
/**
 * \brief The ConMgrNetworkType defines different type of network.
 */
//@serialize
enum ConMgrNetworkType
{
    ConMgrNtwType_Unknown = 0,   /**< unknown   The type of nework is unknown */
    ConMgrNtwType_GSM,           /**< GSM       NADIF network type is 2G/GPRS/EDGE */
    ConMgrNtwType_WCDMA,         /**< WCDMA     NADIF network type is 3G/UMTS */
    ConMgrNtwType_LTE,           /**<  LTE       NADIF network type is 4G/LTE */
    ConMgrNtwType_CDMA_1X,       /**< CDMA_1X   NADIF network type is 2G/CDMA */
    ConMgrNtwType_CDMA_EVDO      /**< CDMA_EVDO NADIF network type is 2G/CDMA EVDO */
};

/**
 * \brief The ConMgrRegistrationStatus defines Registration Status.
 */
//@serialize

enum ConMgrRegistrationStatus
{
    NADIF_REG_STAT_UNKNOWN = 0,         /**< Not Registered, Unknown reason */
    NADIF_REG_STAT_NOT_REGISTERED,      /**< Not Registered, Not Searching */
    NADIF_REG_STAT_REGISTERED,          /**< Registered on a network */
    NADIF_REG_STAT_LIMITED,             /**< Limited service */
    NADIF_REG_STAT_REGISTERED_ROAMING,  /**< Registered on a Roaming network */
    NADIF_REG_STAT_CAMPED               /**< Camped on a network */
};

/**
 * @brief Structure contains information about Gsm metrics:
 * - raw_rssi (The Received Signal Strength Indicator)
 * - bler (The Bit Error Rate)
 */
struct GsmMetrics
{
    signed char raw_rssi;
    unsigned char bler;
    GsmMetrics(): raw_rssi(0xFF),  bler(99){}
};

/**
 * @brief Structure contains information about Umts metrics:
 * - raw_rssi (The Received Signal Strength Indicator)
 * - rscp (The measured Received Signal Code Power)
 * - ecio (This is the measure of the quality/cleanliness of the signal from the tower to the modem and indicates the signal-to noise ratio.)
 * - bler (The Block Error Rate)
 */
struct UmtsMetrics
{
    signed char raw_rssi;
    short int rscp;
    short int ecio;
    unsigned short int bler;
    UmtsMetrics(): raw_rssi(0xFF), rscp(0), ecio(0x7FFF), bler(0xFFFF){}
};

/**
 * @brief Structure contains information about Lte metrics:
 * - raw_rssi (The Received Signal Strength Indicator)
 * - rsrq (The measured Reference Signal Received Quality)
 * - rsrp (The measured Reference Signal Received Power)
 * - snr (The Signal to Noise Ratio)
 */
struct LteMetrics
{
    signed char raw_rssi;
    signed char rsrq;
    short int rsrp;
    short int snr;
    LteMetrics(): raw_rssi(0xFF), rsrq(0x7F), rsrp(0), snr(0x7FFF){}
};

/**
 * @brief Structure contains information about number of Cellular neighboring cells:
 * - num_gsm_cells (Number of neighboring GSM cells)
 * - num_wcdma_cells (Number of neighboring WCDMA cells)
 * - num_lte_cells (Number of neighboring LTE cells)
 */
struct CellularNbCells
{
    unsigned char num_gsm_cells;
    unsigned char num_wcdma_cells;
    unsigned char num_lte_cells;
    CellularNbCells(): num_gsm_cells(0), num_wcdma_cells(0), num_lte_cells(0){}
};

/**
 * @brief Structure contains information about Registration status:
 * - mnc (Mobile Network Code)
 * - mcc (Mobile Country Code)
 * - network_type (Network type (GSM, UMTS, LTE, ...))
 * - network_name (Network name)
 * - cs_reg_status (Registration to the cellular circuit switch)
 * - ps_reg_status (Registration to the cellular packet switch)
 * - cid (Cell Identifier)
 * - tac (Tracking area code)
 * - lac (Local area code)
 */
struct RegistrationStatus
{
    unsigned short int mnc;
    unsigned short int mcc;
    ConMgrNetworkType network_type;
    char network_name[MAX_NETWORK_NAME_LEN];
    ConMgrRegistrationStatus cs_reg_status;
    ConMgrRegistrationStatus ps_reg_status;
    char cid[MAX_CID_LEN];
    unsigned short int tac;
    char lac[MAX_LAC_LEN];
    RegistrationStatus(): mnc(0xFFFF), mcc(0xFFFF), network_type(ConMgrNtwType_Unknown), cs_reg_status(NADIF_REG_STAT_UNKNOWN), ps_reg_status(NADIF_REG_STAT_UNKNOWN), tac(0xFFFF)
    {
        static char const default_network_name[] = "                             ";
        static char const default_cid[] = "               ";
        static char const default_lac[] = "    ";
        assert( strlen( default_network_name ) < MAX_NETWORK_NAME_LEN );
        assert( strlen( default_cid ) < MAX_CID_LEN );
        assert( strlen( default_lac ) < MAX_LAC_LEN );
        strcpy( network_name, default_network_name );
        strcpy( cid, default_cid );
        strcpy( lac, default_lac );
    }
};

/**
 * @brief Structure contains information about Date time:
 * - local_time (Universal time)
 * - timezone (Local time zone)
 * - daylt_sav (Daylight saving time)
 * - offset (difference between system_time and local_time)
 */
struct DateTime
{
    time_t local_time;
    unsigned char timezone;
    unsigned char daylt_sav;
    int offset;
    DateTime(): local_time(0), timezone(0), daylt_sav(0xFF), offset(0) {}
};

}
}

#endif
