/**
 * \file
 *          ILifecycleMonitorTypes.h
 *
 * \brief
 *          Types defined for the LifecycleMonitor
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

#ifndef ILIFECYCLEMONITORTYPES_H
#define ILIFECYCLEMONITORTYPES_H

#include <list>
#include <string>
#include <map>

namespace Stla
{
namespace AppFwk
{

#define AFWK_EARLY_INIT_SERVICE "stla.appfwk.einitbundle.service"

/**
* @brief General */
//@serialize
typedef enum
{
    E_LCM_RET_SUCCESS,                 /**< Call succeeds*/
    E_LCM_RET_FAILURE,                 /**< Generic failure */
    E_LCM_RET_INVALID_ARG,             /**< Invalid input argument */
    E_LCM_RET_DUPLICATE_REG,           /**< Duplicated registration for TCU STM service */
    E_LCM_RET_NOT_REGISTERED,          /**< Application not registered for TCU STM service */
    E_LCM_RET_INTERNAL_ERR,            /**< Internal error */
    E_LCM_RET_NO_PERM,                 /**< Operation not allowed */
    E_LCM_RET_BUSY,                    /**< TCU service cannot respond, try again */
    E_LCM_NO_ERROR                     /**< No error occured*/
}ELCM_ErrorType;

/**
* @brief App */
//@serialize
typedef enum
{
    E_LCM_AppState_INITIALIZING,        /**< Initial state of an application */
    E_LCM_AppState_IDLE,                /**< Application initialized but not functional */
    E_LCM_AppState_NORMAL               /**< Application fully functional */
}ELCM_AppState;

//@serialize
typedef enum
{
    E_LCM_REASON_NONE,						/**< No LCM Reason */
    E_LCM_REASON_SHUTDOWN,                  /**< The system is going to shutdown */
    E_LCM_REASON_SUSPEND_RAM,               /**< The system is entering low power mode */
    E_LCM_REASON_REBOOT,                    /**< The system is going to reboot */
    E_LCM_REASON_SERVICES_READY,            /**< All dependecies are in E_LCM_SRV_AVAILABLE state*/
    E_LCM_REASON_SERVICES_NOT_READY         /**< At least one of the dependencies is in E_LCM_SRV_UNAVAILABLE/E_LCM_SRV_INITIALIZING state */
}ELCM_Reason;

typedef struct
{
    ELCM_AppState state;                /**< The state an application has to enter */
    ELCM_Reason reason;                 /**< The reason behind the transition to the new state */
}SLCM_AppState_t;

/**
* @brief Service */
//@serialize
typedef enum
{
    E_LCM_SRV_UNAVAILABLE,              /**< The service is initialized but not functional */
    E_LCM_SRV_INITIALIZING,             /**< Initial state of a service */
    E_LCM_SRV_AVAILABLE                 /**< The service is fully functional */
}ELCM_SrvState_t;

/** This structure is used by services to notify Init bundle when they enter a new state
 *  To notify a state change, use notifySrvState from ILCServiceNotify.h */
typedef struct
{
    ELCM_SrvState_t state;                  /**< The state entered by the service */
    std::string serviceName;                /**< The name of the service which changed it's state */
}SLCM_SrvState_t;

//@serialize
typedef enum
{
    E_LCM_DIS_REASON_NOT_ALLOWED,                    /**< Shutdown procedure ongoing */
    E_LCM_DIS_REASON_LOW_POWER,                      /**< Suspend to RAM procedure ongoing */
    E_LCM_DIS_REASON_DEPS_UNAVAILABLE                /**< At least one of the dependencies is in E_LCM_SRV_UNAVAILABLE/E_LCM_SRV_INITIALIZING state */
}ELCM_SrvDisableReason_t;


typedef std::map<std::string, ELCM_SrvState_t> TServiceList;

//Lifecycle service defines override

typedef int                       lcm_RtcAlarmHandle_t;

