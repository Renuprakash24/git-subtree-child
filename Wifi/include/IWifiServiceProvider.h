/**
 * \file
 *          IWifiServiceProvider.h
 * \brief
 *          Interface in charge to provide WiFi services and their status to external applications
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

/* To do : Testing purpose */

#ifndef IWIFISERVICERPROVIDER_H
#define IWIFISERVICERPROVIDER_H

#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Service.h"
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"
#include "IWifiRemoteServiceTypes.h"

#define WIFI_SRV_BASE_BUNDLE_NAME "stla.connectivity.wifi.service.base"

using Poco::BasicEvent;

namespace Stla {
namespace Connectivity {


class IWifiServiceProvider : public Poco::OSP::Service
{
public:

    /**
     * @brief   Returns the service information for the object's class.
     */
    const std::type_info& type() const
    {
        return typeid (IWifiServiceProvider);
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
    * \brief getWifiServices: Interface to request the avialable Wi-Fi services when mode is client,
    *                         it triggers m_evWifiServicesChanged event for notification.
    *
    * \param [out] stWifiServicesList - Structure provided by client to be filled with Wi-Fi service list.
    * \return WiFiServerIF_ErrorCodes - WIFI_SERVER_RES_OK operation success |
    *                                   Different than WIFI_SERVER_RES_OK an error was found while retrieving data.
    *
    * \pre : Target and Wi-Fi service fully started.
    * \post : Information about Wi-Fi services attributes will be filled in structure for client use.
    * \msc
    * hscale="2";
    * stlaapp [label="STLA Application"],
    * wifidmn [label="Wifi Domain"];
    * |||;
    * stlaapp note wifidmn [label="Asynchronous", textcolor="#0000BB", linecolor="#0000BB"];
    * |||;
    * stlaapp box stlaapp [label="m_evWifiServicesChanged += Poco::delegate(this,&ClientApp::onWifiServicesChanged)"];
    * ...;
    * wifidmn >> stlaapp[label="m_evWifiServicesChanged"];
    * |||;
    * wifidmn <= stlaapp[label="getWifiServices(serviceList)"];
    * wifidmn =>> wifidmn[label="getWifiServices(serviceList)"];
    * wifidmn box wifidmn [label=" serviceList = {
    * 							\nssid,
    *                             \nConnectionStatus,
    *                             \n802.11 PHY standard,
    *                             \nrssi,
    *                             \nchannel number,
    *                             \nsecurity mode,
    *                             \ncipher information,
    *                             \nmac address
    *                             \n}"];
    * ---[label="else", linecolor="#1BC745"];
    * wifidmn box wifidmn [label="number = 0, empty list"];
    * ---[linecolor="#1BC745"];
    * wifidmn => stlaapp[label="serviceList"];
    *
    * |||;
    * stlaapp note wifidmn [label="Synchronous", textcolor="#0000BB", linecolor="#0000BB"];
    * |||;
    * wifidmn <= stlaapp[label="getWifiServices(serviceList)"];
    * wifidmn =>> wifidmn[label="getWifiServices(serviceList)"];
    * wifidmn box wifidmn [label=" serviceList = {
    * 							\nssid,
    *                             \nConnectionStatus,
    *                             \n802.11 PHY standard,
    *                             \nrssi,
    *                             \nchannel number,
    *                             \nsecurity mode,
    *                             \ncipher information,
    *                             \nmac address
    *                             \n}"];
    * ---[label="else", linecolor="#1BC745"];
    * wifidmn box wifidmn [label="number = 0, empty list"];
    * ---[linecolor="#1BC745"];
    * wifidmn => stlaapp[label="serviceList"];
    * |||;
    * \endmsc
    */
    virtual WiFiServerIF_ErrorCodes getWifiServices(WifiServerServiceList& stWifiServicesList) = 0;

    /**
    * \brief getWifiStatus: Interface to request the current state of Wi-Fi,
    *                        it triggers m_evWifiStatusChanged event for notification.
    *
    * \param [out] stWifiStatus - Structure provide by client to be filled with current Wi-Fi status.
    * \return void.
    *
    * \pre : Target and Wi-Fi service fully started.
    * \post : Information about Wi-Fi status will be filled in structure for client use.
    * \msc
    * hscale="2";
    * stlaapp [label="STLA application"],
    * wifidmn [label="Wi-Fi Domain"];
    * stlaapp note wifidmn [label="Synchronous", textcolor="#0000BB", linecolor="#0000BB"];
    * |||;
    * wifidmn box stlaapp[label="Update service list: getWifiServices(serviceList)"];
    * |||;
    * stlaapp => wifidmn[label="getWifiStatus(stWifiStatus)"];
    * wifidmn =>> wifidmn[label="getWifiStatus(stWifiStatus)"];
    * |||;
    * wifidmn box wifidmn [label="stWifiStatus =\n{\nWi-Fi mode,\nConnection state\n}"];
    * |||;
    * wifidmn >> stlaapp[label=""];
    * |||;
    * stlaapp note wifidmn [label="Asynchronous", textcolor="#0000BB", linecolor="#0000BB"];
    * |||;
    * stlaapp box stlaapp [label="m_evWifiRemoteStatusChanged += Poco::delegate(this,&ClientApp::onWifiStatusChanged)"];
    * |||;
    * ...;
    * wifidmn >> stlaapp[label="m_evWifiRemoteStatusChanged"];
    * |||;
    * stlaapp => wifidmn[label="getWifiStatus(stWifiStatus)"];
    * wifidmn =>> wifidmn[label="getWifiStatus(stWifiStatus)"];
    * wifidmn box wifidmn [label="stWifiStatus =\n{\nWi-Fi mode,\nConnection state\n}"];
    * |||;
    * wifidmn >> stlaapp[label=""];
    * |||;
    * \endmsc
    */
    virtual void getWifiStatus(WifiServerStatus& stWifiStatus) = 0;

    typedef Poco::AutoPtr<IWifiServiceProvider> Ptr;

    /**
    * \brief m_evWifiServicesChanged: Poco event used to notify the available Wi-Fi services.
    * Wi-Fi domain will use the structure WifiServerServiceList to provide:
    * - The number of Wi-Fi services available - unsigned int
    * - For each Wi-Fi service:
    *     - SSID                               - string 33 characters
    *     - Connection status                  - WiFiServerIF_ServiceState_e
    *     - 802.11 PHY standard                - WiFiServerIF_802_11_PhyStandard_e
    *     - Received signal strength indicator - unsigned int
    *     - Wi-Fi channel number               - unsigned int
    *     - Security mode                      - WiFiServerSecurity_e
    *     - Cipher information                 - string 25 characters
    *     - MAC address of the router          - string 18 characters
    *
    * \pre : Current Wi-Fi mode is client.
    * \post : Event m_evWifiServicesChanged will notify the information.
    * \msc
    * hscale="2";
    * stlaapp [label=""],
    * wifidmn [label=""];
    * stlaapp box stlaapp [label="STLA application"],
    * wifidmn box wifidmn [label="Wi-Fi Domain"];
    * stlaapp box stlaapp [label="m_evWifiServicesChanged += Poco::delegate(this,&ClientApp::onWifiServicesChanged)"];
    * ---[label="if (change in services triggered)", linecolor="#0000FF"];
    * wifidmn =>> wifidmn[label="getWifiServices"];
    * ---[label="if (current mode is client)", linecolor="#1BC745"];
    * wifidmn box wifidmn [label="ssid,
    *                              ConnectionStatus,
    *                              802.11 PHY standard,
    *                              rssi,
    *                              channel number,
    *                              security mode,
    *                              cipher information,
    *                              mac address"];
    * ---[label="else", linecolor="#1BC745"];
    * wifidmn box wifidmn [label="number = 0, empty list"];
    * |||;
    * |||;
    * wifidmn >> stlaapp[label="m_evWifiServicesChanged"];
    * |||;
    * \endmsc
    * \note Client must ensure to remove delegate during shutdown proccess (m_evWifiServicesChanged -= Poco::delegate(this,&ClientApp::onWifiServicesChanged)),
    *  If current mode is Client, the number of services will be sent with a list of the elements,
    * if mode is different than Client, the number of services will be 0.
    */
    Poco::BasicEvent<void> m_evWifiRemoteServicesChanged;

    /**
    * \brief m_evWifiStatusChanged: Poco event used to notify the current Wi-Fi state.
    * Wi-Fi domain will use the structure WifiServerStatus to provide:
    * - Wi-Fi state (enabled/disabled, client, access point) - WiFiServerNetState_e
    * - Connection state - WiFiServerIF_ServiceState_e
    *
    * \pre : Target started.
    * \post : Event m_evWifiStatusChanged will notify the information.
    * \msc
    * hscale="2";
    * stlaapp [label=""],
    * wifidmn [label=""];
    * stlaapp box stlaapp [label="STLA application"],
    * wifidmn box wifidmn [label="Wi-Fi Domain"];
    * stlaapp box stlaapp [label="m_evWifiStatusChanged += Poco::delegate(this,&ClientApp::onWifiStatusChanged)"];
    * ---[label="if (change in states triggered)", linecolor="#0000FF"];
    * wifidmn =>> wifidmn[label="getWifiStatus"];
    * wifidmn box wifidmn [label="Wi-Fi mode, Connection state"];
    * |||;
    * |||;
    * wifidmn >> stlaapp[label="m_evWifiStatusChanged"];
    * |||;
    * \endmsc
    * \note Client must ensure to remove delegate during shutdown proccess (m_evWifiStatusChanged -= Poco::delegate(this,&ClientApp::onWifiStatusChanged)).
    */
    Poco::BasicEvent<void> m_evWifiRemoteStatusChanged;
};

}
}

#endif // IWIFISERVICERPROVIDER_H
