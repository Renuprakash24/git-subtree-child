/**
 * \file
 *         IRemoteAccessService.h
 * \brief
 *         Remote Access Macchina API
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

#ifndef TCU_REMOTE_ACCESS_INTERFACE_H_
#define TCU_REMOTE_ACCESS_INTERFACE_H_

/****************** Includes ************************
 ***************************************************/

/* Poco library includes */

#include "Poco/OSP/Service.h"
#include "Poco/AutoPtr.h"
/* Remote Access Service bundle includes */

#include "IRemoteAccessServiceTypes.h"

#define ECRAN_INFO_PRG_RTAB_REM_SIZE 2
#define ECRAN_INFO_PRG_CLIM_REM_SIZE 7
#define ECRAN_INFO_PRG_CLIM_REM_2_SIZE 7

namespace Stla
{
namespace RemoteAccessService
{

/**
 * @brief The IRemoteAccessService interface, for remote access service
 *
 */

static const std::string REMOTE_ACCESS_SERVICE_INTERFACE = "stla.networking.remote-access.service.base";

#ifdef DOXYGEN_WORKING
class IRemoteAccessService : public Poco::OSP::Service
#else
class __attribute__((visibility("default"))) IRemoteAccessService : public Poco::OSP::Service
#endif
{
public:
        /* Pointer to Service interface*/
        typedef Poco::AutoPtr<IRemoteAccessService> Ptr;

        /**
         * @brief Destroy the IRemoteAccessService object
         *         */
        virtual ~IRemoteAccessService() {}

        /*******************************************************************
        @brief *********** Stellantis Remote Access Service Interfaces *************
        ********************************************************************/
        /**
         * @brief Interface to Request Lock All Doors
         *
         * @return  RAS_SUCCESS if the operation is succesful
         * \n       RAS_ERROR   if the operation failed due to an internal communication error
         */
        virtual RAS_Error_t RequestLockAllDoors() = 0;

        /**
         * @brief Interface to confirm locking All doors
         *
         * @return  RAS_SUCCESS if the operation is succesful
         * \n       RAS_ERROR   if the operation failed due to an internal communication error
         */
        virtual RAS_Error_t RequestLockAllDoorsConfirmed() = 0;

        /**
         * @brief Interface to Request to Unlock All Doors
         *
         * @return  RAS_SUCCESS if the operation is succesful
         * \n       RAS_ERROR   if the operation failed due to an internal communication error
         */
        virtual RAS_Error_t RequestUnlockAllDoors() = 0;

        /**
         * @brief Interface to Request to Unlock Driver Door
         *
         * @return  RAS_SUCCESS if the operation is succesful
         * \n       RAS_ERROR   if the operation failed due to an internal communication error
         */
        virtual RAS_Error_t RequestUnlockDriverDoor() = 0;

        /**
         * @brief Interface to Request Unlock Trunk
         *
         * @return RAS_SUCCESS if the operation is succesful
         * \n      RAS_ERROR   if the operation failed due to an internal communication error
         */
        virtual RAS_Error_t RequestUnlockTrunk() = 0;

        /**
        * @brief  Interfaces for Turning Horn off
        *
        * @return   RAS_SUCCESS if the operation is succesful
        * \n        RAS_ERROR   if the operation failed due to an internal communication error
        */
        virtual RAS_Error_t RequestRemoteHornOff() = 0;

        /**
        * @brief  Interfaces for Turning Horn on
        *
        * @return  RAS_SUCCESS if the operation is succesful
        * \n       RAS_ERROR   if the operation failed due to an internal communication error
        */
        virtual RAS_Error_t RequestRemoteHornOn() = 0;

        /**
        * @brief  Interfaces for Turning Lights Off
        *
        * @return RAS_SUCCESS if the operation is succesful
        * \n      RAS_ERROR   if the operation failed due to an internal communication error
        */
        virtual RAS_Error_t RequestTurnLightsOff() = 0;

        /**
        * @brief    Interfaces for Turning Lights On
        *
        * @return RAS_SUCCESS if the operation is succesful
        * \n       RAS_ERROR   if the operation failed due to an internal communication error
        */
        virtual RAS_Error_t RequestTurnLightsOn() = 0;

        /**
        * @brief    Interface for Sending ECRAN_INFO_PRG_RTAB_REM frame 
        * @param ECRAN_INFO_PRG_RTAB_REM: uint8_t table with size = 2
        * @return RAS_SUCCESS if the operation is succesful
        * \n      RAS_ERROR   if the operation failed due to an internal communication error
        */
        virtual RAS_Error_t SendEcranInfoPrgRtabRem(uint8_t ECRAN_INFO_PRG_RTAB_REM[ECRAN_INFO_PRG_RTAB_REM_SIZE]) = 0;

        /**
        * @brief    Interface for Sending ECRAN_INFO_PRG_CLIM_REM frame
        * @param ECRAN_INFO_PRG_CLIM_REM: uint8_t table with size = 7
        * @return RAS_SUCCESS if the operation is succesful
        * \n       RAS_ERROR   if the operation failed due to an internal communication error
        */
        virtual RAS_Error_t SendEcranInfoPgrClimRem(uint8_t ECRAN_INFO_PRG_CLIM_REM[ECRAN_INFO_PRG_CLIM_REM_SIZE]) = 0;

        /**
        * @brief    Interface for Sending ECRAN_INFO_PRG_CLIM_REM_2 frame 
        * @param ECRAN_INFO_PRG_CLIM_REM_2: uint8_t table with size = 7
        * @return  RAS_SUCCESS if the operation is succesful
        * \n       RAS_ERROR   if the operation failed due to an internal communication error
        */
        virtual RAS_Error_t SendEcranInfoPgrClimRem2(uint8_t ECRAN_INFO_PRG_CLIM_REM_2[ECRAN_INFO_PRG_CLIM_REM_2_SIZE]) = 0;

        /**
         * @brief Interface to Request Charge Data
         * @param Request: false = Not requested, true = requested
         * @return  RAS_SUCCESS if the operation is succesful
         * \n       RAS_ERROR   if the operation failed due to an internal communication error
         */
        virtual RAS_Error_t RequestChargeData(bool Request) = 0;
        
		/**
         * @brief Interface to Request remote charge daily limit 
         * @return  RAS_SUCCESS if the operation is succesful
         * \n       RAS_ERROR   if the operation failed due to an internal communication error
         */
		virtual RAS_Error_t RemoteChargeLimitationDaily() = 0;
		
		/**
         * @brief Interface to Request remote charge trip limit 
         * @return  RAS_SUCCESS if the operation is succesful
         * \n       RAS_ERROR   if the operation failed due to an internal communication error
         */
		virtual RAS_Error_t RemoteChargeLimitationTrip() = 0;
		
        /**
        * @brief    Interface for Sending INFO_LOCATION_WEB signal
        * @param    INFO_LOCATION_WEB : Signal length 2 bits
        *           DBC Version 11
        *
        * @return  RAS_SUCCESS if the operation is succesful
        * \n       RAS_ERROR   if the operation failed due to an internal communication error
        * \n       RAS_ERROR_INVALID_ARGUMENT if operation failed due to invalid argument passed to the API
        */
        virtual RAS_Error_t SendInfoLocationWeb(uint8_t INFO_LOCATION_WEB) = 0;

        /**
        * @brief    Interface for Sending NO2_WEB_VALUE signal
        * @param    NO2_WEB_VALUE : Signal length 12 bits (UNM-12)
        *           DBC Version 11
        *
        * @return  RAS_SUCCESS if the operation is succesful
        * \n       RAS_ERROR   if the operation failed due to an internal communication error
        * \n       RAS_ERROR_INVALID_ARGUMENT if operation failed due to invalid argument passed to the API
        */
        virtual RAS_Error_t SendNo2WebValue(uint16_t NO2_WEB_VALUE) = 0;

        /**
        * @brief    Interface for Sending O3_WEB_VALUE signal
        * @param    O3_WEB_VALUE : Signal length 11 bits (UNM-11)
        *           DBC Version 11
        *
        * @return  RAS_SUCCESS if the operation is succesful
        * \n       RAS_ERROR   if the operation failed due to an internal communication error
        * \n       RAS_ERROR_INVALID_ARGUMENT if operation failed due to invalid argument passed to the API
        */
        virtual RAS_Error_t SendO3WebValue(uint16_t O3_WEB_VALUE) = 0;

        /**
        * @brief    Interface for Sending PM25_WEB_VALUE signal
        * @param    PM25_WEB_VALUE : Signal length 10 bits (UNM-10)
        *           DBC Version 11
        *
        * @return  RAS_SUCCESS if the operation is succesful
        * \n       RAS_ERROR   if the operation failed due to an internal communication error
        * \n       RAS_ERROR_INVALID_ARGUMENT if operation failed due to invalid argument passed to the API
        */
        virtual RAS_Error_t SendPM25WebValue(uint16_t PM25_WEB_VALUE) = 0;

        /**
        * @brief    Interface for Sending SO2_WEB_VALUE signal
        * @param    SO2_WEB_VALUE : Signal length 12 bits (UNM-12)
        *           DBC Version 11
        *
        * @return  RAS_SUCCESS if the operation is succesful
        * \n       RAS_ERROR   if the operation failed due to an internal communication error
        * \n       RAS_ERROR_INVALID_ARGUMENT if operation failed due to invalid argument passed to the API
        */
        virtual RAS_Error_t SendSo2WebValue(uint16_t SO2_WEB_VALUE) = 0;
     
        /**
         * @brief Interface to send a request to deactivate immobilisation
         *
         * @param password a non empty string value with a fixed size(7 bytes)
         * @return  RAS_SUCCESS if the operation is succesful
         * \n       RAS_ERROR_INVALID_ARGUMENT if operation failed due to invalid argument passed to the API
         * \n       RAS_ERROR if the operation failed due to an internal communication error
         */
        virtual RAS_Error_t RemoteAccessRequestImmoOff(const std::string& password) = 0;

        /**
         * @brief Interface to send a request to activate immobilisation
         *
         * @param password a non empty string value with a fixed size(7 bytes)
         * @return  RAS_SUCCESS if the operation is succesful
         * \n       RAS_ERROR_INVALID_ARGUMENT if operation failed due to invalid argument passed to the API
         * \n       RAS_ERROR   if the operation failed due to an internal communication error
         */
        virtual RAS_Error_t RemoteAccessRequestImmoOn(const std::string& password) = 0;

        /**
        @brief    All subclasses of Service must override the type() and isA() member functions.
        * for more details see : https://pocoproject.org/pro/docs/Poco.OSP.Service.html
        */

        /**
        * @brief Returns the type information for the object's class
        */
        const std::type_info &type() const
        {
                return typeid(IRemoteAccessService);
        }
        /**
        * @brief Returns true if the class is a subclass of the class given by otherType.
        */
        bool isA(const std::type_info &otherType) const
        {
                std::string name(typeid(IRemoteAccessService).name());
                return name == otherType.name() || Service::isA(otherType);
        }

};
} /* namespace RemoteAccessService*/
} /* Namespace Stla*/

#endif
