/**
 * \file
 *          IEarlyInitService.h
 *
 * \brief
 *          The interface for the InitBundle service
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

#ifndef InitBundleService_INCLUDED
#define InitBundleService_INCLUDED

#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Service.h"
#include "Poco/AutoPtr.h"
#include "ILifecycleMonitor.h"

namespace Stla
{
namespace AppFwk
{

/**
 * @brief The IEarlyInitService interface, for EarlyInitBundle service, providing method to determine if bundle is on ThirdParty macchina instance
 * Also some API for LCM handling is available
 */
#ifdef DOXYGEN_WORKING
class  IEarlyInitService: public Poco::OSP::Service
#else
class __attribute__((visibility("default"))) IEarlyInitService: public Poco::OSP::Service
#endif
{
public:
        typedef Poco::AutoPtr<IEarlyInitService> Ptr;

        /**
         * @brief getInstanceID member function
         * @param[out] isThirdPartyInstance: boolean that indicates if the current instance is third party
         * @return the id of the instance the app is running on
         */
        virtual std::string getInstanceID(bool &isThirdPartyInstance) = 0;

        // LifecycleMonitor API for app usage
        /**
         * @brief getLCM_Obj: application request its own LCM object that handles the application's lifecycle state depending on the state of the dependent services
         *              and lifecycle state notified from TCU
         * @param[in] pAppBndlContext: bundle context of the application
         * @param[in] mandatoryServices: services mandatory for the bundle
         * @param[in] optionalServices: a map of services considered optional (their presence is not critical) (key = service name, value = service state)
         *
         * @return LCM object
         *
         *
         * @msc
         *
         *  width = "1000";
         *
         *  a[label=""], b[label=""], c[label=""], d[label=""];
         *
         *  |||;
         *
         *  a box a [label = "BundleManifest"],
         *  b box b [label = "CLifecycleMonitor"],
         *  c box c [label = "InitBundleServiceImpl"],
         *  d box d [label = "GenericApp"];
         *
         *  |||;
         *  d => c [label = "getLCM_obj(pContext, mandatoryServices, optionalServices)"];
         *  |||;
         *  c => a [label = "requiredBundles()"];
         *  |||;
         *  c => b [label = "CLifecycleMonitor(mandatoryServices, optionalServices, pContext)"];
         *  |||;
         *  c >> d [label = "CLifecycleMonitor*"];
         *
         * @endmsc
         *
         */
        virtual ILifecycleMonitor::Ptr getLCM_Obj(Poco::OSP::BundleContext::Ptr pAppBndlContext, const std::list<std::string>& mandatoryServices, const std::list<std::string>& optionalServices) = 0;


    /**
     * @brief ~IEarlyInitService destructor
     */
    virtual ~IEarlyInitService() {}

};
}
}


#endif // InitBundleService_INCLUDED
