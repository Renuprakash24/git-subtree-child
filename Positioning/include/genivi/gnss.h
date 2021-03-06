/**
 * \file
 *          gnss.h
 * \brief
 *          Compliance Level: Abstract Component
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
 *
 * \license
 * This Source Code Form is subject to the terms of the
 * Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
 * this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @licence end@
 **************************************************************************/

#ifndef INCLUDE_GENIVI_GNSS_EXT
#define INCLUDE_GENIVI_GNSS_EXT

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Description of the fix status of the GNSS reveiver.
 */
 //@ serialize
typedef enum {
    GNSS_FIX_STATUS_NO,         /**< GNSS has no fix, i.e. position, velocity, time cannot be determined */
    GNSS_FIX_STATUS_TIME,       /**< GNSS can only determine the time, but not position and velocity */
    GNSS_FIX_STATUS_2D,         /**< GNSS has a 2D fix, i.e. the horizontal position can be determined but not the altitude.
                                     This implies that also velocity and time are available. */
    GNSS_FIX_STATUS_3D          /**< GNSS has a 3D fix, i.e. position can be determined including the altitude.
                                     This implies that also velocity and time are available. */
} EGNSSFixStatus;

/**
 * @brief TGNSSPosition::fixTypeBits provides GNSS Fix Type indication.
 * I.e. it identifies the sources actually used for the GNSS calculation
 * It is a or'ed bitmask of the EGNSSFixType values.
 * The bit values have been grouped logically with gaps where future extensions can be foreseen
 * Within one group, not all combinations make necessarily sense
 * Between different groups, all combinations should make sense
 */
 //@ serialize
typedef enum {
    //Information about the used satellite data
    GNSS_FIX_TYPE_SINGLE_FREQUENCY      = 0x00000001, /**< GNSS satellite data are received on a single frequency.
                                                           A typical example is GPS using only the C/A code on the L1 frequency.
                                                           It e.g. also applies to a combined GPS(L1)/Galileo(E1) fix since L1 and E1 share the same frequency. */
    GNSS_FIX_TYPE_MULTI_FREQUENCY       = 0x00000002, /**< GNSS satellite data are received on a multiple frequencies.
                                                           This enables the receiver to correct frequency-dependent errors such as for ionospheric delays.
                                                           An example could be a GPS receiver receiving on the L1 and L2C band. */
    GNSS_FIX_TYPE_MULTI_CONSTELLATION   = 0x00000004, /**< GNSS satellite data are received and used for the fix from more than one GNSS system.
                                                           For example, the fix could be calculated from GPS and GLONASS.
                                                           This is also possible for single frequency as several GNSS systems share the same frequencies. */
    //Information of improvement techniques based on the satellite signals
    GNSS_FIX_TYPE_PPP                   = 0x00000010, /**< PPP = Precise Point Positioning
                                                           An improved precision is achieved without differential corrections.
                                                           This is possible even for single frequency receivers, e.g. by using carrier phase tracking */
    GNSS_FIX_TYPE_INTEGRITY_CHECKED     = 0x00000020, /**< Additional integrity checks have been done to ensure the correctness of the fix. */
    //Information about used correction data
    GNSS_FIX_TYPE_SBAS                  = 0x00001000, /**< SBAS = Satellite Based Augmentation System
                                                           Correction data from an SBAS system such as WAAS, EGNOS, ... are taken into account */
    GNSS_FIX_TYPE_DGNSS                 = 0x00002000, /**< DGNSS = Differential GNSS
                                                           Correction data from Differential GNSS is taken into account */
    GNSS_FIX_TYPE_RTK_FIXED             = 0x00004000, /**< RTK = Real Time Kinematic
                                                           Correction data from a RTK fixed solution is taken into account */
    GNSS_FIX_TYPE_RTK_FLOAT             = 0x00008000, /**< RTK = Real Time Kinematic
                                                           Correction data from a RTK floating solution is taken into account */
    GNSS_FIX_TYPE_SSR                   = 0x00010000, /**< SSR = State Space Representation
                                                           Correction data according the SSR standard from RTCM SC104 or similar are taken into account */
    //Information about position propagation
    GNSS_FIX_TYPE_ESTIMATED             = 0x00100000, /**< The position is propagated without additional sensor input */
    GNSS_FIX_TYPE_DEAD_RECKONING        = 0x00200000, /**< The position is propagated with support of additional sensor input, e.g. from inertial and/or vehicle sensors */
    //Information to identify artificial GNSS fixes
    GNSS_FIX_TYPE_MANUAL                = 0x10000000, /**< Position is set by manual input */
    GNSS_FIX_TYPE_SIMULATOR_MODE        = 0x20000000, /**< Position is simulated */
} EGNSSFixType;

