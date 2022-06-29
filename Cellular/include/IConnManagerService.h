/**
 * \file
 *         IConnManagerService.h
 * \brief
 *         IConnManagerService is the interface that provides information about Connection Manager
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

#ifndef ICONNMANAGERSERVICE_H
#define ICONNMANAGERSERVICE_H

#include "IConnManagerServiceTypes.h"
#include "Poco/BasicEvent.h"
#include "Poco/OSP/Service.h"

namespace Stla {
namespace Connectivity {

/**
 * @brief Connection Manager Service name used in OSP
 */
const char* const CONNMANAGER_SERVICE_NAME = "stla.connectivity.connmanager.service.base";

/**
 * IConnManagerService is the interface that provides information about Connection Manager
 */
#ifdef DOXYGEN_WORKING
class IConnManagerService : public Poco::OSP::Service
#else
class __attribute__((visibility("default"))) IConnManagerService : public Poco::OSP::Service
#endif

{
public:
    /**
     * @brief Class smart pointer definition
     */
    typedef Poco::AutoPtr<IConnManagerService> Ptr;

    /**
     * IConnManagerService destructor
     */
    virtual ~IConnManagerService() {};

    /**
     * @brief	Returns the service information for the object's class.
     */

    const std::type_info& type() const
    {
        return typeid(IConnManagerService);
    }

    /**
     * @brief	Returns true if the class is a subclass of the class given by obj.
     */

    bool isA(const std::type_info& obj) const
    {
        std::string name(type().name());
        return name == obj.name();
    }

    /**
     * @brief Poco Event triggered when cellular network type is available or when it changes
     *
     */
    Poco::BasicEvent<const ConMgrNetworkType> onCellularNetworkTypeChanged;

    /**
     * @brief Getter for cellular network type
     *
     * @param [out] result Network type as \link ConMgrNetworkType \endlink
     *
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getCellularNetworkType(ConMgrNetworkType& result) = 0;

    /**
     * @brief Poco Event triggered when cellular APN connection state changes
     *
     * The structure has the following fields:
     * - interface Name of the interface: ApnName_Telematic or ApnName_Public
     * - available Status of the connection: true if connected, false if not connected
     */
    Poco::BasicEvent<const APNConnState> onApnConStateChanged;

    /**
     * @brief Getter for cellular APN connection state
     *
     * @param[in] interface Name of the interface to be checked
     *            Possible values:
     *            - ApnName_Telematic
     *            - ApnName_Public
     * @param[out] result Connection state of APN
     *            true if Connected
     *            false if Not connected
     *
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getApnConState(ConApnName interface, bool& result) = 0;

    /**
     * @brief Poco Event triggered when cellular mobile country code (MCC) is available
     * or when it changes (e.g. crossing the border)
     */
    Poco::BasicEvent<const int> onCellularMCCChanged;

    /**
     * @brief Getter for cellular cellular mobile country code (MCC)
     *
     * @param[out] result Integer value of the MCC
     *
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getCellularMCC(int& result) = 0;

    /**
     * @brief Poco Event triggered when wifi data connection state changes
     *
     * Values are:
     * - true if connected
     * - false if not connected
     */
    Poco::BasicEvent<const bool> onWifiDataConStateChanged;

    /**
     * @brief Getter for wifi data connection state
     *
     * @param[out] result Connection state of WiFi
     *            true if Connected
     *            false if Not connected
     *
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getWiFiDataConState(bool& result) = 0;

    /**
     * @brief Poco Event triggered when cellular signal strength is available and when the value changes
     * moving from one Range to another.
     *
     * Example: For signal strength values 35, 32, 33, 29, 20 (in this order for an LTE network)
     * events will be triggered only when this values are received: 35, 32, 20
     *
     * The information contained in the event is the RSSI value
     * Range from 0 to 100 with 255 as error value.
     *
     *
     *
     * Ranges for each network type are listed below
    <table>
    <tr><th>Range depending on Network type
    <tr><th>Range    <th>GSM   <th>WCDMA      <th>LTE-4G
    <tr><td>Excellent <td>>= 64 <td>>=42 <td>>=34
    <tr><td>Good <td>40 to 63 <td>30 to 41 <td>26 to 33
    <tr><td>Fair <td>18 to 39 <td>18 to 29 <td>9 to 25
    <tr><td>Poor <td><= 17 <td><= 17 <td><= 8
    <tr><td>Lost <td>0 <td>0 <td>0
    </table>
     *
     */
    Poco::BasicEvent<const unsigned char> onCellularSignalStrengthChanged;

    /**
     * @brief Getter for cellular signal strength
     *
     * @param[out] result Signal strength as RSSI of the cellular network
     * Values range from 0 to 100 with 255 as error value.
     *
     * Ranges for each network type are listed below
    <table>
    <tr><th>Range depending on Network type
    <tr><th>Range    <th>GSM   <th>WCDMA      <th>LTE-4G
    <tr><td>Excellent <td>>= 64 <td>>=42 <td>>=34
    <tr><td>Good <td>40 to 63 <td>30 to 41 <td>26 to 33
    <tr><td>Fair <td>18 to 39 <td>18 to 29 <td>9 to 25
    <tr><td>Poor <td><= 17 <td><= 17 <td><= 8
    <tr><td>Lost <td>0 <td>0 <td>0
    </table>
     *
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getCellularSignalStrength(unsigned char& result) = 0;

    /**
     * @brief Poco Event triggered when cellular modem availability changes
     */
    Poco::BasicEvent<const bool> onCellularModemAvailabilityChanged;

    /**
     * @brief Getter for cellular modem availability
     *
     * @param[out] result Cellular modem availability
     *            true if Modem available
     *            false if Modem not available
     *
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getCellularModemAvailability(bool& result) = 0;

    /**
     * @brief Poco Event triggered when gsm metrics are available or when they change
     *
     *  The structure has the following fields:
     * -The Received Signal Strength Indicator (RSSI).
     * -The Bit Error Rate (BER).
     */
    Poco::BasicEvent<const GsmMetrics> onGsmMetrics;

    /**
     * @brief Getter for Gsm Metrics
     * @param [out] result Gsm metrics as \link GsmMetrics \endlink
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getGsmMetrics(GsmMetrics& result) = 0;

    /**
     * @brief Poco Event triggered when umts metrics are available or when they change
     *
     *  The structure has the following fields:
     * -The Received Signal Strength Indicator (RSSI).
     * -The measured Received Signal Code Power (RSCP).
     * -EC/IO. This is the measure of the quality/cleanliness of the signal from the tower to the modem and indicates the signal-to noise ratio.
     */
    Poco::BasicEvent<const UmtsMetrics> onUmtsMetrics;

    /**
     * @brief Getter for Umts Metrics
     * @param [out] result Umts metrics as \link UmtsMetrics \endlink
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getUmtsMetrics(UmtsMetrics& result) = 0;

    /**
     * @brief Poco Event triggered when lte metrics are available or when they change
     *
     *  The structure has the following fields:
     * -The Received Signal Strength Indicator (RSSI).
     * -The measured Reference Signal Received Quality (RSRQ).
     * -The measured Reference Signal Received Power (RSRP).
     * -The Signal to Noise Ratio (SNR).
     */
    Poco::BasicEvent<const LteMetrics> onLteMetrics;

    /**
     * @brief Getter for Lte Metrics
     * @param [out] result Lte metrics as \link LteMetrics \endlink
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getLteMetrics(LteMetrics& result) = 0;

    /**
     * @brief Poco Event triggered when cellular neighboring cells are available or when they change
     * Provides the number of neighbor cells per technology (gsm, umts and lte).
     */
    Poco::BasicEvent<const CellularNbCells> onCellularNbCellsChanged;

    /**
     * @brief Getter for Cellular neighboring cells
     * @param [out] result Cellular neighboring cells as \link CellularNbCells \endlink
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getCellularNbCells(CellularNbCells& result) = 0;

    /**
     * @brief Poco Event triggered when registration status is available or when it changes
     *
     *  The structure has the following fields:
     * -Mobile Network Code (MNC).
     * -Mobile Country Code (MCC).
     * -Network type (GSM, UMTS, LTE, ...).
     * -Network name.
     * -Registration to the cellular circuit switch.
     * -Registration to the cellular packet switch.
     * -Cell Identifier
     * -Tracking area code
     * -Local area code
     */
    Poco::BasicEvent<const RegistrationStatus> onRegistrationStatusChanged;

    /**
     * @brief Getter for Registration status
     * @param [out] result Registration status as \link RegistrationStatus \endlink
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getRegistrationStatus(RegistrationStatus& result) = 0;

    /**
     * @brief Poco Event triggered every 5 minutes
     *
     *  The structure has the following fields:
     * - Universal time.
     * - Local time zone.
     * - Daylight saving time.
     */
    Poco::BasicEvent<const DateTime> onCellularTime;

    /**
     * @brief Getter for Cellular time
     * @param [out] result Cellular time as \link DateTime \endlink
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getCellularTime(DateTime& result) = 0;

    /**
     * @brief Getter for System time
     * @param [out] result System time as time_t
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getSystemTime(time_t& result) = 0;

    /**
     * @brief Poco Event triggered when data path changes
     */
    Poco::BasicEvent<const std::string> onDataPathChanged;

    /**
     * @brief Getter for data path mode
     *
     * @param[out] result current data path "no data", "cellular", "wifi"
     *
     * @return Error number described in \link ConMgrErrno \endlink.
     */
    virtual ConMgrErrno getDataPath(std::string& result) = 0;

    /**
    * @brief Setter GarageBoxMode enable
    * @param[in] TRUE - GarageBoxMode is enabled
    *            FALSE - GarageBoxMode is stoped
    * @return error code, CONN_MGR_INFO_ERR_OK on success.
    */
    virtual ConMgrErrno setGarageBoxMode(bool isGarageBox) = 0;

    /**
    * @brief Getter GarageBoxMode enable
    * @param[in] TRUE - Data connection allowed
    *            FALSE - Data connection not allowed
    * @return error code, CONN_MGR_INFO_ERR_OK on success.
    */
    virtual ConMgrErrno  getGarageBoxMode(bool& isDataAllowed) = 0;
};
}
}

#endif // ICONNMANAGERSERVICE_H
