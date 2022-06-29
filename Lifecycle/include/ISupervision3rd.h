/**
 * \file
 *          ISupervision3rd.h
 *
 * \brief
 *          Interface for the base service provided by SupervisionBundle , which offers retrievial and notification of CPU & RAM usage for MCH3 instance(Device Diagnostic)
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

#ifndef ISUPERVISION3RD_H
#define ISUPERVISION3RD_H

#include "Poco/OSP/Service.h"
#include "Supervison3rdTypes.h"

namespace Stla{
namespace AppFwk{

/**
 * @brief The ISupervision3rd class: interface to be implemented in supervision-app
 */
#ifdef DOXYGEN_WORKING
class ISupervision3rd: public Poco::OSP::Service
#else
class __attribute__((visibility("default"))) ISupervision3rd: public Poco::OSP::Service
#endif
{
public:

    typedef Poco::AutoPtr<ISupervision3rd> Ptr;

    /**
     * @brief ISupervision3rd constructor
     */
    ISupervision3rd(){}

    /**
     * @brief ISupervision3rd destructor
     */
    virtual ~ISupervision3rd(){}

     /**
     * @brief Returns the type information for the object's class
     */
    const std::type_info& type() const {
        return typeid(ISupervision3rd);
    }

    /**
     * @brief Returns true if the class is a subclass of the class given by otherType.
     */
    bool isA(const std::type_info& otherType) const {
        std::string name(type().name());
        return name == otherType.name();
    }

     /**
     * @brief get CPU status for macchina third instance
     * This getter can be used separately , in addition to the periodical notify
     * @param[out] cpuInfo The variable to save the cpu information
     */
    virtual void getMch3CpuInfo(float& cpuInfo) = 0;

    /**
     * @brief get memory information (PSS value) for macchina third instance
     * This getter can be used separately , in addition to the periodical notify
     * @param[out] memInfo The variable to save the PSS value
     */
    virtual void getMch3MemInfo(unsigned int& memInfo) = 0;

    /**
     * @brief event used to notify clients with CPU & MemInfo status every second
     */
    Poco::BasicEvent<const mchProcessInfo> MchProcessInfoUpdate;
};

} /* namespace AppFwk */
} /* namespace Stla */

#endif // ISUPERVISION3RD_H
