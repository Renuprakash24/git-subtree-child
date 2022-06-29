/**
 * \file
 *         IRemoteAccessServiceTypes.h
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

#include <vector>
#ifndef TCU_REMOTE_ACCESS_SERVICE_TYPES_H_
#define TCU_REMOTE_ACCESS_SERVICE_TYPES_H_

namespace Stla
{
namespace RemoteAccessService
{
/**
 * \brief The RAS_Error_t defines different Remote access service interface return types.
 */
//@serialize
enum RAS_Error_t
{
    RAS_SUCCESS,                  /**< Returned in case of success operation */
    RAS_ERROR,                    /**< Returned in case of operation failure due to an internal communication error */
    RAS_ERROR_INVALID_ARGUMENT,   /**< Returned when an invalid argument is passed to the API */    
    RAS_ERROR_NOT_SUPPORTED      /**< Returned while triggering unsupported interfaces/Signals on current Architecture */
   
};
} // namespace RemoteAccessService
} // namespace Stla

#endif
