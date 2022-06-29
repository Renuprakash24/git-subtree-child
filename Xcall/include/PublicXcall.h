/**
 * \file     PublicXcall.h
 * \brief    This is the PublicXcall interface. Needs to be aligned with the PublicXcall.h in SW Package XCallApp
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

#ifndef PUBLICXCALL_H
#define PUBLICXCALL_H

#include <chrono>
#include <string>

#define ECALL_SRV_BUNDLE_NAME "stla.tcu.xcall.app"
#define ECALL_SRV_ROUTER_REMOTE_SERVICE_SERVICE_NAME "Stla.TCU.Xcall.PublicEcall"
#define ECALL_SRV_ROUTER_REMOTE_SERVICE_ADDRESS "127.0.0.1"
#define ECALL_SRV_ROUTER_REMOTE_SERVICE_PORT "834"
#define ECALL_SRV_ROUTER_REMOTE_SERVICE_OBJECT_NAME "PublicEcallRemoteObject"


namespace Stla {
namespace Xcall {

/**
 * \brief The EcallState enum Lists possible simplified Emergency call states.
 * \note Ecall stands for Emergency call.
 */
 //@ serialize
enum EcallState {
    UnknownState = -1,  /**< Invalid state. */
    Idle,               /**< Currently no Ecall is running. */
    OnGoing,            /**< Contains sequence of establishing a call to emergeny hotline and talking to the operator. */
    WaitingForCallback, /**< The operator has hung up the call and he is given time to call the system back to obtain more information. */
};

/**
 * \brief The EcallReason enum Lists possible reasons (a.k.a. triggers) that lead to the launch of an Emergency call.
 */
//@ serialize
enum EcallReason {
    UnknownReason = -1,     /**< Invalid reason. */
    NotTriggered,           /**< Currently no Ecall is running. */
    ManualTriggered,        /**< Ecall is triggered by the User. */
    AutomaticTriggered,     /**< Ecall is triggered by the System. */
};

/**
 * \brief The ButtonState_Type enum Lists possible state of button pressed for Ecall and Acall.
 */
 //@serialize
typedef enum 
{
    NOT_PRESSED = 0, 	/**< Button not Pressed */
    SHORT_PRESSED,		/**< Button short Pressed */
    LONG_PRESSED,		/**< Button long Pressed */
    LONG_RELEASED,		/**< Long Button released */
    UNAVAILABLE = -1	/**< Button press not available */
} ButtonState_Type;

/**
 * \brief The EcallDescription class Keeps a simplified description of an Emergency Call.
 */
//@serialize
struct EcallDescription {
    std::time_t startedAt;          /**< Timestamp of the start of the Ecall in Unix Time: seconds since start of the epoch 1.1.1970. */
    std::uint32_t reason;             /**< How the Ecall is triggered: manual/automatic/not/unknown. */
    std::string VIN;                /**< Vehicle identification number of the car. */

    EcallDescription(): startedAt ( 0 ), reason ( -1 ), VIN ( "", 17 )
    {
    }
};

/**
 * \brief The PublicEcall class Provides an interface to obtain.
 * information pertaining to Ecall.
 */
//@ remote
class PublicEcall {
public:
    /**
     * \brief getEcallState Gets the current state of the Ecall feature.
     * \return EcallState Idle if there is currently no Ecall.
     */
    virtual EcallState getEcallState() = 0;

    /**
     * \brief getEcallReason Gets the reason (aka trigger) of the current Ecall.
     * \return EcallReason NotTriggered if there is currently no Ecall.
     */
    virtual EcallReason getEcallReason() = 0;

    /**
     * \brief getLastEcallDescription Gets a simplified description of the last recorded Ecall.
     * \return EcallDescription a simplified description of an Emergency Call.
     */
    virtual EcallDescription getLastEcallDescription() = 0;

    /**
    * \brief getEcallButtonState Gets a state of ECall button
    * \return ButtonState_Type NOT_PRESSED if there is no button pressed.
    */
    virtual ButtonState_Type getEcallButtonState() = 0;

    /**
    * \brief getAcallButtonState Gets a state of ACall button
    * \return ButtonState_Type NOT_PRESSED if there is no button pressed.
    */
    virtual ButtonState_Type getAcallButtonState() = 0;

    virtual ~PublicEcall() { }
};
//@ remote
    class EcallInfoProvider : public PublicEcall {
public:
    EcallState getEcallState();
    EcallReason getEcallReason();
    EcallDescription getLastEcallDescription();
    ButtonState_Type getEcallButtonState();
    ButtonState_Type getAcallButtonState();

};

} // namespace Xcall
} // namespace Stla

#endif // PUBLICXCALL_H
