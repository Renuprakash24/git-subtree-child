/**
 * \file
 *         ITCUInfoService.h
 * \brief
 *         TCU Information Service API
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
 
#ifndef TCU_INFO_SERVICE_INTERFACE_H_
#define TCU_INFO_SERVICE_INTERFACE_H_

/****************** Includes ************************
 ***************************************************/

/* Poco library includes */

#include "Poco/OSP/Service.h"
#include "Poco/AutoPtr.h"
#include <string>
#include "Poco/BasicEvent.h"

/* TCU Info Service bundle includes */

#include "ITCUInfoServiceTypes.h"
	
namespace Stla
{
namespace TCUInfoService
{

/**
 * @brief The ITCUInfoService interface, for TCU information service
 *
 */

static const std::string TCU_INFO_SERVICE_INTERFACE = "stla.networking.tcu-info.service.base";

#ifdef DOXYGEN_WORKING
class ITCUInfoService : public Poco::OSP::Service
#else
class __attribute__((visibility("default"))) ITCUInfoService : public Poco::OSP::Service
#endif
{
public:
		/* Pointer to Service interface*/
        typedef Poco::AutoPtr<ITCUInfoService> Ptr;

        /**
         * @brief Destroy the ITCUInfoService object
         *         */
        virtual ~ITCUInfoService() {}
		
		/*******************************************************************
        @brief *********** Stellantis TCU Information  Service Interfaces *************
        ********************************************************************/
     	
		/**
         * @brief Get the hardware configuration of the TCU.
         * 
         * @return the hardware configuration of the TCU.
         */
        virtual std::string getHWNumber()= 0;
		
		/**
         * @brief Get the unique serial number of the TCU.
         *
         * @return the serial number of the TCU.
         */
		virtual std::string getUIN()= 0;
		
		/**
         * @brief Get the information of all the applications installed on the TCU.
         *
         * @return the list of application name and version of the installed app in the TCU.
        */		 
		virtual std::list<sAppInfo_t> getAppsInformation() = 0;

		/**
         * @brief Get the information of the Application Framework of the TCU.
         *
         * @return the list of services name and services version of the installed app in the TCU.
        */
		virtual sAppFrameworkInfo_t getAppFwkInformation() = 0;
		
		/**
         * @brief Get the  information of vendor, version, dateofproduction of the firmware components of the TCU.
         *
         * @return the list of firmware components of the TCU.
        */
		virtual sFirmwareInfo_t getFirmwareInformation() = 0;
		
		/**
         * @brief Get the  information of vendor, version, dateofproduction of the all the hardware components of the TCU.
         *
         * @return the list of hardware components of the TCU.
        */
		virtual sHardwareInfo_t getHardwareInformation() = 0;
			

		/** @brief Poco Event triggered when synchronization status of the TCU system time.
		*
		* Values are:
		* - true if synchronised
		* - false if re-synchronizationsynchronised
		*/
		virtual bool isTimeSynchronized() = 0;
		
		/** @brief Poco Event triggered to notify of a synchronization/re-synchronization event of the TCU system time
		*/
		
		Poco::BasicEvent<const bool> onTimeSynchronization;		
		
		/**
         * @brief Get the Vehicle Engine Value
         *
         * @param[out]   EVehicleEngineType
         * @return   SUCCESS if the operation is succesful
         * \n        ERROR if the operation failed due to an internal communication error
         * \n        ERROR_PERS if operation failed due to internal reading error from persistence
         */
        virtual TCUInfo_Error_t getVehicleEngineTypeValue(EVehicleEngineType &vehicleenginetype) = 0;
		
		/**
		 * @brief Function to get the NAD temperature
         * @param[out] NADTemperature: current processor temperature (Celsius degrees)
         * @return  SUCCESS if successful
         * \n       ERROR if NADTemperature is NULL or generic failure
        */
        virtual TCUInfo_Error_t getNADTemperature(int *NADTemperature) =0;
		
		/**
		 * @brief NAD temperature changed - cyclic notification (typically once a second) temperature Celsius degrees
		*/
		Poco::BasicEvent<int> NADTemperatureEvent;  
		
		/**
        @brief    All subclasses of Service must override the type() and isA() member functions.
        * for more details see : https://pocoproject.org/pro/docs/Poco.OSP.Service.html
        */
		
        /**
        * @brief Returns the type information for the object's class
        */
        const std::type_info &type() const
        {
                return typeid(ITCUInfoService);
        }
        /**
        * @brief Returns true if the class is a subclass of the class given by otherType.
        */
        bool isA(const std::type_info &otherType) const
        {
                std::string name(typeid(ITCUInfoService).name());
                return name == otherType.name() || Service::isA(otherType);
        }
};

} /* namespace TCUInfoService*/
} /* Namespace Stla*/
#endif
