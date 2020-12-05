// PriorityQueueTester will demonstrate the init, enqueue, peek, dequeue and delete
// for three different types of queues (a queue without priority, a queue where the
// lowest number is the highest priority and a queue where the highest number is
// the highest priority.
//      - It prints the type of queue being tested
//      - It builds a queue that holds UserData generated based on user's
//        current time across an interval
//      - It peeks at the queue, returning UserData
//      - It dequeues UserData from the queue, returning UserData
//      - As it dequeues, every so often it enqueues other
//        generated time data to prove the queue is still
//        intact, to get removed just like other queue data
//      - it uses empty() to determine if the queue holds any data that
//          can be dequeued or peeked
//      - when done, it deletes the queue
// For demonstration purposes, it shows the number of allocations for
// everything it does (NOTE: it prints only once after generating time data).

#include <stdio.h>
// we will use rand() and srand() from stdlib.h
// we will be getting system data and time from time.h
#include <time.h>
#include <stdlib.h>
// we will use strcpy() and strlen() from string.h
#include <string.h>
// we use a bool from stdbool.h
#include <stdbool.h>
// we use Queue functions from Queue.h
#include "Queue.h"
// we use UserData for the queue
#include "UserData.h"

#define MAXPRIO 4
#define DEQUEUESPERENQUEUE 3
#define INITIALENQUEUES 15

// this local function receives a queue
// as an argument to populates, peek
// and dequeue it, while  printing
// messages and AllocationCount
// along the way
static void          Runtest (Queue Q);
// this local function receives a queue
// and a number of items as arguments
// so to fill the queue with that data
static void          buildQueue (Queue Q, int numItems);
// this local function creates a data
// and assign it a random priority number
// between 1 and MAXPRIO
static UserData      genTimePriorityUserData ();
// this local function takes two UserData
// objects in order to update a queue
// by comparing priority numbers of those
// two UserData objects. It returns true or false
// so that queue knows whether data with lower
// priority numbers are listed as higher priority
// in the queue
static bool          LowestNumIsHighestPriority (UserData first, UserData second);
// this local function takes two UserData
// objects in order to update a queue
// by comparing priority numbers of those
// two UserData objects. It returns true or false
// so that queue knows whether data with higher
// priority numbers are listed as higher priority
// in the queue
static bool          HighestNumIsHighestPriority (UserData first, UserData second);

// this is an int variable that is defined elsewhere
// in the source code. It is listed here as extern
// so PriorityQueueDemo.c can declare that same
// variable which is already defined
extern int AllocationCount;

// buildQueue takes a queue and a number
// in order to fill the queue with
// data and print that data along with
// its priority number
void buildQueue (Queue Q, int numItems)
{
    for (; numItems > 0; numItems--)
    {
        UserData D = genTimePriorityUserData();
        enqueue (Q, D);
        printf ("Time = %s queued at priority %d\n", D.time, D.priority);
    }
    return;
}

//****************************************************
// Function: genTimePriorityUserData
//    This function fills a UserData structure with the current
//    system time and a random priority from 1 to MAXPRIO.
//    Before exiting, this routine spins for 1 second so
//    that another, immediate call will have a different
//    time stamp.  It then returns the populated UserData.
//*****************************************************
UserData genTimePriorityUserData ()
{
    // get the current time
    time_t current_time = time(NULL);
    // convert it to ASCII and point to it
    char* theTime = ctime(&current_time);
    // trim off the \n for prettier printing
    for (int loop = 0; loop < strlen(theTime); loop++)
        if (theTime[loop] == '\n')
            theTime[loop] = 0;
    // fill in time and a priority (1 to MAXPRIO)
    UserData D;
    strcpy (D.time, theTime);
    D.priority = 1 + rand() % MAXPRIO;
    // spin for at least 1 second so that the time field will
    // be different if we are called again immediately
    time_t time_now;
    do
    {
        // get the current time (seconds)
        time_now= time(NULL);
        // spin here if it hasn't changed by at least 1 second
    }
    while ((time_now - current_time) == 0);
    return D;
}

// LowestNumIsHighestPriority is called by the queue
// whenever the queue needs to be updated to maintain priority.
// It performs a comparison in support of the sort used by
// the PriorityQueue implementation
bool LowestNumIsHighestPriority (UserData first, UserData second)
{
    // treat the lower priority number as more important
    if (first.priority <= second.priority)
        return true;
    else
        return false;
}

