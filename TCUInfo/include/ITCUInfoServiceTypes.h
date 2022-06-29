/**
 * \file
 *         ITCUInfoServiceTypes.h
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

#include <string>
#include <list>
#ifndef TCU_INFO_SERVICE_TYPES_H_
#define TCU_INFO_SERVICE_TYPES_H_

namespace Stla
{
namespace TCUInfoService
{
/**
 * @brief VehicleEngineType enumeration
 *
 */
 //@serialize 
typedef enum
{
    UNDEFINED                                           = 0,/**< UNDEFINED engine */
    GASOLINE_TANK                                       = 1,/**< Gasoline tank details */
    DIESEL_TANK                                         = 2,/**< Diesel tank details */
    COMPRESSED_NATURAL_GAS                              = 3,/**< Compressed natural gas */
    LIQUID_PROPANE_GAS                                  = 4,/**< Liquid propane gas */
    ELECTRIC_ENERGY_STORAGE_EXCEEDING_42V_AND_100A_H    = 5,/**< Electric energy storage */
    HYDROGEN_STORAGE                                    = 6,/**< Hydrogen storage */
    GASOLINE_TANK_AND__ELECTRIC_ENERGY_STORAGE          = 7,/**< Gasoline tank and electric energy storage details */
    DIESEL_TANK_AND_ELECTRIC_ENERGY_STORAGE             = 8/**< Diesel tank and electric energy storage details */

} EVehicleEngineType;

/**
 * \brief The TCUInfo_Error_t defines different TCU Info service interface return types.
 */
//@serialize  
enum TCUInfo_Error_t
{
    SUCCESS,                  /**< Returned in case of success operation */
    ERROR,                    /**< Returned in case of operation failure due to an internal communication error */
    ERROR_INVALID_ARGUMENT,   /**< Returned when an invalid argument is passed to the API */
    ERROR_PERS,               /**< Returned in case of internal reading error from persistence */   
};

/**
 *  \brief  sAppInfo_t to retrieve information of all the applications installed on the TCU.
 *  \details
 */
    
typedef struct AppInfo
{
	std::string appName;  /**< Name of the installed Application in the TCU **/
	std::string appVersion; /**< Version detail of the installed Application in the TCU **/	
}sAppInfo_t;

/**
 *  \brief  sAppFwkServiceInfo_t  to retrieve servcies name and version of the Application Framework of the TCU..
 *  \details
 */
typedef struct AppFwkServiceInfo
{
	std::string serviceName;  /**< Name of the services **/
	std::string serviceVersion; /**< Version detail of the installed Application in the TCU **/	
}sAppFwkServiceInfo_t;

/**
 *  \brief  sAppFrameworkInfo_t  to retrieve information on the Application Framework of the TCU.
 *  \details
 */
typedef struct AppFrameworkInfo
{
	std::string appFwkVersion; /**< Application Framework version **/
	std::list<sAppFwkServiceInfo_t> servicesInfo; /**<Application Framework services name and version details  **/
	
}sAppFrameworkInfo_t;

/**
 *  \brief  sFirmwareInfo_t  to retrieve information on all the firmware components of the TCU.
 *  \details
 */
typedef struct FirmwareInfo
{
	std::string vendor ; /**< Firmware Vendor name **/
	std::string FWVersion; /**< Firmware version **/
	std::string FWSerialNumber; /**< Firmware serial number **/
	std::string DateOfProduction; /**< Firmware dateofproduction **/
	
}sFirmwareInfo_t;

/**
 *  \brief  sHardwareInfo_t  to retrieve information on all the firmware components of the TCU.
 *  \details
 */
typedef struct HardwareInfo
{
	std::string vendor ; /**< Hardware Vendor name **/
	std::string HWVersion; /**< Hardware version **/
	std::string HWSerialNumber; /**< Hardware serial number **/
	std::string DateOfProduction; /**< Hardware dateofproduction **/
	
}sHardwareInfo_t;

} // namespace TCUInfoService
} // namespace Stla

#endif
