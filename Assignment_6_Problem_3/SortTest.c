
// This problem demonstrates how a sort ABT can be called to
// sort the caller's data in whatever order the caller wants
//
// To use a sort ADT, the caller provides the ADT of the underlying
// data and the comparison routine to be used when the sort ADT wants
// to determine a sort order.

// Demonstration of all 6 sorts will be done.  Each one will show
// the starting data and the sort results.  In this demonstration,
// integers will be sorted.

// we use printf
#include <stdio.h>
// we use rand to generate random numbers
#include <stdlib.h>
// we use bool true and false
#include <stdbool.h>
// the definition of what the UserData typedef consists of
#include "UserData.h"
// declaration of the sort ADT(s) to be called
#include "SortADTs.h"

/////////////// local function declarations follow ///////////////////

// ProvideIntegerData is the routine called to fill the data array with test
// data.  It will fill up to MaxListSize UserData items with random integers and return
//      the actual number filled in
//   list is the array to fill
//   MaxListSize is the number of items that will fit in the table
static int  ProvideIntegerData (UserData list[], int MaxListSize);

// PrintArray will print out a message and the data in the array provided
//      msg is the character array containing a message to log
//      D is the array with the data to print
//      size is the number of items in the array
static void PrintArray         (char* msg, UserData D[], int size);

// LowToHigh is callable by a sort ADT, returning true if P1.value < P2.value, otherwise false
static bool  LowToHigh          (UserData P1, UserData P2);

// HighToLow is callable by a sort ADT, returning true if P1.value > P2.value, otherwise false
static bool  HighToLow          (UserData P1, UserData P2);

// TheSortFunction typedef gives us a shorthand way of expressing a
// sort function to call.  Such a function will need to provide the list to sort,
// the list size and a comparison routine to support the sort
typedef  void (*TheSortFunction) (UserData list[], int ListSize, Comparer ComesFirst);

// Runtest will print out the name of a test and the data, both unsorted and sorted.
// It will call whatever sort routine is provided and pass the comparison routine
// to be used to the sort ADT
//      nameofSort is a char array containing the name of the sort being done
//      masterArray is an array containing the unsorted data
//      scratchArray is an array that will be filled with the unsorted data and
//          changed to become sorted by the called sort routine
//      arraySize is the number of items to be sorted
//      TheSort is the function pointer to the sort function being executed
//      SortOrder is the comparison function that the sort routine will call
void RunTest (char*             nameOfSort,
              UserData          masterArray[],
              UserData          scratchArray[],
              int               arraySize,
              TheSortFunction   TheSort,
              Comparer          SortOrder );

/////////////// local function definitions follow ///////////////////

// ProvideIntegerData is a function the user writes that fills the List
// with data that can be used if the UserData is int.  The user is responsible
// for filling the list with data, up to the MaxListSize that has been
// allocated by performTest and returning the actual number of items
// filled in.
// For this demo, I chose to use random numbers by calling a system function
//   named getRand that receives a lower and upper bound for a number,
//   returning a random number in that range
int ProvideIntegerData (UserData list[], int MaxListSize)
{
    // fill the memory with random numbers between -100 and 100
    int h;
    int NewListSize;
    // we will use the full list size for this test, inserting random
    // numbers into the list and returning the actual list size equal to
    // the number requested.  the numbers are between -100 and 100.
    //
    // if the data were, for instance, coming from a file, the number
    // of data items read from the file would be returned.
    for (h=0; h < MaxListSize; list[h++].value = (rand() % (int) 201) -100);
    NewListSize = MaxListSize;
    return NewListSize;
}

// <<<<<<<< PrintArray is a utility that will print out a message and array content
// <<<<<<<< you must modify this to suit your printing needs and describe it
// <<<<<<<< accordingly
void PrintArray (char* msg, UserData D[], int size)
{
    printf ("%s", msg);
    for (int i = 0; i < size; i++)
        printf ("%d ", D[i].value);
    printf ("\n");
}

// RunTest is a utility that does the following:
//  1. It copies the master data provided into a scratch array
//  2. It prints out the data to be sorted by calling PrintArray
//  3. It calls the sort routine through the function pointer provided,
//     passing the function pointer of the comparison function to be
//     used by the sort routine
//  4. It prints out the sorted data
//
// Inputs:
//  nameOfSort is a char string that contains the test being done
//  masterArray is an array of the test data to use
//  scratchArray is an array of the same size that data will be copied into
//      and sorted
//  arraySize is the number of items in the masterArray to be sorted
//  TheSortToRun is a function pointer to the sort routine that will be called
//      whenever the sort routine wants to compare one item to another
//  SortOrder is a function pointer to the comparison function that will be called
//

