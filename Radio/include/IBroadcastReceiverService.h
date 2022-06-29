/**
 * \file
 *         IBroadcastReceiverService.h
 * \brief
 *         This class is a interface for Broadcast Receiver Service
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

#ifndef IBROADCASTRECEIVERSERVICE_H
#define IBROADCASTRECEIVERSERVICE_H

#include "Poco/OSP/Service.h"
#include "Poco/AutoPtr.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"

#include "IBroadcastReceiverServiceTypes.h"

namespace Stla {

    namespace Broadcast {

        /**
         * @brief Name of the broadcast receiver service
         */
        const char* const BROADCAST_RECEIVER_SERVICE_NAME = "stla.broadcast.receiver.service.base";

        /**
         * @brief The IBroadcastReceiverService class: Interface for Broadcast Receiver Service.
         */
        class IBroadcastReceiverService: public Poco::OSP::Service
        {
        public:
            typedef Poco::AutoPtr<IBroadcastReceiverService> Ptr;

            /**
             * @brief availableBands: event used to notify available bands data
             */
            Poco::BasicEvent<const std::vector<TAvailableBands> > availableBands;

            /**
             * @brief programInfo: event used to notify program info data
             */
            Poco::BasicEvent<const TProgramInfo> programInfo;

            /**
             * @brief announcementInfo: event used to notify announcement info data
             */
            Poco::BasicEvent<const TAnnouncementInfo> announcementInfo;

            /**
             * @brief presetList: event used to notify preset list data
             */
            Poco::BasicEvent<const TPresetList> presetList;

            /**
             * @brief userSettings: event used to notify user settings data
             */
            Poco::BasicEvent<const TUserSettings> userSettings;

            /**
             * @brief getProgramInfo: getter for the program information
             * @return nullptr if not initialized or not available, the cached content otherwise; check first with isNull if valid.
             */
            virtual  const Poco::SharedPtr<TProgramInfo> getProgramInfo() = 0;

            /**
             * @brief getAvailableBands: getter for the available bands information
             * @return nullptr if not initialized or not available, the cached content otherwise; check first with isNull if valid.
             */
            virtual const Poco::SharedPtr<std::vector<TAvailableBands> > getAvailableBands() = 0;

            /**
             * @brief getAnnouncementInfo: getter for the announcement information
             * @return nullptr if not initialized or not available, the cached content otherwise; check first with isNull if valid.
             */
            virtual const Poco::SharedPtr<TAnnouncementInfo> getAnnouncementInfo()= 0;

            /**
             * @brief getPresetList: getter for the preset list
             * @return nullptr if not initialized or not available, the cached content otherwise; check first with isNull if valid.
             */
            virtual const Poco::SharedPtr<TPresetList> getPresetList() = 0;

            /**
             * @brief getUserSettings: getter for the user settings
             * @return nullptr if not initialized or not available, the cached content otherwise; check first with isNull if valid.
             */
            virtual const Poco::SharedPtr<TUserSettings> getUserSettings() = 0;

            /**
             * \brief IBroadcastReceiverService: virtual destructor
             */
            virtual ~IBroadcastReceiverService() {};
        };

    } // namespace Broadcast

} // namespace Stla

#endif // IBROADCASTRECEIVERSERVICE_H
