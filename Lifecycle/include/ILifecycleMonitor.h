/**
 * \file
 *          ILifecycleMonitor.h
 *
 * \brief
 *          The interface for the LifecycleMonitor
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

#ifndef ILIFECYCLEMONITOR_H
#define ILIFECYCLEMONITOR_H

#include "ILifecycleMonitorTypes.h"
#include "Poco/BasicEvent.h"
#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"

namespace Stla
{
namespace AppFwk
{
/**
 * @brief The ILifecycleMonitor class: interface to be implemented by AppFwk that will handle and notify the app lifecycle states
 * Each application will have its own LCM object of this interface, and will listens on the events that notify its state.
 */
#ifdef DOXYGEN_WORKING
class ILifecycleMonitor: public Poco::RefCountedObject
#else
class __attribute__((visibility("default"))) ILifecycleMonitor: public Poco::RefCountedObject
#endif
{
public:
    typedef Poco::AutoPtr<ILifecycleMonitor> Ptr;

    /**
     * @brief ackAppState: Application can acknowledge here that it finished the operation requested (the requested state change)
     * @param[in] state: can be one of Initializing, Idle(due to Suspend/Shutdown), Normal
     *
     * @msc
     *
     *  a[label=""], b[label=""], c[label=""];
     *
     *  a box a [label = "InitBundleServiceImpl"],
     *  b box b [label = "CLifecycleMonitor"],
     *  c box c [label = "GenericApp"];
     *
     *  c => b [label = "ackAppState(AppState)"];
     *  |||;
     *  b => b [label = "ackAppStateEvent.notifyAsync(this, m_appState);"],
     *  b => a [label = "onAppStatusChange(this, m_appState)"];
     *
     * @endmsc
     */
    virtual void ackAppState(const SLCM_AppState_t& state) =0;


    //**********************************
    // Notifications application state:
    //**********************************

    /**
     * @brief AppStateEvent: Event used to notify applications to change their state. Apps should perform necessary actions to enter the notified state
     */
    Poco::BasicEvent<const SLCM_AppState_t> AppStateEvent;

    /**
     * @brief OptServiceAvailable: Event used to notify applications that one of their optional services became available
     */
    Poco::BasicEvent<const std::string> OptServiceAvailable;

    /**
     * @brief OptServiceUnavailable: Event used to notify applications that one of their optional services became unavailable
     */
    Poco::BasicEvent<const std::string> OptServiceUnavailable;

    /**
     * @brief Check if a mandatory or optional service is available
     * @param[in] symbolicName: Service symbolic name
     * @param[out] available: TRUE if the service associated to the input is available
     * return E_LCM_RET_SUCCESS if successful or E_LCM_RET_INVALID_ARG if there is no service associated to the input
     **/
    virtual ELCM_ErrorType getServiceAvailability(const std::string& symbolicName, bool& available) = 0;

    /**
     * @brief Lifecycle State event - Early init service notifies lifecycle state change to the application
     */
    Poco::BasicEvent<lcm_LifecycleState_t>              LifecycleStateEvent;

    /**
     * @brief CAN Network State event - Early init service notifies CAN Network state change to the application
     */
    Poco::BasicEvent<lcm_CANNetworkState_t>             CanNetworkStateEvent;

    /**
     * @brief Park Mode State event - Early init service notifies Park Mode State change to the application
     */
    Poco::BasicEvent<lcm_ParkModeState_t>               ParkModeStateEvent;

    /**
     * @brief RTC Alarm Expired event - Early init service notifies that one RTC Alarm has expired to the application
     */
    Poco::BasicEvent<lcm_RtcAlarmHandle_t>              RtcAlarmExpiredEvent;

    /**
     * @brief RTC Alarm Deleted event - Early init service notifies that one RTC Alarm has been deleted to the application
     */
    Poco::BasicEvent<lcm_RtcAlarmHandle_t>              RtcAlarmDeletedEvent;

    /**
     * @brief RTC Alarm Created event - Early init service notifies that one RTC Alarm has been created to the application
     * @brief Register to this event before creating RTC alarm
     * @brief Unregister to this event after obtaining the alarm_handle via this notification
     */
    Poco::BasicEvent<lcm_RtcAlarmCreated_t>             RtcAlarmCreatedEvent;

    /**
     * @brief Backup Battery Status event - Early init service notifies Backup Battery Status change to the application
     */
    Poco::BasicEvent<lcm_BackupBatteryStatus_t>         BackupBatteryStatusEvent;

    /**
     * @brief Backup battery voltatge changed - cyclic notification (typically once a second) -voltage in mV
     */
    Poco::BasicEvent<unsigned int>                     BackupBatteryVoltageEvent;

    /**
     * @brief Backup battery temperature changed - cyclic notification (typically once a second) temperature Celsius degrees
     */
    Poco::BasicEvent<int>                              BackupBatteryTemperatureEvent;

    /**
     * @brief Backup battery state of health changed - on change notification
     */
    Poco::BasicEvent<lcm_BuBSOH_t>                      BackupBatterySOHEvent;

    /**
     * @brief Backup battery charge level changed - on change notification
     */
    Poco::BasicEvent<lcm_BuBSOC_t>                     BackupBatteryChargeLevelEvent;

    /**
     * @brief Wakeup Reason event- Early init service notifies the wakeup reason to the application
     */
    Poco::BasicEvent<lcm_WakeupReason_t>                WakeupReasonEvent;

    /**
     * @brief Keep awake status event - the current status of the keep awake.
     * @brief It can be used as an asynchronous response for lcm_keepAwakeReq
     * @brief (when the synchronous response returned through keepAwakeStatus is E_LCM_KA_STATUS_PENDING).
     * @brief It can be used as state change event for keep awake when, for example, the maximum time with keep awake is reached.
     * @brief Register for this event before calling lcm_keepAwakeReq.
     */
    Poco::BasicEvent<lcm_KeepAwakeStatus_t>            KeepAwakeStatusEvent;

    /**
    * @brief Function to send the system keep awake request.
    * @brief This function should be used to delay shutdown in order to make a process without CAN
    * @brief If keepAwakeStatus is set E_LCM_KA_STATUS_PENDING, the caller has to wait for KeepAwakeStatusEvent.
    * @param[in] keepAwake: keep awake request: lcm_KeepAwakeRequest_t
    * @param[out] keepAwakeStatus: synchronous response to keep awake request: lcm_KeepAwakeStatus_t.
    *        memory for keepAwakeStatus parameter must be allocated by the caller
    * @return  E_LCM_RET_SUCCESS if successful
    * \n       E_LCM_RET_FAILURE if generic failure like memory allocation error
    * \n       E_LCM_RET_INVALID_ARG if appName is NULL or exceeds maximum length, if keepAwake has invalid value
    * \n       E_LCM_RET_NOT_REGISTERED if application is not registered with tcu state manager
    */
   virtual ELCM_ErrorType lcm_keepAwakeReq(lcm_KeepAwakeRequest_t keepAwake, lcm_KeepAwakeStatus_t *keepAwakeStatus) = 0;

   /**
    * @brief Function to wakeup the CAN Network.
    * @param[in] causeX: contains causeX reason that will be sent to VSM to wakeup the CAN. Use E_LCM_CAUSE_X to activate and E_LCM_CAUSE_NONE to deactivate the request
    * @return  E_LCM_RET_SUCCESS if successful
    * \n       E_LCM_RET_FAILURE if generic failure like memory allocation error
    * \n       E_LCM_RET_INVALID_ARG if appName is NULL or exceeds maximum length, if causeX has invalid value
    * \n       E_LCM_RET_NOT_REGISTERED if application is not registered with tcu state manager
    * \n       E_LCM_RET_NO_PERM if system state is not NORMAL or BEFORE_SLEEP and cause is not NONE, if CAN network is ON, if max number of retries reached   
    */
   virtual ELCM_ErrorType lcm_requestCANWakeup(lcm_CauseX_t causeX) = 0;

   /**
    * @brief Function to get the current vehicle CAN network state
    * @param[out] CANState: CAN network current status
    * @return  E_LCM_RET_SUCCESS if successful
    * \n       E_LCM_RET_FAILURE if CANState is NULL or generic failure
    */
   virtual ELCM_ErrorType lcm_getCANState(lcm_CANNetworkState_t *CANState) = 0;

   /**
    * @brief Function to get the current Park Mode state
    * @param[out] ParkModeState: Park Mode current status
    * @return  E_LCM_RET_SUCCESS if successful
    * \n       E_LCM_RET_FAILURE if ParkModeState is NULL or generic failure
    */
   virtual ELCM_ErrorType lcm_getParkModeState(lcm_ParkModeState_t *ParkModeState) = 0;

   /**
    * @brief Function to schedule a RTC alarm
    * @brief This Function should be used when an application wants to schedule an action in the future - an application can create maximum 5 alarms
    * @brief Use this alarm mechanism to schedule alarms when the TCU is entering suspend/shutdown(DNO/FULL SLEEP) - in ShutdownEvent callback
    * @param[in] cycles: the counter (different from 0) indicating how many times this alarm will expire - maximum number of cycles is 255
    * @param[in] period: the time in minutes until alarm expires - minimum time is 5 minutes and maximum time is 65535 minutes
    * @param[out] index: local index that will be used to map with alarm_handle obtained via RtcAlarmCreatedEvent.
    * @return  E_LCM_RET_SUCCESS if successful
    * \n       E_LCM_RET_FAILURE if index is NULL or generic failure like memory allocation error
    * \n       E_LCM_RET_INVALID_ARG if appName is NULL or exceeds maximum length, if alarm cycles exceeds maximum value, if alarm period is not in range
    * \n       E_LCM_RET_NOT_REGISTERED if application is not registered with tcu state manager
    * \n       E_LCM_RET_NO_PERM if system state is not BEFORE_SLEEP or maximum number of alarms has been reached
    */
   virtual ELCM_ErrorType lcm_createRTCAlarm(unsigned int cycles, unsigned int period, unsigned int *index) = 0;

   /**
    * @brief Function to delete a RTC alarm
    * @brief This Function should be used when the application wants to cancel a future alarm.
    * @brief When alarm cycles reaches 0 the alarm is automatically deleted after ack is sent or timeout occurred and the application will receive a notification(RtcAlarmDeletedEvent)
    * @brief Deleting an expired alarm is not possible, the application should ack the alarm before requesting the deletion
    * @param[in] alarmHandle: global handle used by applications in order to track alarms.
    * @return  E_LCM_RET_SUCCESS if successful
    * \n       E_LCM_RET_FAILURE if generic failure like memory allocation error
    * \n       E_LCM_RET_INVALID_ARG if appName is NULL or exceeds maximum length, if alarmHandle value is invalid
    * \n       E_LCM_RET_NOT_REGISTERED if application is not registered with tcu state manager
    * \n       E_LCM_RET_NO_PERM if the alarm is expired, the application should ack the alarm before requesting the deletion
    */
   virtual ELCM_ErrorType lcm_deleteRTCAlarm(lcm_RtcAlarmHandle_t alarmHandle) = 0;

   /**
    * @brief Function to acknowledge a RTC alarm to shutdown the system before RTC timer timeout
    * @brief This Function should be used by the application to signal that actions associated with this alarm are done.
    * @brief If this function is not called the system will shutdown with a timeout.
    * @param[in] alarmHandle: global handle used by applications in order to track alarms.
    * @return  E_LCM_RET_SUCCESS if successful
    * \n       E_LCM_RET_FAILURE if generic failure like memory allocation error
    * \n       E_LCM_RET_INVALID_ARG if appName is NULL or exceeds maximum length, if alarmHandle value is invalid
    * \n       E_LCM_RET_NOT_REGISTERED if application is not registered with tcu state manager
    * \n       E_LCM_RET_NO_PERM if the alarm is not expired
    */
   virtual ELCM_ErrorType lcm_acknowledgeRTCAlarm(lcm_RtcAlarmHandle_t alarmHandle) = 0;

   /**
    * @brief Function to get the backup battery status
    * @param[out] batteryStatus: backup battery current status
    * @return  E_LCM_RET_SUCCESS if successful
    * \n       E_LCM_RET_FAILURE if batteryStatus is NULL or generic failure
    */
   virtual ELCM_ErrorType lcm_getBackupBatteryStatus(lcm_BackupBatteryStatus_t *batteryStatus) = 0;

    /**
     * @brief Function to get the backup battery voltage
     * @param[out] bubVoltage: current backup battery voltage (mV)
     * @return  E_LCM_RET_SUCCESS if successful
     * \n       E_LCM_RET_FAILURE if bubVoltage is NULL or generic failure
     */
    virtual ELCM_ErrorType lcm_getBackupBatteryVoltage(unsigned int *bubVoltage) = 0;

    /**
     * @brief Function to get the backup battery temperature
     * @param[out] bubTemperature: current backup battery temperature (Celsius degrees)
     * @return  E_LCM_RET_SUCCESS if successful
     * \n       E_LCM_RET_FAILURE if bubTemperature is NULL or generic failure
     */
    virtual ELCM_ErrorType lcm_getBackupBatteryTemperature(int *bubTemperature) = 0;

    /**
     * @brief Function to get the backup battery state of health
     * @param[out] bubSoh: current backup battery state of health
     * @return  E_LCM_RET_SUCCESS if successful
     * \n       E_LCM_RET_FAILURE if bubSoh is NULL or generic failure
     */
    virtual ELCM_ErrorType lcm_getBackupBatterySOH(lcm_BuBSOH_t *bubSoh) = 0;

    /**
     * @brief Function to get the backup battery charge level
     * @param[out] bubChargeLevel: current backup battery charge level
     * @return  E_LCM_RET_SUCCESS if successful
     * \n       E_LCM_RET_FAILURE if bubChargeLevel is NULL or generic failure
     */
    virtual ELCM_ErrorType lcm_getBackupBatteryChargeLevel(lcm_BuBSOC_t *bubChargeLevel) = 0;

   /**
    * @brief Function to get the wakeup reason
    * @param[out] wakeupReason: wakeup reason current status
    * @return  E_LCM_RET_SUCCESS if successful
    * \n       E_LCM_RET_FAILURE if wakeupReason is NULL or generic failure
    * \n       E_LCM_RET_BUSY if not all wake sources are validated
    */
   virtual ELCM_ErrorType lcm_getWakeupReason(lcm_WakeupReason_t *wakeupReason) = 0;

    /**
     * @brief Function to get the current lifecycle state
     * @param[out] state: current lifecycle state
     * @return  E_LCM_RET_SUCCESS if successful
     * \n       E_LCM_RET_FAILURE if state is NULL or generic failure
     */
    virtual ELCM_ErrorType lcm_getLifecycleState(lcm_LifecycleState_t *state) = 0;

    /**
     * @brief Function to get the current CDNO status
     * @param[out] bCDNOActive: TRUE if CDNO is active, FALSE otherwise
     * @return  E_LCM_RET_SUCCESS if successful
     * \n       E_LCM_RET_INVALID_ARG if bCDNOActive is NULL
     */
    virtual ELCM_ErrorType lcm_isCDNOActive(bool *bCDNOActive) = 0;

    /**
     * @brief ~ILifecycleMonitor: destructor
     */
    virtual ~ILifecycleMonitor(){}
};
}
}

#endif // ILIFECYCLEMONITOR_H