/**
 * @brief Description of the time scale used.
 */
 //@ serialize
typedef enum {
    GNSS_TIME_SCALE_UTC = 0,        /**< GNSS time is provided according UTC time scale (with leap seconds). This is the preferred time scale. */
    GNSS_TIME_SCALE_GPS = 1         /**< GNSS time is provided according GPS time scale (no leap seconds since 06-Jan-1980). This time scale will only be used if UTC is not available. */
} EGNSSTimeScale;

/**
 * @brief TGNSSTime::validityBits provides information about the currently valid parts of UTC date/time.
 * It is a or'ed bitmask of the EGNSSUTCValidityBits values.
 * There are separate validity bits for date end time since a GPS receiver may be able to provide time earlier than date.
 */
 //@ serialize
typedef enum {
    GNSS_TIME_TIME_VALID             = 0x00000001,    /**< Validity bit for field TGNSSTime fields hour, minute, second, ms. */
    GNSS_TIME_DATE_VALID             = 0x00000002,    /**< Validity bit for field TGNSSTime fields year, month, day. */
    GNSS_TIME_SCALE_VALID            = 0x00000004,    /**< Validity bit for field TGNSSTime field scale. */
    GNSS_TIME_LEAPSEC_VALID          = 0x00000008,    /**< Validity bit for field TGNSSTime field leapSeconds. */
} EGNSSTimeValidityBits;

/**
 * Provides the current date and time according UTC (Coordinated Universal Time)
 * Note: the uncommon numbering of day and month is chosen to be compatible with the struct tm from the standard C-Library
 */
typedef struct {
    uint64_t timestamp;             /**< Timestamp of the acquisition of the UTC date/time [ms].
                                         All sensor/GNSS timestamps must be based on the same time source. */
    uint16_t year;                  /**< Year fraction of the UTC time. Unit: [year] Number equivalent to the year (4 digits) */
    uint8_t month;                  /**< Month fraction of the UTC time. Unit: [month] Number betweeen 0 and 11 */
    uint8_t day;                    /**< Day of month fraction of the UTC time. Unit: [day]. Number between 1 and 31 */
    uint8_t hour;                   /**< Hour fraction of the UTC time. Unit: [hour] Number between 0 and 23 */
    uint8_t minute;                 /**< Minute fraction of the UTC time. Unit: [minutes] Number between 0 and 59 */
    uint8_t second;                 /**< Second fraction of the UTC time. Unit: [seconds] Number between 0 and 59.
                                         In case of a leap second this value is 60. */
    uint16_t ms;                    /**< Millisecond fraction of the UTC time. Unit: [milliseconds] Number between 0 and 999 */
    EGNSSTimeScale scale;           /**< Time scale used: UTC or GPS.*/
    int8_t leapSeconds;             /**< Number of leap seconds, i.e. difference between GPS time and UTC. Unit: [seconds].
                                         Note: value before 01-July-2015: 16; from 01-July-2015: 17; further changes possible. */
    uint32_t validityBits;          /**< Bit mask indicating the validity of each corresponding value.
                                         [bitwise or'ed @ref EGNSSTimeValidityBits values].
                                         Must be checked before usage. */
} TGNSSTime;

/**
 * @brief Enumeration to describe the type of GNSS system to which a particular GNSS satellite belongs.
 * For GNSS systems providing different signals (frequencies), separate values are provided for each signal.
 * The enumeration values can be used in bitmasks to represent combinations of satellite systems,
 * e.g. in case of multiconstellation GNSS or GNSS + augmentation systems
 */
 //@ serialize