//@serialize
typedef enum e_lcm_LifecycleState_t
{
    E_LCM_ST_EMERGENCY    = 0,           /**< Ecall in progress */
    E_LCM_ST_NOMINAL      = 1,           /**< Normal operation state */
    E_LCM_ST_UPDATE       = 3,           /**< Software update in progress */
    E_LCM_ST_BEFORE_SLEEP = 4,           /**< Shutdown in progress */
    E_LCM_ST_LAST                        /**< Undefined behavior*/
} lcm_LifecycleState_t;

//@serialize
typedef enum e_lcm_CANNetworkState_t
{
    E_LCM_CAN_OFF,                      /**< CAN Network is InActive */
    E_LCM_CAN_ON,                       /**< CAN Network is Active */
    E_LCM_CAN_OFF_TO_CAUSE,             /**< CAUSE_X timeout - CAN Network is Inactive */
    E_LCM_CAN_LAST                      /**< Undefined behavior*/
} lcm_CANNetworkState_t;

//@serialize
typedef enum e_lcm_ParkModeState_t
{
    E_LCM_PARK_MODE_OFF,                /**< Park Mode is InActive */
    E_LCM_PARK_MODE_ON,                 /**< Park Mode is Active */
    E_LCM_PARK_MODE_LAST                /**< Undefined behavior*/
} lcm_ParkModeState_t;

typedef struct s_lcm_RtcAlarmCreated_t
{
    /**
     * Global alarm handle to be used for delete/expire events
     */
    lcm_RtcAlarmHandle_t           alarmHandle;

    /**
     * Internal index obtained in lcm_createRTCAlarm to be used to pair with the handle received in RtcAlarmCreatedEvent
     */
    unsigned int                  index;
} lcm_RtcAlarmCreated_t;

/**
 * @brief Bub status information
 */
 //@serialize
typedef enum e_lcm_BackupBatteryStatus_t
{
    E_LCM_BUB_ABSENT,                     /**< backup battery is absent */
    E_LCM_BUB_BROKEN,                     /**< backup battery is broken  */
    E_LCM_BUB_INACTIVE_CHARGING,          /**< backup battery is inactive and charging */
    E_LCM_BACKUP_BATTERY_INACTIVE,        /**< BUB is inactive - not in use  */
    E_LCM_BACKUP_BATTERY_ACTIVE,          /**< BUB is active power source  */
    E_LCM_BACKUP_BATTERY_LAST             /**< Undefined behavior*/
} lcm_BackupBatteryStatus_t;

/**
 * @brief Bub state of charge
 */
typedef enum e_lcm_BuBSOC_t
{
    E_LCM_BUB_SOC_ABSENT_OR_BROKEN = 0,   /**< Backup battery is absent or broken */
    E_LCM_BUB_SOC_VERY_LOW,               /**< Backup battery state of charge is verry low */
    E_LCM_BUB_SOC_LOW,                    /**< Backup battery state of charge is low */
    E_LCM_BUB_SOC_HIGH,                   /**< Backup battery state of charge is high, but not full */
    E_LCM_BUB_SOC_FULL,                   /**< Backup battery state of charge is full */
    E_LCM_SOC_BUB_INVALID_LAST            /**< Undefined behavior*/
} lcm_BuBSOC_t;

/**
 * @brief Bub state of health
 */
 //@serialize
typedef enum e_lcm_BuBSOH_t
{
    E_LCM_SOH_BUB_ABSENT = 0,   /**< Backup battery is absent */
    E_LCM_SOH_BUB_BROKEN,       /**< Backup battery broken */
    E_LCM_SOH_BUB_OPERATIONAL,  /**< Backup battery is operational. state of health is OK  */
    E_LCM_SOH_BUB_IN_PROGRESS,  /**< Backup battery state of health test in progress or not yet performed */
    E_LCM_SOH_BUB_LAST          /**< Undefined behavior*/
} lcm_BuBSOH_t;

