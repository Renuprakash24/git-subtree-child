/**
 * \file
 *         ILoggingService.h
 * \brief
 *         Logging Service API
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
 
#ifndef LOGGING_SERVICE_INTERFACE_H_
#define LOGGING_SERVICE_INTERFACE_H_

/****************** Includes ************************
 ***************************************************/

/* Poco library includes */

#include "Poco/OSP/Service.h"
#include "Poco/AutoPtr.h"
#include <string>
#include "Poco/BasicEvent.h"

//To do - Logger file header addition
#include "Poco/Logger.h

/* Logging Service bundle includes */

#include "ILoggingServiceTypes.h"
	
namespace Stla
{
namespace LoggingService
{
/**
 * @brief The logging service shall provide an interface to trigger the * saving of logs in persistent storage. 
 * The interface shall enable to
 * trigger the saving of logs according to a filter based on 
 * application id and context id.
 * If no filter is given, all logs are to be saved.
 * activate the saving of logs automatically in the next system
 * lifecycles. 
 *
 */

static const std::string LOGGING_SERVICE_INTERFACE = "stla.networking.logging.service.base";

#ifdef DOXYGEN_WORKING
class ILoggingService : public Poco::OSP::Service
#else
class __attribute__((visibility("default"))) ILoggingService : public Poco::OSP::Service
#endif
{
public:
		/* Pointer to Service interface*/
        typedef Poco::AutoPtr<ILoggingService> Ptr;

        /**
         * @brief Destroy the ILoggingService object
         *   
		 */
        virtual ~ILoggingService() {}
		
		/**
         * @brief Starts storing logs in a file until stopLogStorage is called Parallel requests are not supported. All the following requests are ignored
         *
         * @param[in]   loglevel : POCO priority 
		 * @param[in]   filter :  (AppId+ CtxID) provided by App to reduce log size. The filter format is "ApplicationId ContextId, ApplicationId ContextId, ...".
		 *\n Example: "MCH3 DALC, SYS JOUR, MCH1 EINI"
		 * @param[in]  nLC_activation : Nb of cycles given by application for automatic activation at start up. Maximum to be defined with STLA.		 		 
		 * @return  Returns 1 for valid request
         * \n       Returns 0 if the request is ignored.
         */
		 //To Do 
		virtual bool startLogStorage(Poco::Priority loglevel, std::string filter ,  int nLC_activation) = 0;	

		/**
		 * @brief Stops the storing logs if already started. 
		 \n This is \b implicit request if LOG_STORAGE_LIMIT is reached.
		 \n The request is ignored , if startLogStorage() was not initiated or if already LOG_STORAGE_LIMIT is reached.
		 * @return  Returns 1 for valid request
         * \n       Returns 0 if the request is ignored.
        */
		virtual bool stopLogStorage() = 0;
		
		/**
         * @brief Get Stored Logs 
         *
         * @param[in]   logType : Based on the architecture, log type can be "Full TCU trace or NAD" 
		 * @return  Returns the file descriptor to the last log storage file. 
         * \n       Returns -1 if there is no such file
         */
		virtual int getStoredLogs(int logType=0) = 0;
		
		/**
		 * @brief Notify when log storage stops (stopLogStorage request or reaching LOG_STORAGE_LIMIT)
		*/
		Poco::BasicEvent<void> logStorageStopped;
		
		/**
		 * @brief clearLogStorage function to clear all stored logs 
		 * @return  SUCCESS if Log storage is cleared
         * \n       ERROR if operation is failed 
        */
		virtual Logging_Error_t clearLogStorage() = 0; 
				
        /**
        * @brief Returns the type information for the object's class
        */
        const std::type_info &type() const
        {
                return typeid(ILoggingService);
        }
        /**
        * @brief Returns true if the class is a subclass of the class given by otherType.
        */
        bool isA(const std::type_info &otherType) const
        {
                std::string name(typeid(ILoggingService).name());
                return name == otherType.name() || Service::isA(otherType);
        }
};

} /* namespace ILoggingService*/
} /* Namespace Stla*/
#endif
