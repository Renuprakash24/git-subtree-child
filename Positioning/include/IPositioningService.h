/**
 * \file
 *          IPositioningService.h
 * \brief
 *          Positioning Macchina API
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

#ifndef IPOSITIONING_SERVICE_H_
#define IPOSITIONING_SERVICE_H_

#if __cplusplus <= 199711L
#include <stdint.h>
#else
#include <cstdint>
#endif

#include "Poco/OSP/Service.h"
#include "Poco/BasicEvent.h"

#include "genivi/gnss.h"
#include "IPositioningServiceTypes.h"

namespace Stla
{
    namespace Positioning
    {
        /**
         * \brief Positioning Service name to be looked up by OSP
         */
        const char* const POSITIONING_SERVICE_NAME = "com.stla.PositioningService";

        /**
         * \brief Positioning Service interface
         *
         * Positioning Service is responsible for providing vehicle location data
         * within Application Framework and it is implemented as a Macchina OSP
         * service.
         *
         * The list of provided information:
         *      - GNSS position
         *      - GNSS time
         *      - GNSS satellite details
         *      - GNSS time to first fix
         *      - Last valid GNSS position
         *      - Enhanced position
         *      - Last valid Enhanced position
         *      - Vehicle traveled distance
         *
         * Most of the data can be accesed by a client on demand (via getters) or
         * on notification basis. The notification is done using Poco::BasicEvent.
         *
         * GNSS information is provided in GENIVI format.
         */
        class IPositioningService : public Poco::OSP::Service
        {
        public:
            /**
             * \brief Class smart pointer definition
             *
             * Because Positioning service is an OSP service, memory management is
             * done by the platform itself. Whenever a client looks up for a service,
             * the platform returns a pointer to the actual service which must be
             * stored in a smart pointer.
             *
             * Usage:
             * \code{.cpp}
             * Poco::OSP::ServiceRef::Ptr pServiceRef = pBundleContext->registry().findByName(POSITIONING_SERVICE_NAME);
             * if(pServiceRef) // Service was found
             * {
             *     TCU::Positioning::IPositioningService::Ptr _posService = pServiceRef->castedInstance<IPositioningService>();
             * }
             * \endcode
             */
            typedef Poco::AutoPtr<IPositioningService> Ptr;

            /**
             * \brief Positioning Service destructor
             */
            virtual ~IPositioningService() = 0;

            /**
             * \brief  Getter for the last updated GNSS Position
             *
             * This function allows to get the GNSS position on demand.
             * GNSS position is updated @1Hz and has only followings fields available:
             *      - timestamp
             *      - altitudeEll
             *      - altitudeMSL
             *      - sigmaAltitude
             *      - heading
             *      - latitude
             *      - longitude
             *      - sigmaHPosition
             *      - sigmaHSpeed
             *      - sigmaHeading
             *      - hSpeed
             *      - vSpeed
             *      - pdop
             *      - hdop
             *      - vdop
             *      - usedSatellites
             *      - fixStatus
             *      - validityBits
             *      - fixTypeBits:
             *              - GNSS_FIX_TYPE_SINGLE_FREQUENCY
             *              - GNSS_FIX_TYPE_MULTI_FREQUENCY (only in SOP2)
             *              - GNSS_FIX_TYPE_MULTI_CONSTELLATION
             *              - GNSS_FIX_TYPE_SBAS
             *
             * Unavailable fields:
             *      - trackedSatellites
             *      - visibleSatellites
             *      - sigmaVSpeed
             *      - activatedSystems
             *      - usedSystems
             *      - correctionAge
             *
             * \note This function returns pure GNSS position
             *
             * \note Getter should be used only if position is needed occasionally.
             * If GNSS position is required more often, then use \link gnssPositionUpdateEvent \endlink.
             *
             * \return Last updated GNSS position
             */
            virtual TGNSSPosition getGNSSPosition() = 0;

            /**
             * \brief  Getter for the last valid GNSS Position
             *
             * This function allows to get the last valid GNSS position.
             * A valid GNSS position is considered to be a position which has 3D fix.
             *
             * The GNSS position structure has only the followings fields available:
             *      - timestamp
             *      - altitudeEll
             *      - altitudeMSL
             *      - sigmaAltitude
             *      - heading
             *      - latitude
             *      - longitude
             *      - sigmaHPosition
             *      - sigmaHSpeed
             *      - sigmaHeading
             *      - hSpeed
             *      - vSpeed
             *      - pdop
             *      - hdop
             *      - vdop
             *      - usedSatellites
             *      - fixStatus
             *      - validityBits
             *      - fixTypeBits:
             *              - GNSS_FIX_TYPE_SINGLE_FREQUENCY
             *              - GNSS_FIX_TYPE_MULTI_FREQUENCY (only in SOP2)
             *              - GNSS_FIX_TYPE_MULTI_CONSTELLATION
             *              - GNSS_FIX_TYPE_SBAS
             *
             * Unavailable fields:
             *      - trackedSatellites
             *      - visibleSatellites
             *      - sigmaVSpeed
             *      - activatedSystems
             *      - usedSystems
             *      - correctionAge
             *
             * \note In case no valid position was acquired during current life cycle, the
             * status will be set to <b>NO FIX</b>.
             *
             * The structure has the same fields available as the ones mentioned in \link getGNSSPosition \endlink description.
             *
             * \note This function returns last valid pure GNSS position
             *
             * \return Last valid GNSS position
             */
            virtual TGNSSPosition getLastValidGNSSPosition() = 0;

            /**
             * \brief Poco Event which is triggered when new GNSS position is available
             *
             * This event is triggered @1Hz and carries newly updated GNSS position.
             * The GNSS position structure has only the followings fields available:
             *      - timestamp
             *      - altitudeEll
             *      - altitudeMSL
             *      - sigmaAltitude
             *      - heading
             *      - latitude
             *      - longitude
             *      - sigmaHPosition
             *      - sigmaHSpeed
             *      - sigmaHeading
             *      - hSpeed
             *      - vSpeed
             *      - pdop
             *      - hdop
             *      - vdop
             *      - usedSatellites
             *      - fixStatus
             *      - validityBits
             *      - fixTypeBits:
             *              - GNSS_FIX_TYPE_SINGLE_FREQUENCY
             *              - GNSS_FIX_TYPE_MULTI_FREQUENCY (only in SOP2)
             *              - GNSS_FIX_TYPE_MULTI_CONSTELLATION
             *              - GNSS_FIX_TYPE_SBAS
             *
             * Unavailable fields:
             *      - trackedSatellites
             *      - visibleSatellites
             *      - sigmaVSpeed
             *      - activatedSystems
             *      - usedSystems
             *      - correctionAge
             *
             * Usage:
             * \code{.cpp}
             * void ClientClass::startup()
             * {
             *      Poco::OSP::ServiceRef::Ptr pServiceRef = pBundleContext->registry().findByName(POSITIONING_SERVICE_NAME);
             *      if(pServiceRef) // Service was found
             *      {
             *          TCU::Positioning::IPositioningService::Ptr _posService = pServiceRef->castedInstance<IPositioningService>();
             *          _posService->gnssPositionUpdateEvent += Poco::delegate(this, &ClientClass::onGnssPositionUpdate);
             *      }
             * }
             *
             * void ClientClass::onGnssPositionUpdate(const TGNSSPosition& data)
             * {
             *      // Do stuff with data
             * }
             *
             * void ClientClass::shutdown()
             * {
             *      if(_posService)
             *      {
             *          _posService->gnssPositionUpdateEvent -= Poco::delegate(this, &ClientClass::onGnssPositionUpdate);
             *          _posService = nullptr;
             *      }
             * }
             * \endcode
             *
             * \note This event is triggered when new pure GNSS position is available
             *
             * \warning All registered callbacks MUST be unregistered before client instance is destroyed, otherwise
             * Macchina instance will crash!
             */
            Poco::BasicEvent<const TGNSSPosition> gnssPositionUpdateEvent;

            /**
             * \brief  Getter for the last updated GNSS time
             *
             * This function allows to get the GNSS time on demand.
             * GNSS time is updated @1Hz and has only followings fields available:
             *      - timestamp
             *      - year
             *      - month
             *      - day
             *      - hour
             *      - minute
             *      - second
             *      - ms
             *      - scale
             *      - validityBits
             *
             * Fields not available:
             *      - leapSeconds
             *
             * \note Getter should be used only if time is needed occasionally.
             * If GNSS time is required more often, then use \link gnssTimeUpdateEvent \endlink.
             *
             * \return Last updated GNSS time
             */
            virtual TGNSSTime getGNSSTime() = 0;

            /**
             * \brief Poco Event which is triggered when new GNSS time update is available
             *
             * This event is triggered @1Hz and carries newly updated GNSS time.
             * The GNSS time structure has only followings fields available:
             *      - timestamp
             *      - year
             *      - month
             *      - day
             *      - hour
             *      - minute
             *      - second
             *      - ms
             *      - scale
             *      - validityBits
             *
             * Fields not available:
             *      - leapSeconds
             *
             *
             * Usage:
             * \code{.cpp}
             * void ClientClass::startup()
             * {
             *      Poco::OSP::ServiceRef::Ptr pServiceRef = pBundleContext->registry().findByName(POSITIONING_SERVICE_NAME);
             *      TCU::Positioning::IPositioningService::Ptr _posService = pServiceRef->castedInstance<IPositioningService>();
             *      _posService->gnssTimeUpdateEvent += Poco::delegate(this, &ClientClass::onGnssTimeUpdate);
             * }
             *
             * void ClientClass::onGnssTimeUpdate(const TGNSSTime& data)
             * {
             *      // Do stuff with data
             * }
             *
             * void ClientClass::shutdown()
             * {
             *      _posService->gnssTimeUpdateEvent -= Poco::delegate(this, &ClientClass::onGnssTimeUpdate);
             *      _posService = nullptr;
             * }
             * \endcode
             *
             * \warning All registered callbacks MUST be unregistered before client instance is destroyed, otherwise
             * Macchina instance will crash!
             */
            Poco::BasicEvent<const TGNSSTime> gnssTimeUpdateEvent;

            /**
             * \brief  Getter for the last updated GNSS satellite details
             *
             * This function allows to get the GNSS satellite details on demand.
             * GNSS satellite details are updated @1Hz and have only followings fields available:
             *      - timestamp
             *      - system
             *      - satelliteId
             *      - azimuth
             *      - elevation
             *      - CNo
             *      - statusBits
             *      - validityBits
             *
             * Fields not available:
             *      - posResidual
             *
             * \note Getter should be used only if satellite details are needed occasionally.
             * If GNSS satellite details are required more often, then use \link gnssSatelliteDetailsUpdateEvent \endlink.
             *
             * \return Last updated GNSS satellite details list
             */
            virtual TGNSSSatelliteDetails getGNSSSatelliteDetails() = 0;

            /**
             * \brief Poco Event which is triggered when new GNSS satellite details update is available
             *
             * This event is triggered @1Hz and carries newly updated GNSS satellite details.
             * The GNSS satellite details structure has only followings fields available:
             *      - timestamp
             *      - system
             *      - satelliteId
             *      - azimuth
             *      - elevation
             *      - CNo
             *      - statusBits
             *      - validityBits
             *
             * Fields not available:
             *      - posResidual
             *
             * Usage:
             * \code{.cpp}
             * void ClientClass::startup()
             * {
             *      Poco::OSP::ServiceRef::Ptr pServiceRef = pBundleContext->registry().findByName(POSITIONING_SERVICE_NAME);
             *      if(pServiceRef) // Service was found
             *      {
             *          TCU::Positioning::IPositioningService::Ptr _posService = pServiceRef->castedInstance<IPositioningService>();
             *          _posService->gnssSatelliteDetailsUpdateEvent += Poco::delegate(this, &ClientClass::onGnssSatelliteDetailsUpdate);
             *      }
             * }
             *
             * void ClientClass::onGnssSatelliteDetailsUpdate(const TGNSSSatelliteDetails& data)
             * {
             *      // Do stuff with data
             * }
             *
             * void ClientClass::shutdown()
             * {
             *      if(_posService)
             *      {
             *          _posService->gnssSatelliteDetailsUpdateEvent -= Poco::delegate(this, &ClientClass::onGnssSatelliteDetailsUpdate);
             *          _posService = nullptr;
             *      }
             * }
             * \endcode
             *
             * \warning All registered callbacks MUST be unregistered before client instance is destroyed, otherwise
             * Macchina instance will crash!
             */
            Poco::BasicEvent<const TGNSSSatelliteDetails> gnssSatelliteDetailsUpdateEvent;

            /**
             * \brief  Getter for the GNSS time to first fix
             *
             * This function allows to get the Time To First(3D) Fix(TTFF) value represented in
             * <b>seconds</b>.
             *
             * \note If no 3D Fix was acquired during current life cycle, the returned value
             * will be <b>0</b>.
             *
             * \return GNSS Time To First Fix
             */
            virtual uint32_t getTimeToFirstFix() = 0;

            /**
             * \brief  Getter for the last updated Enhanced Position
             *
             * This function allows to get the Enhanced position on demand.
             * Enhanced position is updated @10Hz and has all fields available.
             *
             * \note Getter should be used only if enhanced position is needed occasionally.
             * If Enhanced position is required more often, then use \link enhancedPositionUpdateEvent \endlink.
             *
             * \return Last updated Enhanced position
             */
            virtual TEnhancedPosition getEnhancedPosition() = 0;

            /**
             * \brief  Getter for the last valid Enhanced Position
             *
             * This function allows to get the last valid Enhanced position.
             * A valid Enhanced position is considered to be a position which was
             * produced by a calibrated algorithm.
             *
             * \note In case no valid position was calculated during current life cycle, the
             * status will be set to <b>NONE</b>.
             *
             * \return Last valid Enhanced position
             */
            virtual TEnhancedPosition getLastValidEnhancedPosition() = 0;

            /**
             * \brief Poco Event which is triggered when new Enhanced position is available
             *
             * This event is triggered @10Hz and carries newly updated Enhanced position.
             * The structure has the same fields available as the ones mentioned in \link getEnhancedPosition \endlink description.
             *
             * Usage:
             * \code{.cpp}
             * void ClientClass::startup()
             * {
             *      Poco::OSP::ServiceRef::Ptr pServiceRef = pBundleContext->registry().findByName(POSITIONING_SERVICE_NAME);
             *      if(pServiceRef) // Service was found
             *      {
             *          TCU::Positioning::IPositioningService::Ptr _posService = pServiceRef->castedInstance<IPositioningService>();
             *          _posService->enhancedPositionUpdateEvent += Poco::delegate(this, &ClientClass::onEnhancedPositionUpdate);
             *      }
             * }
             *
             * void ClientClass::onEnhancedPositionUpdate(const TEnhancedPosition& data)
             * {
             *      // Do stuff with data
             * }
             *
             * void ClientClass::shutdown()
             * {
             *      if(_posService)
             *      {
             *          _posService->enhancedPositionUpdateEvent -= Poco::delegate(this, &ClientClass::onEnhancedPositionUpdate);
             *          _posService = nullptr;
             *      }
             * }
             * \endcode
             *
             * \warning All registered callbacks MUST be unregistered before client instance is destroyed, otherwise
             * Macchina instance will crash!
             */
            Poco::BasicEvent<const TEnhancedPosition> enhancedPositionUpdateEvent;

            /**
             * \brief  Getter for the vehicle traveled distance
             *
             * This function allows to get the traveled distance represented in <b>meters</b>.
             *
             * Traveled distance is calculated based on Enhanced position and it is refreshed
             * every 1 second.
             * Start of trip conditions: ETAT_GMP is "Engine running" and ETAT_PRINCIP_SEV is "Contact"
             * End of trip conditions: ETAT_GMP is "Engine not running" for more than 10s or system is going to sleep
             *
             * \note Getter should be used only if information is needed occasionally.
             * If information is required more often, then use \link traveledDistanceUpdateEvent \endlink.
             * \note As information is refreshed only once per second, getter shall not be
             * called often than this interval.
             *
             * \return Vehicle driven distance from start of life cycle
             */
            virtual uint32_t getTraveledDistance() = 0;

            /**
             * \brief Poco Event which is triggered when new driven distance information is available
             *
             * This event is triggered @1Hz and carries newly updated driven distance.
             *
             * Usage:
             * \code{.cpp}
             * void ClientClass::startup()
             * {
             *      Poco::OSP::ServiceRef::Ptr pServiceRef = pBundleContext->registry().findByName(POSITIONING_SERVICE_NAME);
             *      if(pServiceRef) // Service was found
             *      {
             *          TCU::Positioning::IPositioningService::Ptr _posService = pServiceRef->castedInstance<IPositioningService>();
             *          _posService->traveledDistanceUpdateEvent += Poco::delegate(this, &ClientClass::onTraveledDistanceUpdate);
             *      }
             * }
             *
             * void ClientClass::onTraveledDistanceUpdate(const uint32_t& data)
             * {
             *      // Do stuff with data
             * }
             *
             * void ClientClass::shutdown()
             * {
             *      if(_posService)
             *      {
             *          _posService->traveledDistanceUpdateEvent -= Poco::delegate(this, &ClientClass::onTraveledDistanceUpdate);
             *          _posService = nullptr;
             *      }
             * }
             * \endcode
             *
             * \warning All registered callbacks MUST be unregistered before client instance is destroyed, otherwise
             * Macchina instance will crash!
             */
            Poco::BasicEvent<const uint32_t> traveledDistanceUpdateEvent;
        };

        inline IPositioningService::~IPositioningService() { }
    }
}

#endif
