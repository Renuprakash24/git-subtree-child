/**
 * \file
 *         ICanService.h
 * \brief
 *        Can service Macchina API's
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
 
#ifndef CAN_SERVICE_INTERFACE_H_
#define CAN_SERVICE_INTERFACE_H_

/****************** Includes ************************
 ***************************************************/

/* Poco library includes */

#include "Poco/OSP/Service.h"
#include "Poco/AutoPtr.h"
#include <memory>
#include <cstdint>
#include <list>

/* CAN Service bundle includes */

#include "ICanServiceTypes.h"

namespace Stla
{
namespace CanService
{

/**
 * @brief The ICanService interface, for CAN Service
 *
 */

static const std::string CAN_SERVICE_INTERFACE = "stla.networking.can.service.base";

#ifdef DOXYGEN_WORKING
class ICanService : public Poco::OSP::Service
#else
class __attribute__((visibility("default"))) ICanService : public Poco::OSP::Service
#endif
{
public:
        /* Pointer to Service interface*/
        typedef Poco::AutoPtr<ICanService> Ptr;

        /**
         * @brief Destroy the ICanService object
         *
         **/
        virtual ~ICanService() {}
		
		/*******************************************************************
        @brief *********** Stellantis Can Service Interfaces *************
        ********************************************************************/     	
				 
		/**
         * @brief Get the Can Frame
         *
         * @param [in]   canbusname : CAN BUS NAME
		 * @param [in]   FrameID : CAN frame identifier
		 * @param [out]  FrameData : FrameData for each FrameID
		 *
         * @return   SUCCESS if the operation is succesful
         * \n        ERROR if the operation failed due to an internal communication error
         * \n        ERROR_INVALID_ARGUMENT Returned when an invalid argument is passed to the API 
		 * \n 		 ERROR_NOT_SUPPORTED Returned while triggering unsupported interfaces on current Architecture 
         * \n		 ERROR_FRAME_UNINITIALIZED Returned in case of operation failure due to CAN Frame not received yet 
         */	
		 
		virtual CAN_Error_t can_getFrameLastValue(eCANBusName canbusname, std::list<uint16_t> FrameID, std::list<CANFrameData_type> FrameData ) = 0;
		
		/**
         * @brief 		Get CAN FrameCache
         *
         * @param [in]  canbusname : CAN BUS NAME
		 * @param [in]  FrameID : CAN frame identifier		 
		 * @param [in]  historyDuration :  Duration of the CAN history 
		 * @param [out] FrameData :  FrameData for each FrameID
		 *
         * @return   SUCCESS if the operation is succesful
         * \n        ERROR if the operation failed due to an internal communication error
         * \n        ERROR_INVALID_ARGUMENT Returned when an invalid argument is passed to the API 
		 * \n        ERROR_NOT_SUPPORTED Returned while triggering unsupported interfaces on current Architecture 
		 * \n        ERROR_CACHE_NOT_READY Returned in case if the API is invoked before the cache becomes ready 
		 * \n        ERROR_MEMORY_FULL  Returned in case if there is no memory available 	
         */
		 
		virtual CAN_Error_t can_getFrameCache(eCANBusName canbusname, std::list<uint16_t> FrameID,  uint8_t historyDuration, std::list<CANFrameData_type> FrameData) = 0;
		
		/**
         * @brief can_unsubscribe
         *
         * @param [in]  Subscription :  Subscription Identifier
		 *
         * @return   SUCCESS if the operation is succesful
         * \n        ERROR if the operation failed due to an internal communication error
         * \n        ERROR_INVALID_ARGUMENT Returned when an invalid argument is passed to the API
         */		   
		virtual CAN_Error_t can_unsubscribe(uint16_t subscription_ID) = 0; 
		
		/**
         * @brief  Get information about the CAN configuration
         * @param  CAN_Info:  Contain the CAN configuration information
         *
         * *************************************************
         * Structure CAN_Info is composed by :
         *           \n Archi_Type     	:   Contains the type of architecture 
		 *           \n CAN_bus_name_list : Contains the CAN bus name list
         *           \n Number_Can_bus :   Contains the number of CAN buses (int32_t)
         *           \n Bus_Type       :   Contains the speed of the CAN Bus (Low Speed = 0 or High Speed = 1 or CAN_FD = 2)
         *           \n CAN_Speed      :   Contains the speed value of the CAN bus (int32_t (kbits/s))
         *
         * *************************************************
         * @return  SUCCESS if the operation is succesful
         *  \n     ERROR   if the operation failed due to an internal communication error
         *  \n     ERROR_INVALID_ARGUMENT if operation failed due to invalid argument passed to the API
         * \n      ERROR_PERS if operation failed due to internal reading error from persistence
         */
		virtual CAN_Error_t can_getConfiguration ( CAN_Config_Info_Type *  CAN_Info ) = 0; 
		
		/**
         * @brief  Subscribe to CAN Frame for better performance
         *
         * @param [in]  canbusname :  CAN BUS NAME
		 * @param [in]  FrameID :  CAN frame identifier
		 * @param [in]  FrameCallback : CAN frame callback function
		 * @param [in]  filtermode: Filter Mode
		 * @param [in]  sampling : Sampling value.		
		 *			A CAN frame is forwarded to the modem every “sampling” *			received frames.		
		 *			Example		
		 *			Sampling = 1 all frames are forwarded		
		 *			Sampling = 2, one out of two is forwarded		
		 *			Sampling = 3, one out of three is forwarded	 
		 *
         * @return   Return the subrscription id and error code
		 * \n 		 SUCCESS if the operation is succesful
         * \n        ERROR if the operation failed due to an internal communication error
         * \n        ERROR_INVALID_ARGUMENT if operation failed due to invalid argument passed to the API
         */		
		virtual SubscribeRetVal_type can_subscribeRTFrame(eCANBusName canbusname, std::list<uint16_t> FrameID, void(FrameCallback)(CANFrameData_type &), eFilter_Mode filtermode, uint16_t sampling = 1 ) = 0;
		
		/**
         * @brief  Subscribe to CAN Frame
         *
         * @param [in]  canbusname :  CAN BUS NAME
		 * @param [in]  FrameID : CAN frame identifier
		 * @param [in]  FrameCallback : CAN frame callback function
		 * @param [in]  filtermode 	  : Filter Mode
		 * @param [in]  sampling :  sampling value.			
		 *			A CAN frame is forwarded to the modem every “sampling” *		  received frames.		
		 *			Example		
		 *			Sampling = 1 all frames are forwarded		
		 *			Sampling = 2, one out of two is forwarded		
		 *			Sampling = 3, one out of three is forwarded	 
		 *
         * @return   SubscribeRetVal_type : Return the subrscription id and error code
		 * \n 		 SUCCESS if the operation is succesful
         * \n        ERROR if the operation failed due to an internal communication error
         * \n        ERROR_INVALID_ARGUMENT if operation failed due to invalid argument passed to the API
         */	
		virtual SubscribeRetVal_type can_subscribeFrame(eCANBusName canbusname, std::list<uint16_t> FrameID, void(FrameCallback)(CANFrameData_type &), eFilter_Mode filtermode, uint16_t sampling = 1 ) = 0;
				
		
		/**
         * @brief get SignalLastValue of CAN Service 
         *
         * @param [in]  canbusname  : CAN BUS NAME
		 * @param [in]  signal_list : Requested signal list
		 * @param [out] signalValue : For each signal ID		
		 *
         * @return   SUCCESS if the operation is succesful
         * \n        ERROR if the operation failed due to an internal communication error
         * \n        ERROR_INVALID_ARGUMENT Returned when an invalid argument is passed to the API 
		 * \n        ERROR_NOT_SUPPORTED Returned while triggering unsupported interfaces on current Architecture 
		 * \n        ERROR_FRAME_UNINITIALIZED Returned in case of operation failure due to CAN Frame not received yet  
		 */		
		 
		virtual CAN_Error_t can_getSignalLastValue(eCANBusName canbusname, std::list<uint32_t> signal_list, std::list<CANSignalData_type> signalValue) = 0;
		
		/**
         * @brief subscribe to CAN signal 
         *
         * @param [in]  canbusname : CAN BUS NAME
		 * @param [in]  signal_list : Requested signal list
		 * @param [in]  SignalCallback : CAN signal callback function
		 * @param [in]  filtermode :  Filter Mode
		 * @param [in]  sampling : Sampling value.		
		 *			A CAN frame is forwarded to the modem every “sampling” 
		 *			received frames.		
		 *			Example		
		 *			Sampling = 1 all frames are forwarded		
		 *			Sampling = 2, one out of two is forwarded		
		 *			Sampling = 3, one out of three is forwarded	
		 *
         * @return   Return the subrscription id and error code
		 * \n 		 SUCCESS if the operation is succesful
         * \n        ERROR if the operation failed due to an internal communication error
         * \n        ERROR_INVALID_ARGUMENT if operation failed due to invalid argument passed to the API
         */		
		virtual SubscribeRetVal_type can_subscribeSignal(eCANBusName canbusname, std::list<uint32_t> signal_list, void(SignalCallback)(CANSignalData_type &), eFilter_Mode filtermode, uint16_t sampling = 1) = 0;
		
		/**
         * @brief subscribe to CAN signal for better performance
         *
         * @param [in]  canbusname : CAN BUS NAME
		 * @param [in]  signal_list : Requested signal list
		 * @param [in]  SignalCallback : CAN signal callback function
		 * @param [in]  filtermode :  Filter Mode
		 * @param [in]  sampling : Sampling value.		
		 *			A CAN frame is forwarded to the modem every “sampling” *			received frames.		
		*			Example		
		*			Sampling = 1 all frames are forwarded		
		*			Sampling = 2, one out of two is forwarded		
		*			Sampling = 3, one out of three is forwarded	
		 *
         * @return   Return the subrscription id and error code
		 * \n 		 SUCCESS if the operation is succesful
         * \n        ERROR if the operation failed due to an internal communication error
         * \n        ERROR_INVALID_ARGUMENT if operation failed due to invalid argument passed to the API
         */		
		virtual SubscribeRetVal_type can_subscribeRTSignal(eCANBusName canbusname, std::list<uint32_t> signal_list, void(SignalCallback)(CANSignalData_type &), eFilter_Mode filtermode, uint16_t sampling = 1) = 0;
        
		/**
         * @brief get can signal cache 
         *
         * @param [in]   canbusname : CAN BUS NAME
		 * @param [in]   signal_list : Requested signal list
		 * @param [in] 	 historyDuration :  Duration of the CAN history 
		 * @param [out]  signalValue : For each signal ID		
		 *
         * @return   SUCCESS if the operation is succesful
         * \n        ERROR if the operation failed due to an internal communication error
         * \n        ERROR_INVALID_ARGUMENT Returned when an invalid argument is passed to the API 
		 * \n        ERROR_NOT_SUPPORTED Returned while triggering unsupported interfaces on current Architecture 
		 * \n        ERROR_CACHE_NOT_READY Returned in case if the API is invoked before the cache becomes ready 
		 * \n        ERROR_MEMORY_FULL  Returned in case if there is no memory available 	
         */	
		virtual CAN_Error_t can_getSignalCache(eCANBusName canbusname, std::list<uint32_t> signal_list, uint8_t historyDuration, std::list<CANSignalData_type> signalValue)= 0;		
		
		
		/**
        @brief    All subclasses of Service must override the type() and isA() member functions.
        * for more details see : https://pocoproject.org/pro/docs/Poco.OSP.Service.html
        */
		
        /**
        * @brief Returns the type information for the object's class
        */
        const std::type_info &type() const
        {
                return typeid(ICanService);
        }
		
        /**
        * @brief Returns true if the class is a subclass of the class given by otherType.
        */
        bool isA(const std::type_info &otherType) const
        {
                std::string name(typeid(ICanService).name());
                return name == otherType.name() || Service::isA(otherType);
        }
};

} /* namespace CanService*/
} /* Namespace Stla*/

#endif
