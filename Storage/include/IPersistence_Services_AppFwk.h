#ifndef IPERSSERVICES_APPFWK_H
#define IPERSSERVICES_APPFWK_H

 /**
 * \file
 *         IPersistence_Services_AppFwk.h
 * \brief
 *         Persistence Macchina API
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

/***** INCLUDES ***********************************************************/

#include "Poco/OSP/Service.h"
#include "Poco/AutoPtr.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/Poco.h"
#include "Poco/OSP/SystemEvents.h"

#if !defined(Persistence_Services_AppFwk_API)
#define Persistence_Services_AppFwk_API
#endif

#define PERSISTENCE_SERVICE_APPFWK_NAME                              ("com.stellantis.PersistenceServiceAppFwk")

/* To Do- #define values are yet to be defined. The value provided here are example */
/*#define PERSISTENCE_SERVICE_NAME_MAX_SZ                              (100)
#define PERSISTENCE_SERVICES_KEYNAME_MAX_SZ                          (100)

#define PERSISTENCE_SERVICES_KEY_MAX_SZ                              (5 * 1024 * 1024)*/
/* Maximum size of an encrypted/critical key */
/*#define PERSISTENCE_SERVICES_SECURED_KEY_MAX_SZ                      (25 * 1024) 
#define PERSISTENCE_SERVICES_QUOTA_MAX                               (PERSISTENCE_SERVICES_KEY_MAX_SZ)*/

#define PERSISTENCE_SERVICES_SERVICENAME_FOR_PUBLIC_ACCESS           ("PUBLIC_SRV")
#define PERSISTENCE_SERVICES_SERVICENAME_FOR_PUBLIC_CRITICAL_ACCESS  ("PUBLIC_SEC")


/***** TYPEDEFS ***********************************************************/

/**
 * @brief Pcl error type information
 */
 //@serialize
typedef enum pcl_error
{
    PCL_ERROR_NONE         = 0,                    /**< No error (success) */
    PCL_ERROR_GENERIC      = -99,                  /**< Other error, a call to the persistence provided by OTP failed */
    PCL_ERROR_INVALID_ARG,                         /**< Invalid argument */
    PCL_ERROR_INTERNAL,                            /**< Internal error */
    PCL_ERROR_ACCESS_DENIED,                       /**< Access denied */
    PCL_ERROR_NO_QUOTA,                            /**< Not enough space available */
    PCL_ERROR_KEY_EXISTS,                          /**< A key with the same name already exists */
    PCL_ERROR_SERVICE_DISABLED,                    /**< Service disabled */
    PCL_ERROR_KEY_NOT_FOUND                        /**< The key was not found */
} PCL_Error_t;

/**
 * @brief Pcl notification status information
 */
 //@serialize
typedef enum pcl_notification_status
{
    PCL_STATUS_NO_CHANGE      = 0,                 /**< No status change */
    PCL_STATUS_CREATED,                            /**< Status was created */
    PCL_STATUS_MODIFIED,                           /**< Status was modified */
    PCL_STATUS_DELETED,                            /**< Status was deleted */
    PCL_STATUS_RECOVERED_TO_DEFAULT,               /**< Status was recovered to default */
} PCL_Client_NotifyStatus_t;

/**
 * @brief Persistence database state
 */
 //@serialize
typedef enum pcl_database_state
{
    PCL_DB_STATE_UNKNOWN = 0,               /**< no info available about public database state */
    PCL_DB_STATE_NORMAL,                    /**< database OK */
    PCL_DB_STATE_CORRUPTED,                 /**< database has been corrupted and the system services are recovering mandatory info */
    PCL_DB_STATE_RESTORED_TO_DEFAULT,       /**< database has been corrupted and restored, applications can start recreating their keys */

    PCL_DB_STATE_LAST                       /**< used in range checks */
} PCL_Client_DatabaseState_t;

/**
 * @brief Pcl change notification structure
 */
 //@serialize
typedef struct pcl_change_notification
{
    PCL_Client_NotifyStatus_t   notify_status;     /**< Notify status type of PCL_Client_NotifyStatus_t */
    int                         not_used;          /**< Not used flag */
    const char                  *key_id;           /**< Name of key id */
} PCL_Client_ChangeNotification_t;

typedef PCL_Error_t (* ChangeNotifyFuncPtr_t)(PCL_Client_ChangeNotification_t *pclClientKeyNotifyInfo);


namespace Stla {
namespace Persistence {

/***** CLASSES ************************************************************/
class Persistence_Services_AppFwk_API IPersistence_Services_AppFwk: public Poco::OSP::Service
{
public:
    /**
     * @brief Ptr is an auto pointer of IPersistence_Services_AppFwk class type
     */
    typedef Poco::AutoPtr<IPersistence_Services_AppFwk> Ptr;

