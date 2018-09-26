#pragma once

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup event_queue Event Queue

    Provides a timed event queue.
    @{
*/

#define EVENT_TIMER (EVENT_NEW+2)
#define EVENT_START (EVENT_NEW+3)
#define EVENT_END (EVENT_NEW+4)
// #define EVENT_UPDATE (EVENT_NEW+5)

/** @brief Insert an event into the queue.
    @param data is a pointer to the event data
    @param type is the type of the event
    @param time is the time at which the event becomes active
*/
void insert_event (void *data, int type, int64_t time);

/** @brief Remove all events from the queue that match the event data.
    @brief data is a pointer to the event data
*/
void remove_event (void *data);

/** @brief Returns (and removes) the next active event from the queue if any.
    @param any is a pointer to value that receives the event data
    @returns the type of event or EVENT_NONE if there are no active events in
    the queue.
*/
int next_event (void **any);

/** @brief Create an event queue timer to wake up @ref event_poll. */
void event_init ();

/** @} */

typedef struct _Event {
  struct _Event *next;
  void *data; int type;
  int64_t time;
} Event;

