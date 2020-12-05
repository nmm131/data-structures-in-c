//
//  Queue.c
//

// stdlib provides malloc and free
#include <stdlib.h>
// stdbool defines bool
#include <stdbool.h>
// asserts are used for checking that the queue exists
#include <assert.h>
// calls the queue supports are included for consistency checking
#include "Queue.h"
// the queue uses a linked list to implement a queue behavior (FIFO)
// enqueue and pop will be done from the list front.
#include "LinkedList.h"

/*
 initQueue() allocates a queue structure and initializes its contents.
 This consists of creating the underlying linked list and declaring the
 queue to be empty
*/
Queue initQueue()
{
    // allocate a queue structure and abort if the allocation failed
    Queue Q = (Queue) malloc(sizeof(QueueInfo));
    assert (Q!= NULL);
    AllocationCount++;
    // allocate and initialize the underlying linked list
    Q->LL = LL_Init();
    // we are empty until an item is pushed
    Q->empty = true;
    // return the queue to the caller
    return Q;
}

/*
peek() will return the UserData at the front of the queue, but leave the data
on the queue by calling the linked list GetFront() with a RETAIN option
*/
UserData    peek(Queue Q)
{
	assert((Q != NULL) && (Q->empty != true));
	return LL_GetFront(Q->LL, RETAIN_NODE);
}

/*
empty() returns the boolean indicating the queue is currently empty
*/
bool empty(Queue Q)
{
	assert(Q != NULL);
	return Q->empty;
}

/*
 deleteQueue() calls the linked list delete to free up all of its nodes and, on return,
 frees up the queue itself.  it returns NULL to indicate that there is no longer a
 queue.
 */
//Queue deleteQueue(Queue Q)
//{
//  ****************** your implementation goes here
//}

/* enqueue() calls the linked list to place the UserData at the end of
   the linked list. Since an enqueue is being done, the queue is no longer empty
*/
//void enqueue (Queue Q, UserData D)
//{
//  ****************** your implementation goes here
//}

/*
   dequeue() will fetch the UserData at the front of the linked list and return it to
   caller.  It updates the queue empty status by seeing if the linked list was
   holding only a single item before the removal from the linked list occurs.
*/
//UserData dequeue (Queue Q)
//{
//  ****************** your implementation goes here
//}