    /**
     * @brief IPersistence_Services_AppFwk constructor
     */
    IPersistence_Services_AppFwk()
    {

    }

    /**
     * @brief IPersistence_Services_AppFwk destructor
     */
    ~IPersistence_Services_AppFwk()
    {

    }

    /**
     * IPersistence_Services_AppFwk Events
     */

    /**
     * @brief DatabaseStateChanged Event triggered on database corruption recovery notification
     */

    Poco::BasicEvent<PCL_Client_DatabaseState_t> DatabaseStateChanged;

    /**
     * IPersistence_Services_AppFwk Interfaces
     */

    /**
     * @brief Create an empty critical key of type byte array in database.
     * @param[in] bundle_symbolic_name: bundle symbolic name extracted from bundle context.If bundle_symbolic_name is NULL, the data is shared.
	 If bundle_symbolic_name is filled and match, the data is private.
     * @param[in] key_id: key name
     * @param[in] max_size: maximum size of this byte array (but not more than PERSISTENCE_SERVICES_SECURED_KEY_MAX_SZ)
     * @return PCL_ERROR_NONE if successful
     * \n      PCL_ERROR_GENERIC if calls to the persistence provided by OTP fail
     * \n      PCL_ERROR_INVALID_ARG if key_id is NULL or if any param has invalid size
     * \n      PCL_ERROR_INTERNAL if max_size is 0 or for internal errors
     * \n      PCL_ERROR_NO_QUOTA if there is not enough space available
     * \n      PCL_ERROR_KEY_EXISTS if a key with the same name already exists
     * \n      PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_keyCreateByteArrayCritical(const unsigned char *bundle_symbolic_name, const unsigned char *key_id, unsigned int max_size) = 0;

    /**
     * @brief Remove app related keys from database
     * @param[in] bundle_symbolic_name: bundle symbolic name extracted from bundle context.If bundle_symbolic_name is NULL, the data is shared.
	 If bundle_symbolic_name is filled and match, the data is private.
     * @return PCL_ERROR_NONE if successful
     * \n      PCL_ERROR_GENERIC if calls to the persistence provided by OTP fail
     * \n      PCL_ERROR_INVALID_ARG if param is NULL or length is 0
     * \n      PCL_ERROR_INTERNAL for internal errors
     * \n      PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_removeAppKeys(const unsigned char *bundle_symbolic_name) = 0;

    /**
     * @brief Create an empty critical key of type int in database.
     * @param[in] bundle_symbolic_name: bundle symbolic name extracted from bundle context.If bundle_symbolic_name is NULL, the data is shared.
	 If bundle_symbolic_name is filled and match, the data is private.
     * @param[in] key_id: key name
     * @return PCL_ERROR_NONE if successful
     * \n      PCL_ERROR_GENERIC if calls to the persistence provided by OTP fail
     * \n      PCL_ERROR_INVALID_ARG if any param is NULL or has invalid size
     * \n      PCL_ERROR_INTERNAL for internal errors like encoding or memory allocation errors
     * \n      PCL_ERROR_NO_QUOTA if there is not enough space available
     * \n      PCL_ERROR_KEY_EXISTS if a key with the same name already exists
     * \n      PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_keyCreateIntCritical(const unsigned char *bundle_symbolic_name, const unsigned char *key_id) = 0;


    /**
     * @brief Delete a critical key from the database.
     * @param[in] bundle_symbolic_name: bundle symbolic name extracted from bundle context.If bundle_symbolic_name is NULL, the data is shared.
	 If bundle_symbolic_name is filled and match, the data is private.
     * @param[in] key_id: key name
     * @return  PCL_ERROR_NONE if successful
     * \n       PCL_ERROR_KEY_NOT_FOUND if the key was not found
     * \n       PCL_ERROR_GENERIC if calls to the persistence provided by OTP fail
     * \n       PCL_ERROR_INVALID_ARG if any param is NULL or has invalid size
     * \n       PCL_ERROR_INTERNAL for internal errors
     * \n       PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_keyDeleteCritical(const unsigned char *bundle_symbolic_name, const unsigned char *key_id) = 0;

    /**
     * @brief Create an empty key of type byte array in database.
     * @param[in] bundle_symbolic_name: bundle symbolic name extracted from bundle context.If bundle_symbolic_name is NULL, the data is shared.
	 If bundle_symbolic_name is filled and match, the data is private.
     * @param[in] key_id: key name
     * @param[in] max_size: maximum size of this byte array (but not more than PERSISTENCE_SERVICES_KEY_MAX_SZ)
     * @return  PCL_ERROR_NONE if successful
     * \n       PCL_ERROR_GENERIC if calls to the persistence provided by OTP fail
     * \n       PCL_ERROR_INVALID_ARG if key_id is NULL or if any param has invalid size
     * \n       PCL_ERROR_INTERNAL if max_size is 0 or for internal errors
     * \n       PCL_ERROR_NO_QUOTA if there is not enough space available
     * \n       PCL_ERROR_KEY_EXISTS if a key with the same name already exists
     * \n       PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_keyCreateByteArray(const unsigned char *bundle_symbolic_name, const unsigned char *key_id, unsigned int max_size) = 0;


    /**
     * @brief Create an empty key of type int in database.
     * @param[in] bundle_symbolic_name: bundle symbolic name extracted from bundle context.If bundle_symbolic_name is NULL, the data is shared.
	 If bundle_symbolic_name is filled and match, the data is private.
     * @param[in] key_id: key name
     * @return  PCL_ERROR_NONE if successful
     * \n       PCL_ERROR_GENERIC if calls to the persistence provided by OTP fail
     * \n       PCL_ERROR_INVALID_ARG if any param is NULL or has invalid size
     * \n       PCL_ERROR_INTERNAL for internal errors like encoding or memory allocation errors
     * \n       PCL_ERROR_NO_QUOTA if there is not enough space available
     * \n       PCL_ERROR_KEY_EXISTS if a key with the same name already exists
     * \n       PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_keyCreateInt(const unsigned char *bundle_symbolic_name, const unsigned char *key_id) = 0;


    /**
     * @brief Delete a key from the database.
     * @param[in] bundle_symbolic_name: bundle symbolic name extracted from bundle context.If bundle_symbolic_name is NULL, the data is shared.
	 If bundle_symbolic_name is filled and match, the data is private.
     * @param[in] key_id: key name
     * @return  PCL_ERROR_NONE if successful
     * \n       PCL_ERROR_KEY_NOT_FOUND if the key was not found
     * \n       PCL_ERROR_GENERIC if calls to the persistence provided by OTP fail
     * \n       PCL_ERROR_INVALID_ARG if any param is NULL or has invalid size
     * \n       PCL_ERROR_INTERNAL for internal errors
     * \n       PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_keyDelete(const unsigned char *bundle_symbolic_name, const unsigned char *key_id) = 0;


    /**
     * @brief Read a key of type byte array from the database.
     * @brief Key must be created and written before calling this function.
     * @param[in] bundle_symbolic_name: bundle symbolic name extracted from bundle context.If bundle_symbolic_name is NULL, the data is shared.
	 If bundle_symbolic_name is filled and match, the data is private.
     * @param[in] key_id: key name
     * @param[in] size: size of out buffer
     * @param[out] buffer: out buffer - allocated by user
     * @return  PCL_ERROR_NONE if successful
     * \n       PCL_ERROR_KEY_NOT_FOUND if the key was not found
     * \n       PCL_ERROR_GENERIC if call to OTP function tpPCL_keyReadData fails
     * \n       PCL_ERROR_INVALID_ARG if key_id is NULL or have invalid size, if buffer is NULL
     * \n       PCL_ERROR_INTERNAL for internal errors
     * \n       PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_KeyReadByteArray(const unsigned char *bundle_symbolic_name, const unsigned char *key_id, const int size, unsigned char *buffer) = 0;


    /**
     * @brief write a key of type byte array from the database.
     * @brief Key must be created before calling this function.
     * @param[in] bundle_symbolic_name: bundle symbolic name extracted from bundle context.If bundle_symbolic_name is NULL, the data is shared.
	 If bundle_symbolic_name is filled and match, the data is private.
     * @param[in] key_id: key name
     * @param[in] size: size of in buffer
     * @param[in] buffer: in buffer - provided by user
     * @return  PCL_ERROR_NONE if successful
     * \n       PCL_ERROR_KEY_NOT_FOUND if the key was not found
     * \n       PCL_ERROR_GENERIC if call to OTP function tpPCL_keyWriteData fails
     * \n       PCL_ERROR_INVALID_ARG if key_id is NULL or have invalid size, if buffer is NULL
     * \n       PCL_ERROR_INTERNAL for internal errors
     * \n       PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_KeyWriteByteArray(const unsigned char *bundle_symbolic_name, const unsigned char *key_id, const int size, unsigned char *buffer) = 0;


    /**
     * @brief Get the size a key of type byte array from the database.
     * @brief Key must be created and written before calling this function.
     * @param[in] bundle_symbolic_name: bundle symbolic name extracted from bundle context.If bundle_symbolic_name is NULL, the data is shared.
	 If bundle_symbolic_name is filled and match, the data is private.
     * @param[in] key_id: key name
     * @param[out] size: actual size of key
     * @return  PCL_ERROR_NONE if successful
     * \n       PCL_ERROR_KEY_NOT_FOUND if the key was not found
     * \n       PCL_ERROR_GENERIC if call to OTP function tpPCL_keyGetSize fails
     * \n       PCL_ERROR_INVALID_ARG if any param is NULL, if bundle_symbolic_name or key_id have invalid size
     * \n       PCL_ERROR_INTERNAL for internal errors
     * \n       PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_KeyGetSize(const unsigned char *bundle_symbolic_name, const unsigned char *key_id, int *size) = 0;


    /**
     * @brief Read a key of type int from the database.
     * @brief Key must be created and written before calling this function.
     * @param[in] bundle_symbolic_name: bundle symbolic name extracted from bundle context.If bundle_symbolic_name is NULL, the data is shared.
	 If bundle_symbolic_name is filled and match, the data is private.
     * @param[in] key_id: key name
     * @param[out] value: int type value
     * @return  PCL_ERROR_NONE if successful
     * \n       PCL_ERROR_KEY_NOT_FOUND if the key was not found
     * \n       PCL_ERROR_GENERIC if call to OTP function tpPCL_keyReadData fails
     * \n       PCL_ERROR_INVALID_ARG if any param is NULL, if bundle_symbolic_name or key_id have invalid size
     * \n       PCL_ERROR_INTERNAL for internal errors
     * \n       PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_KeyReadInt(const unsigned char *bundle_symbolic_name, const unsigned char *key_id, unsigned int *value) = 0;


    /**
     * @brief Write a key of type int from the database.
     * @brief Key must be created before calling this function.
     * @param[in] bundle_symbolic_name: bundle symbolic name extracted from bundle context.If bundle_symbolic_name is NULL, the data is shared.
	 If bundle_symbolic_name is filled and match, the data is private.
     * @param[in] key_id: key name
     * @param[in] value: int type value
     * @return  PCL_ERROR_NONE if successful
     * \n       PCL_ERROR_KEY_NOT_FOUND if the key was not found
     * \n       PCL_ERROR_GENERIC if call to OTP function tpPCL_keyWriteData fails
     * \n       PCL_ERROR_INVALID_ARG if key_id is NULL or have invalid size
     * \n       PCL_ERROR_INTERNAL for internal errors
     * \n       PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_KeyWriteInt(const unsigned char *bundle_symbolic_name, const unsigned char *key_id, unsigned int value) = 0;


    /**
     * @brief Register an application for notification on key update.
     * @param[in] bundle_symbolic_name: bundle symbolic name extracted from bundle context.If bundle_symbolic_name is NULL, the data is shared.
	 If bundle_symbolic_name is filled and match, the data is private.
     * @param[in] key_id: key name
     * @param[in] callback: type ChangeNotifyFuncPtr_t callback function
     * @return  PCL_ERROR_NONE if successful
     * \n       PCL_ERROR_KEY_NOT_FOUND if the key was not found
     * \n       PCL_ERROR_GENERIC if call to OTP function tpPCL_keyRegisterNotifyOnChange fails
     * \n       PCL_ERROR_INVALID_ARG if key_id is NULL or have invalid size
     * \n       PCL_ERROR_INTERNAL for internal errors
     * \n       PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_keyRegisterNotifyOnChange(const unsigned char *bundle_symbolic_name, const unsigned char *key_id, ChangeNotifyFuncPtr_t callback) = 0;


    /**
     * @brief Query how much of the quota is used
     * @param[out] used_space: How much space of the quota is used
     * @return  PCL_ERROR_NONE if successful
     * \n       PCL_ERROR_GENERIC if call to OTP function tpPCL_keyReadData fails
     * \n       PCL_ERROR_INVALID_ARG if used_space is NULL
     * \n       PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_getUsedSpace(unsigned int *used_space) = 0;


    /**
     * @brief Query how much space is still available of the quota
     * @param[out] remaining_space: How much space of the quota is remaining
     * @return  PCL_ERROR_NONE if successful
     * \n       PCL_ERROR_GENERIC if call to OTP function tpPCL_keyReadData fails
     * \n       PCL_ERROR_INVALID_ARG if remaining_space is NULL
     * \n       PCL_ERROR_SERVICE_DISABLED if service is disabled
     */
    virtual PCL_Error_t pcl_getRemainingSpace(unsigned int *remaining_space) = 0;

    /**
     * @brief  Returns the current database state
     * @return  PCL_DB_STATE_NORMAL if no recovery occured
     * \n       PCL_DB_STATE_CORRUPTED if database has been corrupted and the system services are recovering mandatory info
     * \n       PCL_DB_STATE_RESTORED_TO_DEFAULT if database has been corrupted and restored, applications can start recreating their keys
     */
    virtual PCL_Client_DatabaseState_t pcl_getDatabaseState() = 0;

};

} }

#endif
