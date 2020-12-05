
// This problem demonstrates how a sort ABT can be called to
// sort the caller's data in whatever order the caller wants
//
// To use a sort ADT, the caller provides the ADT of the underlying
// data and the comparison routine to be used when the sort ADT wants
// to determine a sort order.

// Demonstration of all 6 sorts will be done.  Each one will show
// the starting data and the sort results.  In this demonstration,
// first names, last names, degrees and GPAs will be sorted.

// we use printf
#include <stdio.h>
// we use rand to generate random numbers
#include <stdlib.h>
// we use bool true and false
#include <stdbool.h>
// we use strcpy from string.h
#include <string.h>
// we use assert from assert.h
#include <assert.h>
// the definition of what the UserData typedef consists of
#include "UserData.h"
// declaration of the sort ADT(s) to be called
#include "SortADTs.h"

/////////////// local function declarations follow ///////////////////

// ProvideStudentData is the routine called to fill the data array with test
// data.  It will fill up to a user defined number of UserData items
// with char, char array and float data which is read from a file
// it returns
//      the actual number filled in
//   list is the array to fill
//   MaxListSize is the number of items that will fit in the table
static int  ProvideStudentData (UserData list[], int MaxListSize);

// PrintArray will print out a message and the data in the array provided
//      msg is the character array containing a message to log
//      D is the array with the data to print
//      size is the number of items in the array
static void PrintArray         (char* msg, UserData D[], int size);

// LowerFirstName is callable by a sort ADT, returning true if P1.firstName < P2.firstName, otherwise false
static bool  LowerFirstName          (UserData P1, UserData P2);

// HigherLastName is callable by a sort ADT, returning true if P1.lastName > P2.lastName, otherwise false
static bool  HigherLastName          (UserData P1, UserData P2);

// LowestDegreeFirst is callable by a sort ADT, returning true if P1.degree < P2.degree, otherwise false
static bool  LowestDegreeFirst          (UserData P1, UserData P2);

// HighestDegreeFirst is callable by a sort ADT, returning true if P1.degree > P2.degree, otherwise false
static bool  HighestDegreeFirst        (UserData P1, UserData P2);

// LowestGPAFirst is callable by a sort ADT, returning true if P1.GPA < P2.GPA, otherwise false
static bool  LowestGPAFirst          (UserData P1, UserData P2);

// HighestGPAFirst is callable by a sort ADT, returning true if P1.GPA > P2.GPA, otherwise false
static bool  HighestGPAFirst        (UserData P1, UserData P2);

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

// ProvideStudentData is a function the user writes that fills the List
// with data that can be used if the UserData is char, char array and float.
// The user is responsible for filling the list with data, up to the MaxListSize
//  that has been allocated by performTest and returning the actual number of items
// filled in.
int ProvideStudentData (UserData list[], int MaxListSize)
{

    // initialize variables for reading data from a file
    int count;
    int i = 0;
    int NewListSize;
    char fileName[] = "StudentData.txt";
    char firstNameTemp[21];
    char lastNameTemp[21];
    char degreeTemp;
    float GPATemp;

    // attempt to open the file
    FILE * inputFile = fopen(fileName, "r");
    // exit if the file did not open
    assert(inputFile != NULL);
    // the file opened, so proceed and process its contents

    // read records from the file, printing out each record
    do {
        //try to read in a record
         count = fscanf (inputFile, "%s%s %c%f", firstNameTemp, lastNameTemp, &degreeTemp, &GPATemp);
         //write data to array if enough records are read
         if (count == 4) {
                //create data
                UserData D;
                //set that data's firstName, lastName, degree and GPA, strcpy is used to write to an array
                strcpy(D.firstName, firstNameTemp);
                strcpy(D.lastName, lastNameTemp);
                D.degree = degreeTemp;
                D.GPA = GPATemp;
                //add data to the array
                list[i] = D;
         }
         //if 4 records are not read, exit the loop
         if (count != 4) {
                 break;
         }
         //otherwise increment a counter value and continue the do while loop
         i++;
    } while ((count == 4) && (i < MaxListSize));
    //stop reading the file
    fclose (inputFile);

    // return the number of data items read from the file.
    NewListSize = i;
    return NewListSize;
}

// PrintArray takes a message to display to the user which describes the
// name of the test to be run. It takes an array of UserData that includes
// char, char arrays and float values
// PrintArray is responsible for displaying each element's
// first and last name, degree and GPA. It is given the array's number
// of elements so that it knows when to stop displaying data and
// it returns nothing.
void PrintArray (char* msg, UserData D[], int size)
{
    printf ("%s", msg);
    for (int i = 0; i < size; i++)
        printf ("\n\t%s %s %c %.2f", D[i].firstName, D[i].lastName, D[i].degree, D[i].GPA);
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
    PrintArray(("\n   Sorted array contents are: "), scratchArray, arraySize);
    return;
}