// HighestNumIsHighestPriority is called by the queue
// whenever the queue needs to be updated to maintain priority.
// It performs a comparison in support of the sort used by
// the PriorityQueue implementation
bool HighestNumIsHighestPriority (UserData first, UserData second)
{
    // treat the lower priority number as more important
    if (first.priority > second.priority)
        return true;
    else
        return false;
}

void Runtest (Queue Q)
{
    // seed the random number generator so it doesn't always
    // start with the same value
    time_t t;
    srand((unsigned) time(&t));
    // start with a queue filled with INITIALENQUEUES items of random priority
    // buildQueue will insure that the timestamps are separated by 1
    // second so we can see that priority queue behavior is done correctly
    buildQueue (Q, INITIALENQUEUES);
    printf ("Total allocations is %d after buildQueue\n", AllocationCount);
    printf ("Starting to dequeue and queue information\n");
    // we will enqueue 1 item after dequeueing at most DEQUESPERENQUEUE
    // items by priority unless the queue is exhausted.
    // if that happens, we are done
    int NumToDequeue = DEQUEUESPERENQUEUE;
    // peek data, print it, then dequeue it and print it
    // until the queue no longer contains any data.
    // data is added along the way to prove the queue is
    // still functional or intact and this new data
    // gets dequeued as well.
    while (empty(Q) != true)
    {
        UserData D = dequeue (Q);
        printf ("  Allocation = %2d, dequeued data: ", AllocationCount);
        printf ("Priority %-3d Time = %s\n", D.priority, D.time);
        // if we have dequeued DEQUEUESPERENQUEUE items, generate
        // and queue another one to show that the queue is intact
        // even if we have begun dequeueing items
        if (--NumToDequeue == 0)
        {
            // generate random data and a time stamp
            UserData D = genTimePriorityUserData();
            // place previously randomly generated
            // data into the queue at the end of
            // the linked list
            enqueue (Q, D);
            printf ("Time = %s queued at priority %d\n", D.time, D.priority);
            // reestablish how many items to dequeue before the next enqueue
            NumToDequeue = DEQUEUESPERENQUEUE;
        }
    }
    // only the allocation of the queue itself remains to be freed
    printf ("Total allocations is %2d after all the dequeue calls\n", AllocationCount);
    return;
}

// main takes no arguments and is responsible for testing three different kinds
// of queues including a queue without priority, a queue where the lowest number
// is the highest priority and a queue where the highest number is the highest
// priority. Each test allocates a queue and its linked list but also
// prints descriptions of steps taken to test the queue as well as
// AllocationCount along the way. This includes the generation of 15
// sequential times, each a second apart, based on user's current time.
// That data is printed and added into the queue. Then that data is removed from
// the queue differently based on what kind of queue is used including first in-first
// out, first in-first out with lowest number as dequeue priority and first in-first
// out with highest number as dequeue priority. Dequeues are printed alongside
// the AllocationCount. Along the way, new data is added to the queue to prove
// the queue is still intact. This data gets removed too so that after all data has
// been removed, the queue is deleted and the next queue is tested.
int main()
{
    printf ("Demonstrating how the queue works WITHOUT a priority application\n");
    // provide NULL so that no priority check will be done
    Queue Q = initQueue(NULL);
    printf ("Total allocations is %d after initQueue\n", AllocationCount);
    Runtest(Q);
    Q = deleteQueue (Q);
    printf ("After deleteQueue, remaining allocations is %d \n", AllocationCount);
    printf ("\n\nDemonstrating how the queue works WITH a priority application\n");
    printf ("The lowest priority number should be the highest priority to dequeue\n");
    // provide a routine to test priorities so that priority will be maintained
    Q = initQueue(LowestNumIsHighestPriority);
    printf ("Total allocations is %d after initQueue\n", AllocationCount);
    Runtest(Q);
    Q = deleteQueue (Q);
    printf ("\n\nDemonstrating how the queue works WITH a priority application\n");
    printf ("The highest priority number should be the highest priority to dequeue\n");
    // provide a routine to test priorities so that priority will be maintained
    Q = initQueue(HighestNumIsHighestPriority);
    printf ("Total allocations is %d after initQueue\n", AllocationCount);
    Runtest(Q);
    Q = deleteQueue (Q);
    printf ("After deleteQueue, remaining allocations is %d \n", AllocationCount);
    return 0;
}