//@serialize
typedef enum e_lcm_KeepAwakeRequest_t
{
    E_LCM_KEEPAWAKE_INACTIVE,           /**< Notify end of keep awake, always calls it after Keep awake request ends */
    E_LCM_KEEPAWAKE_ACTIVE,             /**< Notify start of keep awake request */
    E_LCM_KEEPAWAKE_LAST                /**< Undefined behavior*/
} lcm_KeepAwakeRequest_t;

/**
 * @brief  Description of keep awake status
 */
 //@serialize
typedef enum e_lcm_KeepAwakeStatus_t
{
    E_LCM_KA_STATUS_INACTIVE,                  /**< Keep awake inactive */
    E_LCM_KA_STATUS_ACTIVE,                    /**< Keep awake active */
    E_LCM_KA_STATUS_FINISHED,                  /**< Keep awake finished */
    E_LCM_KA_STATUS_RJCT_ON_BUB,               /**< Keep awake request rejected while system is running on BUB */
    E_LCM_KA_STATUS_RJCT_FORCED_SHUTDOWN,      /**< Keep awake request rejected during forced shutdown */
    E_LCM_KA_STATUS_RJCT_WRONG_STATE,          /**< Keep awake request rejected because it was sent in wrong LC state */
    E_LCM_KA_STATUS_RJCT_APP_SHUTDOWN,         /**< Keep awake request rejected during application shutdown */
    E_LCM_KA_STATUS_PENDING,                   /**< Waiting for response */
    E_LCM_KA_STATUS_LAST                       /**< Undefined behavior*/
} lcm_KeepAwakeStatus_t;

//@serialize
typedef enum e_lcm_CauseX_t
{
    E_LCM_CAUSE_NONE = 0,           /**< Cause_x 0 */
    E_LCM_CAUSE_1,                  /**< Cause_x 1 */
    E_LCM_CAUSE_2,                  /**< Cause_x 2 */
    E_LCM_CAUSE_3,                  /**< Cause_x 3 */
    E_LCM_CAUSE_4,                  /**< Cause_x 4 */
    E_LCM_CAUSE_5,                  /**< Cause_x 5 */
    E_LCM_CAUSE_6,                  /**< Cause_x 6 */
    E_LCM_CAUSE_7,                  /**< Cause_x 7 */
    E_LCM_CAUSE_8,                  /**< Cause_x 8 */
    E_LCM_CAUSE_LAST                /**< Undefined behavior*/
} lcm_CauseX_t;

//@serialize
typedef enum e_lcm_WakeupReason_t
{
    E_LCM_WAKEUP_CAN,               /**< Can wakeup reason */
    E_LCM_WAKEUP_ECALL,             /**< Ecall/Acall wakeup reason */
    E_LCM_WAKEUP_BCALL,             /**< Deprecated */
    E_LCM_WAKEUP_POWER_SUPPLY_LOST, /**< Power supply wakeup reason */
    E_LCM_WAKEUP_SMS,               /**< Sms wakeup reason */
    E_LCM_WAKEUP_DATA,              /**< Data wakeup reason */
    E_LCM_WAKEUP_RTC,               /**< Deprecated */
    E_LCM_WAKEUP_VEHICLE_MOVEMENT,  /**< Vehicle movement wakeup reason */
    E_LCM_WAKEUP_VOICE_CALL,        /**< Voice call wakeup reason */
    E_LCM_WAKEUP_GPT,               /**< General Purpose Timer expired wakeup reason */
    E_LCM_WAKEUP_GENERIC,           /**< Generic wakeup reason */
    E_LCM_WAKEUP_RTC_APP,           /**< Application timer expired wakeup reason */
    E_LCM_WAKEUP_RTC_SWM,           /**< SWM timer expired reason */
    E_LCM_WAKEUP_UNDEFINED,         /**< Undefined wakeup reason; set while LifecycleState is E_LCM_ST_BEFORE_SLEEP */
    E_LCM_WAKEUP_LAST               /**< Undefined behavior */
} lcm_WakeupReason_t;

}
};


#endif // LIFECYCLEMONITORTYPES_H