// LowerFirstName is a function to check that one UserData's
// firstName member is earlier in the alphabet than another UserData's
// firstName. It returns true if the first is sooner in the alphabet
// and false if it is further along in the alphabet.
bool LowerFirstName (UserData P1, UserData P2)
{
    //strcmp is used to compare strings
    // < 0 and the first comes earlier in the alphabet
    // = 0 and they are the same
    // > 0 and the first comes further along in the alphabet
    return (strcmp(P1.firstName, P2.firstName) < 0);
}

// HigherLastName is a function to check that one UserData's
// firstName member is later in the alphabet than another UserData's
// firstName. It returns true if the first is further along in
// the alphabet and false if it comes sooner in the alphabet.
bool HigherLastName (UserData P1, UserData P2)
{
    //strcmp is used to compare strings
    // < 0 and the first comes earlier in the alphabet
    // = 0 and they are the same
    // > 0 and the first comes further along in the alphabet
    return (strcmp(P1.lastName, P2.lastName) > 0);
}

// LowestDegreeFirst is a function to check that one UserData's
// degree member is less than another UserData's degree. It returns
// true if the first is less than the second and false if it
// is greater than the second.
bool LowestDegreeFirst (UserData P1, UserData P2)
{
    // Degree values in Lowest to Highest Order
    char expectedChar[4] = {'?', 'U', 'M', 'D'};
    // temp variables to hold indices of P1 and P2 once
    // they equal an element in expectedChar[] array
    int P1IndexTemp;
    int P2IndexTemp;

    // find the index that P1 Degree equals
    // in expectedChar[] array
    for (int i = 0; i < 4; i++) {
        if (expectedChar[i] == P1.degree)
            P1IndexTemp = i;
    }

    // find the index that P2 Degree equals
    // in expectedChar[] array
    for (int j = 0; j < 4; j++) {
        if (expectedChar[j] == P2.degree)
            P2IndexTemp = j;
    }

    // compare indices since their values in
    // expectedChar[] array are sorted in Lowest
    // to Highest Order
    if (P1IndexTemp < P2IndexTemp) {
        return true;
    } else {
    return false;
    }
}

// HighestDegreeFirst is a function to check that one UserData's
// degree member is greater than another UserData's degree. It returns
// true if the first is greater than the second and false if it
// is less than the second.
bool HighestDegreeFirst (UserData P1, UserData P2)
{
    // Degree values in Lowest to Highest Order
    char expectedChar[4] = {'?', 'U', 'M', 'D'};
    // temp variables to hold indices of P1 and P2 once
    // they equal an element in expectedChar[] array
    int P1IndexTemp;
    int P2IndexTemp;

    // find the index that P1 Degree equals
    // in expectedChar[] array
    for (int i = 0; i < 4; i++) {
        if (expectedChar[i] == P1.degree)
            P1IndexTemp = i;
    }

    // find the index that P2 Degree equals
    // in expectedChar[] array
    for (int j = 0; j < 4; j++) {
        if (expectedChar[j] == P2.degree)
            P2IndexTemp = j;
    }

    // compare indices since their values in
    // expectedChar[] array are sorted in Lowest
    // to Highest Order
    if (P1IndexTemp > P2IndexTemp) {
        return true;
    } else {
    return false;
    }
}

// LowestGPAFirst is a function to check that one UserData's
// GPA member is less than another UserData's GPA. It returns
// true if the first is less than the second and false if it
// is greater than the second.
bool LowestGPAFirst (UserData P1, UserData P2)
{
    return (P1.GPA < P2.GPA);
}

// HighestGPAFirst is a function to check that one UserData's
// GPA member is greater than another UserData's GPA. It returns
// true if the first is greater than the second and false if it
// is less than the second.
bool HighestGPAFirst (UserData P1, UserData P2)
{
    return (P1.GPA > P2.GPA);
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
    int numTestItems = ProvideStudentData(masterArray, TestArrayMaxSize);
    // run the tests
    printf ("Sort tests follow:\n");
    printf ("==================\n");
    RunTest ("Insertion Lower First Name first",       masterArray, scratchArray, numTestItems, InsertionSort, LowerFirstName);
    printf ("==================\n");
    RunTest ("SelectionSort Higher Last Name first",   masterArray, scratchArray, numTestItems, SelectionSort, HigherLastName);
    printf ("==================\n");
    RunTest ("HeapSort Highest Degree first",        masterArray, scratchArray, numTestItems, HeapSort, HighestDegreeFirst);
    printf ("==================\n");
    RunTest ("QuickSort Lowest Degree first",       masterArray, scratchArray, numTestItems, QuickSort, LowestDegreeFirst);
    printf ("==================\n");
    RunTest ("MergeSort Highest GPA first",       masterArray, scratchArray, numTestItems, MergeSort, HighestGPAFirst);
    printf ("==================\n");
    RunTest ("ShellSort Lowest GPA first",       masterArray, scratchArray, numTestItems, ShellSort, LowestGPAFirst);
    printf ("==================\n");
    return (0);
} //end main

