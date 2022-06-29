/**
 * \file
 *          IWifiRemoteServiceTypes.h
 * \brief
 *          Data types to be used within remote Wi-Fi service interaction
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
 
#ifndef IWIFIREMOTESERVICETYPES_H
#define IWIFIREMOTESERVICETYPES_H

#include "Poco/Types.h"
#include <vector>
#include <string>

using namespace std;


/**
 * @brief WiFiServerIF_802_11_PhyStandard_e: Technology revission given by IEEE standard in WiFi communication protocol
 */
 //@serialize
enum WiFiServerIF_802_11_PhyStandard_e
{
    WIFI_SERVER_STD_IEEE80211_UNKNOWN,              /**< Unknown WiFi standard protocol */
    WIFI_SERVER_STD_IEEE80211_MODE_B,               /**< Compatible with B 802.11 protocol mode */
    WIFI_SERVER_STD_IEEE80211_MODE_BG,              /**< Compatible with B and G 802.11 protocol modes */
    WIFI_SERVER_STD_IEEE80211_MODE_BGN,             /**< Compatible with B, G and N 802.11 protocol modes */
    WIFI_SERVER_STD_IEEE80211_MODE_A,               /**< Compatible with A 802.11 protocol mode */
    WIFI_SERVER_STD_IEEE80211_MODE_AN,              /**< Compatible with A and N 802.11 protocol modes */
    WIFI_SERVER_STD_IEEE80211_MODE_ANAC             /*!< Compatible with A, N and AC 802.11 protocol modes */
};

/**
 * @brief WiFiServerIF_ErrorCodes: Error code definition from the
 */
 //@serialize
enum WiFiServerIF_ErrorCodes
{
    WIFI_SERVER_RES_OK,
    WIFI_SERVER_RES_ERR,
    WIFI_SERVER_RES_NOT_INI,
    WIFI_SERVER_RES_ERR_WIFIMGR_NOT_READY,
    WIFI_SERVER_RES_ERR_CLIENT_NOT_READY,
    WIFI_SERVER_RES_ERR_CLIENT_NOT_ENABLED,
};

/**
 * @brief WiFiServerIF_ServiceState_e: Depicts the actual state of the WiFi network Service
 */
 //@serialize
enum WiFiServerIF_ServiceState_e
{
    WIFI_SERVER_STATE_CONNECTING,
    WIFI_SERVER_STATE_CONNECTED,
    WIFI_SERVER_STATE_DISCONNECTING,
    WIFI_SERVER_STATE_DISCONNECTED,
    WIFI_SERVER_STATE_FAILURE
};

/**
 * @brief WiFiServerSecurity_e: Indicates type of security encryption employed on a WiFi network connection
 */
 //@serialize
enum WiFiServerSecurity_e
{
    WIFI_SERVER_SECURITYLEVEL_NONE,
    WIFI_SERVER_SECURITYLEVEL_WPA_PSK,
    WIFI_SERVER_SECURITYLEVEL_WPA_EAP,
    WIFI_SERVER_SECURITYLEVEL_WPA2_WPS,
    WIFI_SERVER_SECURITYLEVEL_WPA2_PSK,
    WIFI_SERVER_SECURITYLEVEL_WPA2_EAP,
    WIFI_SERVER_SECURITYLEVEL_WEP
};

/**
 * @brief WiFiServerNetState_e: Type of service carried on current WiFi network connection
 */
 //@serialize
enum WiFiServerNetState_e
{
    TCU_STATE_OFF,                     /**< WiFi Network conneciton is off */
    TCU_STATE_ENABLING_STA,            /**< WiFi client is in enabling state */
    TCU_STATE_ENABLING_AP,             /**< WiFi access point is in enabling state. This value is not applicable for ATB4S product. */
    TCU_STATE_ENABLED_STA,             /**< WiFi client is successfully enabled */
    TCU_STATE_ENABLED_AP,              /**< WiFi access point is successfully enabled. This value is not applicable for ATB4S product*/
    TCU_STATE_DISABLING,               /**< WiFi connectivity is in disabling state */
    TCU_STATE_RECOVERING,              /**< WiFi connectivity is in recovering state */
    TCU_STATE_FAILURE,                 /**< WiFi connectivity is in failure state */
    TCU_STATE_LAST                     /**< Default state*/
};

/**
 * @brief WifiServerServiceConfig: Attributes definition for given WiFi service
 */
struct WifiServerServiceConfig
{
    std::string ssid;                                       /*!< Network name : Service Set Identifier. This is applicable for client and non client mode */

    unsigned int rssi;                                      /*!< Signal strength indicator. This is applicable only for client mode */

    unsigned int channel;                                   /*!< WiFi frequency channel. This is applicable only for client mode */

    std::string cipher;                                     /*!< WiFi encryption type. This is applicable only for client mode */

    std::string mac;                                        /*!< MAC Address. This is applicable for client and non client mode */

    WiFiServerIF_802_11_PhyStandard_e IEE_802_11_mode;      /*!< WiFi protocol standard revision. This is applicable only for client mode */

    WiFiServerIF_ServiceState_e connection_status;          /*!< WiFi Connection status. This is applicable only for client mode */

    WiFiServerSecurity_e securityMode;                      /*!< WiFi Security protocol. This is applicable only for client mode */
};

/**
 * @brief WifiServerServiceList: WiFi service data record
 */
struct WifiServerServiceList
{
    vector<WifiServerServiceConfig> wifiRemoteServices;

    unsigned int services_num;
};

/**
 * @brief WifiServerStatus: WiFi service status data
 */
struct WifiServerStatus
{
    WiFiServerIF_ServiceState_e connectionStatus;
    WiFiServerNetState_e mode;
};


#endif // IWIFIREMOTESERVICETYPES_H
