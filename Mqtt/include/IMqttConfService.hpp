/**
 * \file
 *         IMqttConfService.hpp
 * \brief
 *         Interface available for 3rd Party application to configure the MQTT broker.
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
 
#ifndef IMQTTCONFSERVICE_H_
#define IMQTTCONFSERVICE_H_

#include <string>
#include <vector>

#include <Poco/BasicEvent.h>
#include <Poco/OSP/Service.h>
#include "Poco/OSP/SystemEvents.h"
#include "Poco/OSP/BundleContext.h"


namespace Stla
{
namespace Connectivity
{
	/**
	* @brief The mqtt_conf_err_code defines the error code */
	//@serialize
	typedef enum mqtt_conf_err_code
	{
		OK = 0,             		/**< no error */
		METHOD_NOT_ALLOWED, 		/**< the operation is not allowed */
		OUT_OF_MEMORY,      		/**< operation exceeds the available memory for MQTT configuration */
		ID_INVALID,         		/**< given index is invalid */
		ID_UNUSED,          		/**< index is not set */
		BROKER_ALREADY_CONFIGURED, 	/**< another Third Party  application is already using the interface */
		BROKER_NOT_AVAILABLE, 		/**< MQTT Manager does not respond */
		UNKNOWN_ERROR				/**< Unknown Error */
	} mqtt_conf_err_code_t;

	/**
	 * @brief Maximum number of configuration items set by ADK interface. All items are indexed: 0..MAX-1
	 */
	#define MAX_CONF_ITEM 10

#ifdef DOXYGEN_WORKING
    class IMqttConfHandler : public Poco::RefCountedObject
#else
    class __attribute__((visibility("default"))) IMqttConfHandler : public Poco::RefCountedObject
#endif
    {

    public:

        /**
         * @brief Class smart pointer definition
         */
        typedef Poco::AutoPtr<IMqttConfHandler> Ptr;

        /**
         * @brief Destroy the IMqttConfHandler handler
         *
         */
        virtual ~IMqttConfHandler() {}


        /**
         * @brief Get the current mode used by the MQTT Manager.
         *
         * @param adk_mode output parameter: True if the MQTT Broker is configured through ADK (Application Framework), False if the broker is configured through Device Management.
         *
         * @return Status of the operation. OK on success.
         */
        virtual mqtt_conf_err_code_t getAdkMode(bool &adk_mode_out) = 0;

        /**
         * @brief Set the current mode used by the MQTT Manager.
         * 
         * @param adk_mode New value for the configuration mode: if True, it will enable ADK mode. If False, it will disable ADK mode (enabling DM mode).
         *
         * @warning Changing the mode of the MQTT Manager will reset the current configuration, and remove all data from persistence. No configuration reset shall be applied if the current mode corresponds to the mode to be set.
         * @warning Setting the mode to ADK (adk_mode = True) will prevent other appications from accessing the MqttConfService.
         *
         * @return Status of the operation. OK on success.
         */
		virtual mqtt_conf_err_code_t setAdkMode(bool adk_mode) = 0;

        /**
         * @brief Get the list of MQTT configuration items already set.
         *
         * @param indexes output parameter: a sorted list of the index of MQTT Configuration items: between 0 and MAX_CONF_ITEM values, each value is between 0 and MAX_CONF_ITEM - 1. Indexes are sorted from smaller to larger.
         *
         * @return Status of the operation. OK on success.
         */
        virtual mqtt_conf_err_code_t getIndexList(std::vector<unsigned int> &indexes_out) = 0;

        /**
         * @brief Read 1 configuration item.
         *
         * @param index index of the configuration item to read (between 0 and MAX_CONF_ITEM - 1; MAX_CONF_ITEM = 10 -> index between 0 and 9)
         * @param config_out output parameter: configuration item set on the broker
         *
         * @return Status of the operation. OK on success.
         */
		virtual mqtt_conf_err_code_t getItem(unsigned int index, std::string &config_out) = 0;

        /**
         * @brief Writes a new configuration item.
         * 
         *  The following good practices should be enforced:
         * - Clarification done on the mandatory constraint about the mqtt keep-alive period, wich is due to Service Watcher Mode.
         * - The following good practice should be observed:
         * - The RAM isn't unlimited and is budgeted for each applications. Tests are done on a regular basis, with the parameters fixed in the build. 
         *   If you raise the values of parameters that shall increase the RAM consumed by mqtt broker, it shall have consequences on the RAM remaining 
         *   and available for other applications (e.g. STLA apps). It can also provoke crashes. I strongly not recommend this type of change.
         * - If you notice a parameter in this family should be changed, please contact us to change it in the build. This way, 
         *   the RAM consumption will be followed up.
         * - Some parameters can be changed by Device Management and ADK master application. E.G. "Persistence". 
         *   These parameters should be changed in the way defined by STLA requirements (e.g. with DM use of Resource 3000.3000 for "Persistence" value), 
         *   and not take advantage of a bridge configuration file to change a general parameter. A bridge config file should normally define only parameters for the bridge, not general parameters. 
         *   If needed, we should rather add more resources in DM. For example, if the persistence parameter is added in a bridge configuration file, 
         *   you will have one value defined in the general mosquitto.conf and another one in the bridge configuratiion file.
         * - This is the exhaustive list of parameters that we changed in the configuration file:
         * 
         *        \# Disable the publishing of the $SYS tree.
         *        sys_interval 0
         *
         *        The maximum number of client connections to allow. This is a per listener setting.
         *        max_connections 50
         *
         *        Save persistent message data to disk (true/false).
         *        persistence false
         *
         *        The filename to use for the persistent database, not including # the path.
         *        persistence_file mosquitto.db
         *
         *        Location for persistent database. Must include trailing /
         *        persistence_location /data/persistency/public/file/
         *
         * - During the discussion, we focused on the "log_dest" parameter. In the TCU, the logs are sent to dlt traces. An application does manage these traces, 
         *   with a cyclic buffer to memorize a given duration of the logs (not sure of the exact time). If you can change this value for testing, 
         *   I would not recommend to change it in production, because you could fill the file system.
         * - The remote_clientid, keepalive_interval, cleansession, notifications, notification_topic, bridge_protocol_version, 
         *   try_private parameters are some examples of values that can be changed only by device management, or by the ADK master application.
         *
         * @param index index of the configuration item to write (between 0 and MAX_CONF_ITEM - 1; MAX_CONF_ITEM = 10 -> index between 0 and 9)
         * @param config new configuration string to set 
         *
         * @warning this operation will create the configuration item if not set, or will overwrite the current configuration
         * @warning if the MQTT broker cannot apply the given configuration, the operation will fail & the previous configuration will be kept unchanged.
         * @warning if the total configuration exceeds the maximum size, the operation will fail & the previous configuration will be kept unchanged.
         * @warning if only a parameter of the configuration will be changed the whole configuration needs to be sent because the content of hte config files
         * which corresponds to the given index will be replaced with the new content from config parameter
         *
         * @return Status of the operation. OK on success.
         */
		virtual mqtt_conf_err_code_t setItem(unsigned int index, const std::string config) = 0;

        /**
         * @brief Remove 1 configuration item
         *
         * @param index index of the configuration item to delete (between 0 and MAX_CONF_ITEM - 1; MAX_CONF_ITEM = 10 -> index between 0 and 9)
         *
         * @warning this operation will delete the configuration from the broker and from the persistence, irrespectively of the broker status.
         *
         * @return Status of the operation. OK on success.
         */
		virtual mqtt_conf_err_code_t deleteItem(unsigned int index) = 0;

    };


    /**
     * @brief MQTT Configuration - AppFwk service name used in OSP
     */
    const char* const MQTT_CONF_SERVICE_NAME = "stla.connectivity.mqttconf.service.base";

    /**
     * @brief IMqttConfService is the MQTT Configuration service allows the configuration of the TCU MQTT broker through the Application Framework.
     */
