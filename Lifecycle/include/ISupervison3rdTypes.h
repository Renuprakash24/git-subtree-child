/**
 * \file
 *          Supervision3rdTypes.h
 *
 * \brief
 *          Types defined for the ISupervision3rd
 
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

#ifndef SUPERVISION3RDTYPES_H
#define SUPERVISION3RDTYPES_H

namespace Stla{
namespace AppFwk{

/**
 * @brief Name of the suprervision service for macchina 3d instance info (CPU & RAM usage)
 */
static std::string SUPERVISION_SERVICE_BASE ("stla.appfwk.supervision.service.base");


/**
 * @brief Structure containing macchina 3rd instance info
 * The event that notfies macchina 3rd instance info use this data type
 */
struct mchProcessInfo{
    /**
    * @brief Cpu load , in percent
    */
    float CPU_LOAD;
    /**
    * @brief PSS memory used , in KB
    */
    unsigned int PSS_MEM;
};
}
}

#endif // SUPERVISION3RDTYPES_H