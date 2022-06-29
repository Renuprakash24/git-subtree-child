/**
 * \file
 *          IPositioningServiceTypes.h
 * \brief
 *          Positioningservice data types
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

#ifndef IPOSITIONINGSERVICE_TYPES_H_
#define IPOSITIONINGSERVICE_TYPES_H_

#include <vector>
#include "genivi/gnss.h"

namespace Stla
{
    namespace Positioning
    {
        /**
         *  Data type for satellite details list
         */
        using TGNSSSatelliteDetails = std::vector<TGNSSSatelliteDetail>;

        /**
         * @brief Description of the fix type of the enhanced position.
         */
		  //@ serialize
        typedef enum {
            ENH_POSITION_FIX_TYPE_NONE,         /**< No position is available */
            ENH_POSITION_FIX_TYPE_GNSS_ONLY,    /**< Only GNSS position is available */
            ENH_POSITION_FIX_TYPE_DR_ONLY,      /**< Only DR position is available (DR position is calculated exclusively based on sensor data) */
            ENH_POSITION_FIX_TYPE_GNSS_DR       /**< GNSS and DR position combination */
        } EEnhancedPositionFixType;

        /**
         * @brief Description of the status of the dead reckoning position.
         */
		 //@ serialize
        typedef enum {
            DR_FAULT,                           /**< DR position can not be calculated because of sensor fault / no GNSS position available */
            DR_CALIBRATING,                     /**< DR algorithm is in calibration phase */
            DR_CALIBRATED                       /**< DR algorithm is calibrated */
        } EDeadReckoningStatus;

        /**
         * Dead reckoning position extended information.
         * This data structure provides information about dead reckoning position
         * status and quality.
         */
        typedef struct {
            EDeadReckoningStatus status;        /**< Status of the DR position */
            uint8_t quality;                    /**< Quality of the DR position: (0%) Not calibrated, (> 0%) Calibrating, (> 50%) Good calibration [%]. */
        } TDeadReckoningInfo;

        /**
         * @brief TEnhancedPosition::validityBits provides information about the currently valid signals
         * of the enhanced position.
         * It is a or'ed bitmask of the EEnhancedPositionValidityBits values.
         */
		 //@ serialize
        typedef enum {
            ENH_POSITION_HPOS_VALID         = 0x00000001,   /**< Validity bit for field TEnhancedPosition::latitude and TEnhancedPosition::longitude. */
            ENH_POSITION_SHPOS_VALID        = 0x00000002,   /**< Validity bit for field TEnhancedPosition::sigmaHPosition. */
            ENH_POSITION_HSPEED_VALID       = 0x00000010,   /**< Validity bit for field TEnhancedPosition::hSpeed. */
            ENH_POSITION_HEADING_VALID      = 0x00000040,   /**< Validity bit for field TEnhancedPosition::heading. */
            ENH_POSITION_DR_INFO_VALID      = 0x40000000,   /**< Validity bit for field TEnhancedPosition::drInfo. */
            ENH_POSITION_FIX_TYPE_VALID     = 0x80000000    /**< Validity bit for field TEnhancedPosition::fixType. */
        } EEnhancedPositionValidityBits;

        /**
         * Enhanced position data.
         * This data structure provides enhanced position information which can be
         * retrieved, depending on availability, from GNSS / Dead Reckoning.
         */
        typedef struct {
            uint64_t timestamp;                 /**< Timestmap for when the position was calculated [ms]. */
            double latitude;                    /**< Latitude in WGS84 in [degree]. */
            double longitude;                   /**< Longitude in WGS84 in [degree]. */
            float hSpeed;                       /**< Horizontal speed [m/s], in direction as given by @ref heading. */
            float heading;                      /**< Enhanced course angle [degree] (0 => north, 90 => east, 180 => south, 270 => west, no negative values). */
            float sigmaHPosition;               /**< Standard error estimate of the horizontal position in [m]. */
            TDeadReckoningInfo drInfo;          /**< Dead Reckoning information. */
            EEnhancedPositionFixType fixType;   /**< Types of positions used for this enhanced position. */
            uint32_t validityBits;              /**< Bit mask indicating the validity of each corresponding value.
                                                     [bitwise or'ed @ref EEnhancedPositionValidityBits values].
                                                     Must be checked before usage. */
        } TEnhancedPosition;

        /**
         * @brief Description of VCS engine status.
         */
		 //@ serialize
        typedef enum {
            E_ENGINE_STATUS_NOT_RUNNING = 0,
            E_ENGINE_STATUS_STARTING,
            E_ENGINE_STATUS_RUNNING,
            E_ENGINE_STATUS_STOPPED,
            E_ENGINE_STATUS_UNKNOWN
        } EEngineStatus;

        /**
         * Description of VCS SEV status.
         */
		 //@ serialize
        typedef enum {
            E_CAN_POWER_MODE_STOP = 0,
            E_CAN_POWER_MODE_CONTACT,
            E_CAN_POWER_MODE_DEM,
            E_CAN_POWER_MODE_NOT_USED,
            E_CAN_POWER_MODE_UNKNOWN
        } ESEVStatus;
    }
}

#endif