typedef enum {
    GNSS_SYSTEM_GPS            = 0x00000001,       /**< GPS (L1 signal)*/
    GNSS_SYSTEM_GLONASS        = 0x00000002,       /**< GLONASS (L1 signal) */
    GNSS_SYSTEM_GALILEO        = 0x00000004,       /**< GALILEO (E1 signal) */
    GNSS_SYSTEM_BEIDOU         = 0x00000008,       /**< BeiDou aka COMPASS (B1 signal) */
    GNSS_SYSTEM_GPS_L2         = 0x00000010,       /**< GPS (L2 signal) */
    GNSS_SYSTEM_GPS_L5         = 0x00000020,       /**< GPS (L5 signal) */
    GNSS_SYSTEM_GLONASS_L2     = 0x00000040,       /**< GLONASS (L2 signal) */
    GNSS_SYSTEM_BEIDOU_B2      = 0x00000080,       /**< BeiDou aka COMPASS (B2 signal) */
    /* Numbers >= 0x00010000 are used to identify SBAS (satellite based augmentation system) */
    GNSS_SYSTEM_SBAS_WAAS      = 0x00010000,       /**< WAAS (North America) */
    GNSS_SYSTEM_SBAS_EGNOS     = 0x00020000,       /**< EGNOS (Europe) */
    GNSS_SYSTEM_SBAS_MSAS      = 0x00040000,       /**< MSAS (Japan) */
    GNSS_SYSTEM_SBAS_QZSS_SAIF = 0x00080000,       /**< QZSS-SAIF (Japan) */
    GNSS_SYSTEM_SBAS_SDCM      = 0x00100000,       /**< SDCM (Russia) */
    GNSS_SYSTEM_SBAS_GAGAN     = 0x00200000,       /**< GAGAN (India) */
} EGNSSSystem;

/**
 * @brief TGNSSSatelliteDetail::statusBits provides additional status information about a GNSS satellite.
 * It is a or'ed bitmask of the EGNSSSatelliteFlag values.
 */
 //@ serialize
typedef enum {
    GNSS_SATELLITE_USED                 = 0x00000001,    /**< Bit is set when satellite is used for fix. */
    GNSS_SATELLITE_EPHEMERIS_AVAILABLE  = 0x00000002,    /**< Bit is set when ephemeris is available for this satellite. */
} EGNSSSatelliteFlag;

/**
 * @brief TGNSSSatelliteDetail::validityBits provides information about the currently valid values of GNSS satellite data.
 * It is a or'ed bitmask of the EGNSSSatelliteDetailValidityBits values.
 */
 //@ serialize
typedef enum {
    GNSS_SATELLITE_SYSTEM_VALID                 = 0x00000001,    /**< Validity bit for field TGNSSSatelliteDetail::system. */
    GNSS_SATELLITE_ID_VALID                     = 0x00000002,    /**< Validity bit for field TGNSSSatelliteDetail::satelliteId. */
    GNSS_SATELLITE_AZIMUTH_VALID                = 0x00000004,    /**< Validity bit for field TGNSSSatelliteDetail::azimuth. */
    GNSS_SATELLITE_ELEVATION_VALID              = 0x00000008,    /**< Validity bit for field TGNSSSatelliteDetail::elevation. */
    GNSS_SATELLITE_CNO_VALID                    = 0x00000010,    /**< Validity bit for field TGNSSSatelliteDetail::CNo. */
    GNSS_SATELLITE_USED_VALID                   = 0x00000020,    /**< Validity bit for field TGNSSSatelliteDetail::statusBits::GNSS_SATELLITE_USED. */
    GNSS_SATELLITE_EPHEMERIS_AVAILABLE_VALID    = 0x00000040,    /**< Validity bit for field TGNSSSatelliteDetail::statusBits::GNSS_SATELLITE_EPHEMERIS_AVAILABLE. */
    GNSS_SATELLITE_RESIDUAL_VALID               = 0x00000080,    /**< Validity bit for field TGNSSSatelliteDetail::posResidual. */
} EGNSSSatelliteDetailValidityBits;

/**
 * Detailed data from one GNSS satellite.
 */
