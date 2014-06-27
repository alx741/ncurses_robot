/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

				File: queue.h

*/

#ifndef QUEUE_H
#define QUEUE_H

// QUEUE NODES
typedef struct queue_node_t queue_node_t;

// QUEUE
typedef struct queue_t queue_t;


/* Returns a QUEUE pointer */
queue_t* queue_new();


/* Enqueue VALUE ptr in QUEUE
 *
 * Returns 1 if succed
 */
int enqueue(queue_t* queue, void* value);


/* Dequeue QUEUE
 * Returns value ptr
 *
 * Returns NULL if empty queue or error
 */
void* dequeue(queue_t* queue);


/* Returns 1 if QUEUE is empty */
int is_queue_empty(queue_t* queue);

#endif
