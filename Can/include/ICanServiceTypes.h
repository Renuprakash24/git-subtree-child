/**
 * \file
 *         ICanServiceTypes.h
 * \brief
 *         Can Service Macchina API
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

#include <vector>
#include <list>
#ifndef CAN_SERVICE_TYPES_H_
#define CAN_SERVICE_TYPES_H_

namespace Stla
{
namespace CanService
{
/**
 * \brief The CANFrameData_type struct to get CAN service Frame properties.
 */
//@serialize
typedef struct
{
	uint32_t relativeTimeStamp; /**< The exact timestamp in milliseconds when the CAN frame was received with a new value */
    uint16_t frameID; /**< The CAN frame ID*/
    uint8_t frameSize; /**< The CAN frame size */
    std::vector<uint8_t> payload; /**< The frame data payload */

} CANFrameData_type;

template<typename T>

/**
 * \brief The CANSignalData_type struct to get CAN Service Signal properties.
 */
//@serialize

typedef struct
{
	uint32_t relativeTimeStamp; /**< The exact timestamp in milliseconds when the CAN frame that contains this signal was received with a new value */
    String signalname; /**< CAN signal name */
    ECanSignalDataType signalType; /**< The signal type. Template type contains signal type as well.  */
    T & signalValue; /**< The signal value */
	
} CANSignalData_type;

/**
 * \brief The CAN_Bus_type defines different CAN Bus types.
 */
//@serialize

typedef enum
{
    Low_Speed = 0,      /**< Low CAN Speed */
    High_Speed = 1,     /**< High CAN Speed */
    CAN_FD = 2,         /**< CAN FD Configuration */
    Invalid_Speed = 3   /**< Indefined CAN Speed Bus */

} CAN_Bus_type;

/**
 * \brief The CAN_Architecture_Type defines different CAN architecture types.
 */
//@serialize

typedef enum
{

    NEA_R1 = 0,               /**< NEA_R1 */
    NEA_R1_RETROFIT_2010 = 1, /**< NEA_R1_RETROFIT_2010 */
    NEA_R2 = 2,               /**< NEA_R2 */
    UNAVAILABLE = 3           /**< Returned when reading the architecture type value from persistence fails */

} CAN_Architecture_Type;

/*Structure that contain CAN configuration info */
typedef struct
{
    CAN_Architecture_Type Archi_Type; /* Different CAN architecture types */
	std::list<eCANBusName> CAN_bus_name_list; /* CAN Bus Name depending on architecture */	
    int32_t Number_Can_bus;           /* Number of CAN buses */
    CAN_Bus_type Bus_Type;            /* Different CAN Bus types */
    int32_t CAN_Speed;                /* CAN Speed (kbits/s)*/
	
} CAN_Config_Info_Type;


typedef struct
{
    CAN_Error_t ErrorCode;	/* CAN Service return code */
    uint16_t Subscription_ID; /* CAN Service subscription id */
	
} SubscribeRetVal_type;

/**
 * \brief The ECanSignalDataType defines different CAN signal data types.
 */
//@serialize
typedef enum
{
    E_DATA_BOOL = 0, /**< Indicates that the signal type is a Boolean */
	E_DATA_INT64 = 1, /**< Indicates that the signal type is an Integer */
    E_DATA_UINT64 = 2, /**< Indicates that the signal type is an Enum of Integer */
    E_DATA_DOUBLE = 3, /**< Indicates that the signal type is a Double */
    E_DATA_STRING = 4, /**< Indicates that the signal type is a String */
    E_DATA_TYPE_UNKNOWN = 5 /**< In case of an internal error, this value indicates that the signal type is unkown */
 } ECanSignalDataType;

/**
 * \brief The CAN_Error_t defines different CAN service interface return types.
 */
//@serialize

enum CAN_Error_t
{
    SUCCESS,                  /**< Returned in case of success operation */
    ERROR,                    /**< Returned in case of operation failure due to an internal communication error */
    ERROR_SIG_UNINITIALIZED,  /**< Returned in case of operation failure due to CAN signal not received yet (The signalData pointer contenent will not be changed in this case) */
	ERROR_INVALID_ARGUMENT,   /**< Returned when an invalid argument is passed to the API */
    ERROR_PERS,               /**< Returned in case of internal reading error from persistence */
    ERROR_NOT_SUPPORTED,      /**< Returned while triggering unsupported interfaces on current Architecture */
    ERROR_FRAME_UNINITIALIZED, /**< Returned in case of operation failure due to CAN Frame not received yet */
	ERROR_CACHE_NOT_READY, /**< Returned in case if the API is invoked before the cache becomes ready */
	ERROR_MEMORY_FULL /**< Returned in case if there is no memory available */	
};

/**
 * \brief The eCANBusName defines different types CAN Bus.
 */
//@serialize
enum eCANBusName
{	
	/* To be defined based on applicable architecture */
	
};

/**
 * @brief The eFilter_Mode defines different types filtering mode.
 * \n Example of filtering mode
 *
 * \li \c 		 ------------------------------------------------------------------------
 *  \li \c \b T_frame \p | \p 0  | \p 1  | \p 2  | \p 3  | \p 4  | \p 5  | 6 |
* \li \c -------------------------------------------------------------------------
* \li \c \b frame \b content  | aa | bb | bb | bb | bb | cc | dd |
* \li \c -------------------------------------------------------------------------
* \li \c FILTER_OFF   |	Y  | Y  | Y  | Y  | Y  |  Y |  Y |
* \li \c -------------------------------------------------------------------------
* \li \c FILTER_SAMPLING| Y  | N  | Y  | N  | Y  |  N |  Y |
* \li \c -------------------------------------------------------------------------
* \li \c FILTER_ON_CHANGE| Y  | Y  | N  | N  | N  |  Y |  Y |
* \li \c -------------------------------------------------------------------------
* \li \c FILTER_SAMPLING_AND_ON_CHANGE| Y  | N  | Y  | N  | N  |  N |  Y |
* \li \c -------------------------------------------------------------------------
* \li \c FILTER_SAMPLING_OR_ON_CHANGE | Y  | Y  | Y  | N  | Y  |  Y |  Y |
* \li \c  -------------------------------------------------------------------------
*/
//@serialize
enum eFilter_Mode
{
	FILTER_OFF , /**< when the frame is received.*/
	FILTER_SAMPLING , /**< every X received frames */
	FILTER_ON_CHANGE , /**< when the content of the last received frame from the CAN is different from the previous frame sent to the modem */
	FILTER_SAMPLING_AND_ON_CHANGE , /**< when the sampling time is over AND the content of the frame is different. */
	FILTER_SAMPLING_OR_ON_CHANGE /**< when the sampling time is over OR the content of the frame is different */
};

} // namespace CanService
} // namespace Stla

#endif