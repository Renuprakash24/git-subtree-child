#ifndef _IDIAG_MANAGER_CLIENT_H_
#define _IDIAG_MANAGER_CLIENT_H_
/**
 * \file
 *         IDiagManagerClient.h
 * \brief
 *         Diagnosis Macchina API
 *
 *  \par Copyright Notice:
 * \verbatim
 * Copyright (c) 2021 Stellantis N.V.
 * All Rights Reserved.
 * The reproduction, transmission or use of this document or its contents is
 * not permitted without express written authority.
 * Offenders will be liable for damages. All rights, including rights created
 * by patent grant or registration of a utility model or design, are reserved.
 * \endverbatim
 */
 
/********************************** INCLUDES ***********************************************************/
#include "Poco/OSP/Service.h"
#include "Poco/AutoPtr.h"
#include "Poco/NotificationCenter.h"
#include "Poco/Notification.h"
#include "Poco/Observer.h"
#include "IDiagManagerClientTypes.h"
#include "Poco/RefCountedObject.h"

using Poco::Notification;
using Poco::NotificationCenter;
using Poco::Observer;
/************************************** Variables ******************************************/
/**
 * \brief Diagnosis Service name to be looked up by OSP
 */
#define TCU_DIAG_CLIENT_SERVICE "stla.diagnosis.client.service"
/************************************** Enumerations ****************************************/

/************************************** Structures ******************************************/

/************************************** Typedef *********************************************/

/************************************** Variables *******************************************/

/************************************ Declarations ******************************************/

namespace Stla
{
namespace Diagnosis
{
/**
  * \brief Diagnosis Service interface
  */
#ifdef DOXYGEN_WORKING
class Diagnosis_IF : public Poco::OSP::Service
#else
class __attribute__((visibility("default"))) Diagnosis_IF : public Poco::OSP::Service
#endif
{
public:
    /**
	 * \brief Class smart pointer definition
	 *
	 * Because Diagnosis service is an OSP service, memory management is
	 * done by the platform itself. Whenever a client looks up for a service,
	 * the platform returns a pointer to the actual service which must be
	 * stored in a smart pointer.
	 *
	 * Usage:
	 * \code{.cpp}
	 * Poco::OSP::ServiceRef::Ptr pServiceRef = pBundleContext->registry().findByName(TCU_DIAG_CLIENT_SERVICE);
	 * if(pServiceRef) // Service was found
	 * {
	 *     Stla::Diagnosis::Diagnosis_IF::Ptr _pDiagMgrClientIntf = pServiceRef->castedInstance<Stla::Diagnosis::Diagnosis_IF>();
	 * }
	 * \endcode
	 */
    typedef Poco::AutoPtr<Diagnosis_IF> Ptr;
    /**
	 * \brief Diagnosis Service constructor
	 */
    Diagnosis_IF()
    {
        /* Do nothing */
    }
    /**
	 * \brief Diagnosis Service destructor
	 */
    virtual ~Diagnosis_IF()
    {
        /* Do nothing */
    }

    /**
     *  \brief  diagClientQueryDtcStatus
     *  \param  dtcCode: DTC code (3 bytes) to be queried
     *  \return status: DTC status
	 * 				3 if CONFIRMED_PRESENT
	 * 				4 if CONFIRMED_ABSENT
     *  \details API provided to domains to query a specific DTC Status
     */
    virtual eDiagDtcStat_t diagClientQueryDtcStatus(unsigned int dtcCode) = 0;
    /**
     *  \brief  diagClientQueryAllConfirmedPresentDtcs
     *  \return std::vector contains all confirmed dtcs listed in the eDiagdtccode_t enumeration
     *  \details API provided to domains to query all confirmed Present DTCs
     */
    virtual std::vector<unsigned int> diagClientQueryAllConfirmedPresentDtcs(void) = 0;
};

/**
 * \brief Poco Notification which is dispatched when DTC confirmation is received 
 *
 * This notification encapsulated data information.
 * The data is sDiagClientDTCConfirmation_t structure.
 * \details
 * create a notification center responsible to delivers the notification to interested observers
 * create an observer object that can hold the data and register it to the notification center
 * Usage:
 * \code{.cpp}
 * void ClientClass::startup()
 * {
 * 		Poco::NotificationCenter& nc = Poco::NotificationCenter::defaultCenter();
 * 		Poco::Observer<ClientClass, Stla::Diagnosis::DiagClientDtcConfirmationNotify> obs (*this, &ClientClass::handleNotification);
 * 		nc.addObserver(obs);
 * 		Poco::OSP::ServiceRef::Ptr pServiceRef = pBundleContext->registry().findByName(TCU_DIAG_CLIENT_SERVICE);
 * 		if(pServiceRef) // Service was found
 * 		{
 *     		Stla::Diagnosis::Diagnosis_IF::Ptr _pDiagMgrClientIntf = pServiceRef->castedInstance<Stla::Diagnosis::Diagnosis_IF>();
 * 		}
 * }
 * void ClientClass::handleNotification(DiagClientDtcConfirmationNotify*  data)
 * {
 *      // Do stuff with data
 * }
 *  void ClientClass::shutdown()
 * {
 *     nc.removeObserver(obs);
 * }
 * \endcode
 */
class DiagClientDtcConfirmationNotify : public Notification
{
public:
    DiagClientDtcConfirmationNotify(sDiagClientDTCConfirmation_t &data) : _msg(data){

                                                                          };

    sDiagClientDTCConfirmation_t &data()
    {
        return _msg;
    };

    sDiagClientDTCConfirmation_t _msg;
};

} // namespace Diagnosis
} // namespace Stla

#endif //    _IDIAG_MANAGER_CLIENT_H_