void RunTest (char*             nameOfSort,
              UserData          masterArray[],
              UserData          scratchArray[],
              int               arraySize,
              TheSortFunction   TheSortToRun,
              Comparer          SortOrder )
{
    // copy the master data into the scratch area to be used by the sort
    for (int i=0; i < arraySize; i++)
        scratchArray[i] = masterArray[i];
    // print out the original data
    printf ("%s test follows:\n", nameOfSort);
    PrintArray(("   Array initial contents are:"), scratchArray, arraySize);
    // call the requested sort ADT, giving it the function to use for comparisons
    TheSortToRun (scratchArray, arraySize, SortOrder);
    // print out the sort results
    PrintArray(("   Sorted array contents are: "), scratchArray, arraySize);
    return;
}

// <<<<< The callable sorts need to have a comparator provided
// <<<<< The comparator will need to answer the question "is P1 < P2"
// <<<<< or "is P1 > P2"
// <<<<< DO NOT CODE A <= or >= !!!
// <<<<< Don't forget, P1 and P2 are UserData sensitive, so if you have
// <<<<< a UserData that is a struct, you have to compare a member in the
// <<<<< struct

bool LowToHigh (UserData P1, UserData P2)
{
    return (P1.value < P2.value);
}

bool HighToLow (UserData P1, UserData P2)
{
    return (P1.value > P2.value);
}

// Here is a test main that demonstrates direct sort calls to all 6 of
// the sorts we are studying for a UserData
//
// To just run a sort, you need:
//   - an array of your UserData, filled in with your data
//   - a scratch array of the same size that the sort will use
//   - its size
//   - the sort routine
//   - the comparison function to be called by the sort routine
// Just call RunTest to run the test for you!
int main()
{
    // allocate space for the test data and a scratch array to be used when sorting
    UserData masterArray [10], scratchArray [10];
    // get the size of the array to sort
    int TestArrayMaxSize;
    printf ("Enter the maximum number of items to process (1-10) :");
    int result = scanf ("%d", &TestArrayMaxSize);
    // abort if we don't have a valid size
    if (( result != 1) || (TestArrayMaxSize < 1) || (TestArrayMaxSize > 10))
    {
        printf ("Bad maximum number of items to process... exiting\n");
        exit(1);
    }

    // fill the masterArray with test data
    int numTestItems = ProvideIntegerData(masterArray, TestArrayMaxSize);
    // run the tests
    printf ("Sort tests follow..\n");
    printf ("==================\n");
    RunTest ("Insertion low to high",       masterArray, scratchArray, numTestItems, InsertionSort, LowToHigh);
    RunTest ("Insertion high to low",       masterArray, scratchArray, numTestItems, InsertionSort, HighToLow);
    printf ("==================\n");
    RunTest ("SelectionSort low to high",   masterArray, scratchArray, numTestItems, SelectionSort, LowToHigh);
    RunTest ("SelectionSort high to low",   masterArray, scratchArray, numTestItems, SelectionSort, HighToLow);
    printf ("==================\n");
    RunTest ("HeapSort low to high",        masterArray, scratchArray, numTestItems, HeapSort, LowToHigh);
    RunTest ("HeapSort high to low",        masterArray, scratchArray, numTestItems, HeapSort, HighToLow);
    printf ("==================\n");
    RunTest ("QuickSort low to high",       masterArray, scratchArray, numTestItems, QuickSort, LowToHigh);
    RunTest ("QuickSort high to low",       masterArray, scratchArray, numTestItems, QuickSort, HighToLow);
    printf ("==================\n");
    RunTest ("MergeSort low to high",       masterArray, scratchArray, numTestItems, MergeSort, LowToHigh);
    RunTest ("MergeSort high to low",       masterArray, scratchArray, numTestItems, MergeSort, HighToLow);
    printf ("==================\n");
    RunTest ("ShellSort low to high",       masterArray, scratchArray, numTestItems, ShellSort, LowToHigh);
    RunTest ("ShellSort high to low",       masterArray, scratchArray, numTestItems, ShellSort, HighToLow);
    printf ("==================\n");
    return (0);
} //end main

