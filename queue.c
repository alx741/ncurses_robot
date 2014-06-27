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

				File: queue.c

*/

#include "queue.h"

#include <stdlib.h>


// QUEUE NODES
typedef struct queue_node_t
{
	struct queue_node_t* next;
	struct queue_node_t* previous;
	void* payload;
}queue_node_t;

// QUEUE
typedef struct queue_t
{
	queue_node_t* head;
	queue_node_t* tail;
}queue_t;


/* Returns a QUEUE pointer */
queue_t* queue_new()
{
	queue_t* queue = (queue_t*) malloc(sizeof(queue_t));

	// Init Queue
	queue.head = NULL;
	queue.tail = NULL;
}


/* Enqueue VALUE ptr in QUEUE
 *
 * Returns 1 if succed
 */
int enqueue(queue_t* queue, void* value)
{
	// Create node
	queue_node_t* node = (queue_node_t*) malloc(sizeof(queue_node_t));
	node -> payload = value;

	if( queue -> tail == NULL ) //Empty queue
	{
		node -> next = NULL;
		node -> previous = NULL; 
		queue -> head = node;
		queue -> tail = node;
	}
	else
	{
		node -> next = queue -> tail;
		node -> previous = NULL;
		queue -> tail -> previous = node; 
		queue -> tail = node;
	}

	return 1;
}



/* Dequeue QUEUE
 * Returns value ptr
 *
 * Returns NULL if empty queue or error
 */
void* dequeue(queue_t* queue)
{
	void* value;

	if( queue -> tail == NULL ) //Empty queue
	{
		return NULL;
	}
	else
	{
		value = queue -> head -> payload; 

		if( queue -> tail == queue -> head ) // Single node queue
		{ 
			// Free node memory
			free(queue -> head);

			// Empty queue
			queue -> tail = NULL;
			queue -> head = NULL; 

			return value;
		}
		else
		{ 
			queue -> head = queue -> head -> previous;
			
			// Free last HEAD memory
			free(queue -> head -> next);

			queue -> head -> next = NULL;

			return value;
		}
	}

	return NULL; 
}
		

/* Returns 1 if QUEUE is empty */
int is_queue_empty(queue_t* queue)
{
	if( queue -> tail == 0 )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


//int main()
//{
//	queue_t QUEUE;
//	QUEUE.tail = NULL;
//	QUEUE.head = NULL;
//
//	void* value = NULL;
//
//	enqueue(&QUEUE, value);
//	enqueue(&QUEUE, value);
//	enqueue(&QUEUE, value);
//
//	dequeue(&QUEUE);
//	dequeue(&QUEUE);
//	dequeue(&QUEUE);
//
//	return 0;
//}
//
