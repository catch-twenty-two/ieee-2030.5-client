#pragma once

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup queue Queue
    @{
*/

/** @brief Queue structure */
typedef struct {
  List *first; ///< is the first item in the queue
  List *last; ///< ist the last item in the queue
} Queue;

/** @brief Return the head of the queue without removing it.
    @param queue is a pointer to a Queue
    @return the head of the queue
 */
#define queue_peek(queue) (void *)(queue)->first

/** @brief Test if the queue is empty.
    @param queue is a pointer to a Queue
    @return true if the queue is not empty
 */
#define queue_empty(queue) ((queue)->first == NULL)

/** @brief Return the tail of the queue
    @param queue is a pointer to a Queue
    @return the tail of the queue
 */
#define queue_tail(queue) (void *)(queue)->last

/** @brief Clear the queue
    @param queue is a pointer to a Queue
 */
#define queue_clear(queue) (queue)->first = (queue)->last = NULL

/** @brief Insert linked item at the tail of the queue.
    @param queue is a pointer to a Queue
    @param item is a pointer to a linked item
 */
void queue_add (Queue *queue, void *item);

/** @brief Remove linked item from the head of the queue.
    @param queue is a pointer to a Queue
    @return pointer to a linked item
 */
void *queue_remove (Queue *queue);

/** @brief Free queued items.
    @param queue is a pointer to a Queue
 */
void queue_free (Queue *queue);

/** @} */

    
