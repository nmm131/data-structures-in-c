
// StackTester will demonstrate the init, push, peek, pop and delete
// for a stack.
//      - It builds a stack that holds UserData from a file being read
//      - it peeks at the stack, returning UserData
//      - It pops UserData from the stack, returning UserData
//      - it uses empty() to determine if the stack holds any data that
//          can be popped or peeked
//      - when done, it deletes the stack
// For demonstration purposes, it shows the number of allocations for
// everything it does.

// printf support
#include <stdio.h>
// we use strcpy from string.h
#include <string.h>
// we use assert from assert.h
#include <assert.h>
// stack callable routines
#include "Stack.h"
// UserData definition for making and getting stack data
#include "UserData.h"
// local functions

// PrintStackItem is a local function that we can call to print out a message (msg) and
// a UserData item.  So we can see how many things are allocated as we proceed,
// it will also print out the number of things allocated
static void PrintStackItem (char msg[], UserData D);

// PrintAllocations is a local function that will print out a message (msg) and the
// current global AllocationCount
static void PrintAllocations (char msg[]);

int main(int argc, const char * argv[]) {
    // initialize variables for reading data from a file
    char fileName[] = "StackData.txt";
    int count;
    int i = 0;
    int taskNumberTemp;
    char taskNameTemp[80];

    // Show the allocation count when we start
    PrintAllocations ("On startup");

    // create a stack ans see the effect of on the number of allocations
    Stack S = initStack();
    PrintAllocations ("After initStack called");

    // push the data on the stack, showing the data and allocations

    // attempt to open the file
    FILE * inputFile = fopen(fileName, "r");
    // exit if the file did not open
    assert(inputFile != NULL);
    // the file opened, so proceed and process its contents

    // read records from the file, printing out each record
    do {
        //try to read in a record
         count = fscanf (inputFile, "%d%s", &taskNumberTemp, taskNameTemp);
         //push to and print stack if enough records are read
         if (count == 2) {
                //create data
                UserData D;
                //set that data's taskNumber and taskName, strcpy is used to write to an array
                D.taskNumber = taskNumberTemp;
                strcpy(D.taskName, taskNameTemp);
                //push now set data to the stack
                push (S, D);
                //print the results of the push
                PrintStackItem("push called, data is", D);
         }
         //if 2 records are not read, exit the loop
         if (count != 2) {
                 break;
         }
         //otherwise increment a counter value and continue the do while loop
         i++;
    } while (count == 2);
    //stop reading the file
    fclose (inputFile);

    // pop and print the stack content
    // peek at the data before popping it so we can see what peek yields
    while (!empty(S))
    {
        PrintStackItem ("peek called, data is", peek(S));
        PrintStackItem ("pop  called, data is", pop(S));
    }
    // delete the stack and see the effect on the allocations
    PrintAllocations ("Before deleteStack called");
    S = deleteStack(S);
    PrintAllocations ("After deleteStack called");
    return 0;
}

/*
   PrintStackData prints out the received message and the data in UserData
*/
void PrintStackItem (char msg[], UserData D)
{
    //now the integer to be printed is UserData's taskNumber
    //and UserData's taskName
    printf ("%s %d %s, #allocations is %d\n", msg, D.taskNumber, D.taskName, AllocationCount);
}

/*
   PrintAllocations prints out the received message and the current allocation count
   The allocation count is global AllocationCount
*/
void PrintAllocations (char msg[])
{
    printf ("%s, #allocations is %d\n", msg, AllocationCount);
    return;
}
