/**
 * \file
 *          IPosDataProvider.h
 *
 * \brief
 *          The interface for the PosDataProvider service
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

#ifndef IPOSDATAPROVIDER_H
#define IPOSDATAPROVIDER_H

#include "genivi/gnss.h"
#include <string>
#include "Poco/BasicEvent.h"
#include <deque>


namespace Stla{
namespace Positioning {

typedef unsigned int PosTriggerId;

typedef struct{
    PosTriggerId trigger_id;
    TGNSSPosition data;
}GNSS_Payload;

#ifdef DOXYGEN_WORKING
class IPosDataProvider
#else
class __attribute__((visibility("default"))) IPosDataProvider
#endif
{
public:

    /**
     * @brief IPosDataProvider: default destructor
     */
    virtual ~IPosDataProvider() = default;

    /**
     * @brief Event triggered to send cached data to the client
     * @param GNSS_Payload struct containing the triggered id and the data structure
     */
    Poco::BasicEvent<const GNSS_Payload> cachedDataDeliverEvent;

    /**
     * @brief Event triggered to send live data to the client
     * @param GNSS_Payload struct containing the triggered id and the data structure
     */
    Poco::BasicEvent<const GNSS_Payload> liveDataDeliverEvent;

    /**
     * @brief Event triggered when notifications are missing from positioning service
     */
    static Poco::BasicEvent<void> dataIntakeInterrupted;

    /**
     * @brief Event triggered when notifications from positioning service start comming again after an interruption
     */
    static Poco::BasicEvent<void> dataIntakeResumed;    

    /**
     * @brief Function used to request positioning data for a limited or unlimited period of time
     * @param past: Specifies how much data should be sent from the cachedDataDeliverEvent
     *              0 - no data from the cache will be sent
     *              1-120 - only the data cached in the last 'past' seconds will be sent
     * @param future: Specifies the subscription period for real time data
     *                0 - real time data will be sent infinite.
     *                1-2147483647 - send real time data for the next 'future' seconds
     * @return: Unique triggerID. The triggerIDs are unique only in the context of this instance
     *          It will be used to cancel the consumption request or to identify the request
     */
    virtual PosTriggerId posDataRequest(unsigned int past, int future) = 0;

    /**
     * @brief Cancel a trigger
     * @param trigger_id: The id of the trigger to be canceled
     * @return true if the trigger was canceled, false if there was no active/valid trigger
     */
    virtual bool cancel(const PosTriggerId& trigger_id) = 0;
};

}
}
#endif // IPOSDATAPROVIDER_H
