/**
 * \file
 *         ILoggingServiceTypes.h
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

#include <string>
#include <list>
#ifndef LOGGING_SERVICE_TYPES_H_
#define LOGGING_SERVICE_TYPES_H_

namespace Stla
{
namespace LoggingService
{

/**
 * \brief The Logging_Error_t defines different Logging service interface return types.
 */
//@serialize  
enum Logging_Error_t
{
    SUCCESS,                  /**< Returned in case of success operation */
    ERROR                    /**< Returned in case of operation failure due to an internal communication error */    
};


} // namespace LoggingService
} // namespace Stla

#endif