typedef struct {
    uint64_t timestamp;             /**< Timestamp of the acquisition of the satellite detail data [ms].
                                         All sensor/GNSS timestamps must be based on the same time source. */
    EGNSSSystem system;             /**< Value representing the GNSS system. */
    uint16_t satelliteId;           /**< Satellite ID.
                                         Satellite IDs are only unique within one satellite system.
                                         Satellites of different systems can be distinguished by @ref TGNSSSatelliteDetail::system.
                                         Ranges:
                                         1..32: GPS satellites (by PRN)
                                         33..64: SBAS/WAAS satellites
                                         65..96: GLONASS satellites
                                         1..64: GALILEO satellites, see Galileo OS SIS ICD, http://www.gsc-europa.eu/gnss-markets/segments-applications/os-sis-icd.
                                    */
    uint16_t azimuth;               /**< Satellite Azimuth in degrees. Value range 0..359 */
    uint16_t elevation;             /**< Satellite Elevation in degrees. Value range 0..90 */
    uint16_t CNo;                   /**< C/No (SNR) in dBHz. Range 0 to 99, 0 when not tracking */
    uint32_t statusBits;            /**< Bit mask of additional status flags.
                                        [bitwise or'ed @ref EGNSSSatelliteFlag values]. */
    int16_t posResidual;            /**< Residual in m of position calculation. Range -999 to +999, 0 if not tracking */
    uint32_t validityBits;          /**< Bit mask indicating the validity of each corresponding value.
                                        [bitwise or'ed @ref EGNSSSatelliteDetailValidityBits values].
                                        Must be checked before usage. */
} TGNSSSatelliteDetail;

/**
 * @brief TGNSSPosition::validityBits provides information about the currently valid signals
 * of the GNSS position and velocity including status and accuracy data.
 * It is a or'ed bitmask of the EGNSSPositionValidityBits values.
 */
 //@ serialize
typedef enum {
    //position
    GNSS_POSITION_LATITUDE_VALID        = 0x00000001,    /**< Validity bit for field TGNSSPosition::latitude. */
    GNSS_POSITION_LONGITUDE_VALID       = 0x00000002,    /**< Validity bit for field TGNSSPosition::longitude. */
    GNSS_POSITION_ALTITUDEMSL_VALID     = 0x00000004,    /**< Validity bit for field TGNSSPosition::altitudeMSL. */
    GNSS_POSITION_ALTITUDEELL_VALID     = 0x00000008,    /**< Validity bit for field TGNSSPosition::altitudeEll. */
    //velocity
    GNSS_POSITION_HSPEED_VALID          = 0x00000010,    /**< Validity bit for field TGNSSPosition::hSpeed. */
    GNSS_POSITION_VSPEED_VALID          = 0x00000020,    /**< Validity bit for field TGNSSPosition::vSpeed. */
    GNSS_POSITION_HEADING_VALID         = 0x00000040,    /**< Validity bit for field TGNSSPosition::heading. */
    //quality parameters: satellite constellation
    GNSS_POSITION_PDOP_VALID            = 0x00000080,    /**< Validity bit for field TGNSSPosition::pdop. */
    GNSS_POSITION_HDOP_VALID            = 0x00000100,    /**< Validity bit for field TGNSSPosition::hdop. */
    GNSS_POSITION_VDOP_VALID            = 0x00000200,    /**< Validity bit for field TGNSSPosition::vdop. */

    GNSS_POSITION_USAT_VALID            = 0x00000400,    /**< Validity bit for field TGNSSPosition::usedSatellites. */
    GNSS_POSITION_TSAT_VALID            = 0x00000800,    /**< Validity bit for field TGNSSPosition::trackedSatellites. */
    GNSS_POSITION_VSAT_VALID            = 0x00001000,    /**< Validity bit for field TGNSSPosition::visibleSatellites. */
    //quality parameters: error estimates
    GNSS_POSITION_SHPOS_VALID           = 0x00002000,    /**< Validity bit for field TGNSSPosition::sigmaHPosition. */
    GNSS_POSITION_SALT_VALID            = 0x00004000,    /**< Validity bit for field TGNSSPosition::sigmaAltitude. */
    GNSS_POSITION_SHSPEED_VALID         = 0x00008000,    /**< Validity bit for field TGNSSPosition::sigmaHSpeed. */
    GNSS_POSITION_SVSPEED_VALID         = 0x00010000,    /**< Validity bit for field TGNSSPosition::sigmaVSpeed. */
    GNSS_POSITION_SHEADING_VALID        = 0x00020000,    /**< Validity bit for field TGNSSPosition::sigmaHeading. */
    //quality parameters: overall GNSS fix status
    GNSS_POSITION_STAT_VALID            = 0x00040000,    /**< Validity bit for field TGNSSPosition::fixStatus. */
    GNSS_POSITION_TYPE_VALID            = 0x00080000,    /**< Validity bit for field TGNSSPosition::fixTypeBits. */
    //gnss system information
    GNSS_POSITION_ASYS_VALID            = 0x00100000,    /**< Validity bit for field TGNSSPosition::activatedSystems. */
    GNSS_POSITION_USYS_VALID            = 0x00200000,    /**< Validity bit for field TGNSSPosition::usedSystems. */
    //correction data information
    GNSS_POSITION_CORRAGE_VALID         = 0x00400000,    /**< Validity bit for field TGNSSPosition::correctionAge. */
} EGNSSPositionValidityBits;

