#pragma once

#include "hash.h"

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup schedule Schedule

    The schedule module provides methods for IEEE 2030.5 event scheduling.
    Scheduling is done per function set such as Pricing, Distributed Energy
    Resources (DER), or Demand Response / Load Control (DRLC).

    The events of each function set are independent and each EndDevice may
    utilitize one or more function sets, therefore an EndDevice could have one
    or more independent event schedules. 
    @{
*/

#define SCHEDULE_UPDATE (EVENT_NEW+10)

enum EventStatus {Scheduled, Active, Canceled, CanceledRandom,
		  Superseded, Aborted, Completed, ActiveWait,
		  ScheduleSuperseded};

/** @brief An EventBlock is an Event instance scheduled for a particular
    EndDevice.

    The start and end times are effective times with the event
    randomization already applied, primacy is derived the context that the event
    occured.
*/
typedef struct _EventBlock {
  struct _EventBlock *next; ///< is a pointer to the next EventBlock
  void *event; ///< is a pointer to the Event Stub
  void *program; ///< is a pointer to the DERProgram for DERControls
  void *context; //< is a pointer to device specific information
  uint8_t status; ///< the schedule event status
  uint8_t primacy;  ///< associated event primacy
  uint32_t der; ///< bitmask of active DER controls
  int64_t start; ///< the effective start time
  int64_t end; ///< the effective end time
} EventBlock;

/** @brief A Schedule organizes the events of a particular function set for an
    EndDevice in terms of the rules in section 12.1.3 Event Rules and Guidlines.
    
    Events are assigned to an EventBlock which can belong to one of three
    queues, `scheduled`, `active`, and `superseded`. EventBlocks that
    correspond with server events that have been marked Canceled or Superseded
    belong to none of these queues and are eventually removed from the schedule
    when the events expire.

    Initially all EventBlocks are inserted into the `scheduled` queue using the
    rules for overlapping and nested events. Future events that are superseded
    by scheduling are marked `ScheduleSuperseded` and are placed in the
    superseded queue. If the set of events changes for some reason, these
    events may eventually rejoin the `scheduled` queue.

    When EventBlocks in the scheduled queue become active (i.e when the current
    time matches the effective start time) they are transfered to the `active`
    queue, in the process they may be superseded by existing active EventBlocks
    or they may supersede other active EventBlocks. In these cases the
    superseded EventBlocks are removed from the schedule and a Response is sent
    to the server with the response status EventSuperseded.

    If an EventBlock is sucessfully transfered to the `active` queue and the
    EventStatus.currentStatus retrieved from the server is Active then an
    internal EVENT_START event is generated for current time. If the
    EventStatus.currentStatus is Scheduled, then the event will be marked
    `ActiveWait` and remain in the active queue, but the EVENT_START event will
    only be generated when currentStatus for the event changes to Active. When
    the EventBlock expires (i.e the current time matches the effective end
    time) or it is superseded then an internal EVENT_END event is generated
    at that time for the EventBlock.
*/
typedef struct {
  int64_t next;
  Stub *device; ///< EndDevice that is the subject of scheduling
  void *context; //< is a pointer to device specific information
  HashTable *blocks; /**< HashTable of EventBlocks that belong to the schedule
			using the Event mRID as the hash key. */
  EventBlock *scheduled; ///< EventBlock queue sorted by effective start time
  EventBlock *active; ///< EventBlock queue sorted by effective end time
  EventBlock *superseded; ///< EventBlock queue sorted by effective start time
} Schedule;

/** @brief Send an event response to the server on the behalf of a device.
    @param device is a pointer to an EndDevice Stub
    @param event is a pointer to an Event Stub
    @param status is the status of the event response (@ref ResponseType)
*/
void device_response (Stub *device, Stub *event, int status);

/** @brief Add an event to a schedule with an associated primacy.
    @param s is a pointer to a Schedule
    @param event is a pointer to an Event
    @param primacy is the associated primacy for the event
    @returns a pointer to an EventBlock belonging to the schedule
*/
EventBlock *schedule_event (Schedule *s, Stub *event, int primacy);

/** @brief Update the schedules associated with an event.
    @param event is a pointer to an event Stub
*/
void event_update (Stub *event);

/** @brief Update the schedule based upon the current time.
    @param s is a pointer to a Schedule
*/
void update_schedule (Schedule *s);

/** @brief Initialize the schedule.
    @param s is a pointer to a Schedule
*/
void schedule_init (Schedule *s);

/** @} */

