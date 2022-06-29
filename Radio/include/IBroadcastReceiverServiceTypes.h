/**
 * \file
 *         IBroadcastReceiverServiceTypes.h
 * \brief
 *         This class defines Broadcast Receiver Service types
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

#ifndef IBROADCASTRECEIVERSERVICETYPES_H
#define IBROADCASTRECEIVERSERVICETYPES_H

namespace Stla
{
    namespace Broadcast
    {

        /**
         * @brief TBandRange: struct used to store band range data
         */
        struct TBandRange final {
            int min;
            int max;
            int manualStep;
            int autoStep;
        };

        /**
         * @brief TAvailableBands: struct used to store available bands data
         */
        struct TAvailableBands final {
            std::string band;
            TBandRange bandRange;
        };

        /**
         * @brief TProgramInfo: struct used to store program info data
         */
        struct TProgramInfo final {
            std::string band;
            std::string programId;
            std::string ensembleId;
            int serviceIndex;
            int serviceCount;
            std::string channelName;
            int frequency;
            std::string programName;
            std::string ensembleName;
            int programType;
            int ecc;
            std::string quality;
            std::vector<std::string> capability;
            std::vector<std::string> announcementType;
            std::string handoverState;
            int currentPresetIndex;
            bool stationLost;
            std::string dabCodingType;
            std::string audioTransmission;
        };

        /**
         * @brief TAnnouncementInfo: struct used to store announcement info data
         */
        struct TAnnouncementInfo final {
            std::string band;
            bool direct;
            std::string programId;
            std::string programName;
            int frequency;
            std::string quality;
            std::string announcementType;
        };

        /**
         * @brief TCapabilitySettings: struct used to store capability settings data
         */
        struct TCapabilitySettings final {
            bool handover;
            bool fMTA;
            bool aF;
            bool ePG;
            bool sLS;
            bool carison;
            bool tPEG;
            bool journaline;
        };

        /**
         * @brief TDABAnnouncementSettings: struct used to store DAB announcement settings data
         */
        struct TDABAnnouncementSettings final {
            bool areaWeatherFlash;
            bool programInformation;
            bool transportFlash;
            bool newsFlash;
            bool financialReport;
            bool eventAnnouncement;
            bool specialEvent;
            bool warningService;
            bool roadTrafficFlash;
            bool sportReport;
        };

        /**
         * @brief TUserSettings: struct used to store user settings data
         */
        struct TUserSettings final {
            TCapabilitySettings capabilitySettings;
            TDABAnnouncementSettings dABAnnouncementSettings;
        };

        /**
         * @brief TPresetListItems: struct used to store preset list item data
         */
        struct TPresetListItems final {
            std::string band;
            std::string channelName;
            std::string ensembleId;
            std::string programId;
            std::vector<std::string> announcementType;
            int frequency;
            int programType;
            std::string stableProgramName;
            std::string ensembleName;
            int index;
        };

        /**
         * @brief TPresetList: struct used to store preset list data
         */
        struct TPresetList final {
            std::vector<TPresetListItems> items;
            int totalNumber;
        };

    } // namespace Broadcast

} // namespace Stla

#endif // IBROADCASTRECEIVERSERVICETYPES_H