#ifdef DOXYGEN_WORKING
    class IMqttConfService : public Poco::OSP::Service
#else
    class __attribute__((visibility("default"))) IMqttConfService : public Poco::OSP::Service
#endif
    {
    public:
    
        /**
         * @brief Class smart pointer definition
         */
        typedef Poco::AutoPtr<IMqttConfService> Ptr;
        
        /**
         * @brief IMqttConfService constructor.
         *
         * This class is used to interface with the MQTT Manager
         *
         * @warning The framework/interface shall retrieve the Symbolic name of the calling application.
         */
        IMqttConfService() {}

        /**
         * @brief IMqttConfService destructor.
         */
        virtual ~IMqttConfService() {}

        /**
         * @brief Get the MQTT Configuration Handler, unique per bundlecontext (= unique per application)
         * 
         * @param pAppBndlContext Application context
         *
         * @warning once a bundle has set a configuration, no other bundle is allowed to read or write the MQTT configuration.
         *
         * @return IMqttConfHandler::Ptr 
         */
        virtual IMqttConfHandler::Ptr getMqttConfHandler(Poco::OSP::BundleContext::Ptr pAppBndlContext) = 0;

        /**
         * @brief Tells if the service functionality is ready or not
         * 
         * @return mqtt_conf_err_code_t e.g. invalid MQTT configuration
         */
        virtual mqtt_conf_err_code_t isServiceReady() const = 0;

        /**
         * @brief	Returns the service information for the object's class.
         */
        const std::type_info& type() const
        {
            return typeid(IMqttConfService);
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
         * @brief Poco event notifying a state change of the MQTT Manager
         * 
         */
        Poco::BasicEvent<const mqtt_conf_err_code_t> event_ServiceStatusChange;
        
    };

} ///* namespace Connectivity */
} ///* namespace Stla */

#endif ///* IMQTTCONFSERVICE_H_ */