/**
 * GNSS position data including velocity, status and accuracy.
 * This data structure provides all GNSS information which is typically needed
 * for positioning applications such as GNSS/Dead Reckoning sensor fusion.
 *
 * Note: For an optimum sensor fusion with vehicle and inertial sensors,
 * the velocity vector (@ref hSpeed, @ref vSpeed, @ref heading)
 * is preferred to be low latency or instantaneous velocity output
 * from the GNSS chipset.
 * This may require a specific configuration of the GNSS chipset
 * which is out of the scope of this API.
 */
typedef struct {
    uint64_t timestamp;             /**< Timestamp of the acquisition of the GNSS data [ms].
                                         All sensor/GNSS timestamps must be based on the same time source. */
    //position
    double latitude;                /**< Latitude in WGS84 in [degree]. */
    double longitude;               /**< Longitude in WGS84 in [degree]. */
    float altitudeMSL;              /**< Altitude above mean sea level (geoid) in [m]. */
    float altitudeEll;              /**< Altitude above WGS84 ellipsoid in [m]. */
    //velocity
    float hSpeed;                   /**< Horizontal speed [m/s], in direction as given by @ref heading. */
    float vSpeed;                   /**< Vertical speed [m/s].
                                         A positive value indicates an upwards movement, i.e. an ascending altitude. */
    float heading;                  /**< GNSS course angle [degree] (0 => north, 90 => east, 180 => south, 270 => west, no negative values). */
    //quality parameters: satellite constellation
    float pdop;                     /**< The positional (3D) dilution of precision. [Note: pdop^2 = hdop^2+vdop^2] */
    float hdop;                     /**< The horizontal (2D) dilution of precision. */
    float vdop;                     /**< The vertical (altitude) dilution of precision. */
    uint16_t usedSatellites;        /**< Number of satellites used for the GNSS fix. */
    uint16_t trackedSatellites;     /**< Number of satellites from which a signal is received. */
    uint16_t visibleSatellites;     /**< Number of satellites expected to be receivable, i.e. above horizon or elevation mask. */
    //quality parameters: error estimates
    float sigmaHPosition;           /**< Standard error estimate of the horizontal position in [m]. */
    float sigmaAltitude;            /**< Standard error estimate of altitude in [m]. */
    float sigmaHSpeed;              /**< Standard error estimate of horizontal speed in [m/s]. */
    float sigmaVSpeed;              /**< Standard error estimate of vertical speed in [m/s]. */
    float sigmaHeading;             /**< Standard error estimate of horizontal heading/course in [degree]. */
    //quality parameters: overall GNSS fix status
    EGNSSFixStatus fixStatus;       /**< Value representing the GNSS mode. */
    uint32_t fixTypeBits;           /**< Bit mask indicating the sources actually used for the GNSS calculation.
                                         [bitwise or'ed @ref EGNSSFixType values]. */
    //gnss system information
    uint32_t activatedSystems;      /**< Bit mask indicating the satellite systems that are activated for use
                                         [bitwise or'ed @ref EGNSSSystem values].*/
    uint32_t usedSystems;           /**< Bit mask indicating the satellite systems that are actually used for the position fix
                                         [bitwise or'ed @ref EGNSSSystem values].*/
    //correction data information
    uint16_t correctionAge;         /**< Age of used correction data in [s].
                                         Note: The kind of used correction data is identified by the corresponding bit in @ref fixTypeBits. */
    //validity bits
    uint32_t validityBits;          /**< Bit mask indicating the validity of each corresponding value.
                                         [bitwise or'ed @ref EGNSSPositionValidityBits values].
                                         Must be checked before usage. */
} TGNSSPosition;

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_GENIVI_GNSS_EXT */
