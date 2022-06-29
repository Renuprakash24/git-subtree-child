#ifndef IDIAGNOSISSERVICES_TYPES_H
#define IDIAGNOSISSERVICES_TYPES_H
/**
 * \file
 *         IDiagManagerClientTypes.h
 * \brief
 *         Diagnosis Macchina API
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

/******************************************** TYPEDEFS ***********************************************************/

namespace Stla
{
namespace Diagnosis
{
	/**
  * \brief eDiagdtccode_t Define DTC Table
  *
  */
  typedef enum DiagDtcCode_e
  {
    /*Diagnosis domain DTCs to be defined*/
    /*Positioning domain DTCs to be defined*/
    /*Operating System domain DTCs to be defined*/
    /*AIRBAG dtcs to be defined*/
    /*ECALL-ACALL dtcs to be defined*/
    /*ACCEL dtcs to be defined*/
    /*LOUDSPEAKER dtcs to be defined*/
    /*AMPLI dtcs to be defined*/
    /*LED dtcs to be defined*/
    /*Security DTCs to be defined*/
    /*Lifecycle & Persistence domain DTCs to be defined*/
    /*Connectivity DTCs to be defined*/
    /*Broadcast DTCs to be defined*/
    /*Operating System DTCs to be defined*/
    /*Networking domain DTCs to be defined*/
    /*OTA DTCs to be defined*/
    /*Networking domain DTCs to be defined */
    /*External Antenna DTC to be defined*/
   
  } eDiagdtccode_t;

  /**
  * \brief eDiagDtcStat_t Define DTC status
  *
  */

    typedef enum DiagDtcStat_e{
        /*Value to be defined*/
    } eDiagDtcStat_t;

    /**
 *  \brief  sDiagClientDTCConfirmation_t
 *  \details
 */
    typedef struct DiagClientDTCConfirmation{
       /*Value to be defined*/
    }sDiagClientDTCConfirmation_t;

} // namespace Diagnosis
} // namespace Stla

using namespace Stla::Diagnosis;

#endif //   IDIAGNOSISSERVICES_TYPES_H
