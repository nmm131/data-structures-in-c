// the definition of what the UserData typedef consists of
#include "UserData.h"
// declaration of the sort ADT(s) to be called
#include "SortADTs.h"
// we use bool true and false
#include <stdbool.h>

// Swap is responsible for switching the first index of the unsorted
// part of the array with the lowest/greatest value found towards the
// end of the array (also unsorted). It takes an array to swap data
// for and the indices of the two elements to switch data for.
// It returns nothing.
static void swap (UserData list[], int firstindex, int lastindex);
// getChoice is responsible for finding the lowest/greatest value
// in the unsorted part of the array. It compares all data
// in the unsorted part of the array in order to return the found
// lowest/greatest integer. It takes the list to iterate through,
// over two given indices which determine the unsorted part of the
// array. It compares all data values using a boolean function to
// dictate whether to compare low to high or high to low.
static int getChoice (UserData List[], int startindex, int lastIndex, Comparer ComesFirst);

// SelectionSort will rearrange elements in an array by finding the
// next lowest/greatest element and swaps it with the front element.
// This repeats, each time shrinking the unsorted part of the array.
// It takes an array of UserData integer elements to sort, the array's
// number of elements contained and a boolean function to determine
// how to arrange data, either from low to high or high to low.
// It returns nothing.
void SelectionSort (UserData list[], int ListLength,  Comparer ComesFirst)
{
    // array's index counter variable
    int index;
    // start at the first element in the array
    // iterating over every element in the array
    for (index = 0; index < ListLength-1; index++)
    {
        // call getChoice to find lowest/greatest value in unsorted
        // part of the array and assign it to a placeholder variable.
        int indexofchoice = getChoice(list, index, ListLength-1, ComesFirst);
        // swap the lowest/greatest value (the placeholder variable)
        // with the first index of the unsorted part of the array, essentially
        // adding it to the sorted part of the array
        swap (list, index, indexofchoice);
    }
}

// Swap will replace one element's data with another element's
// data, given the array and two indices to do so. Swapping
// is given unsorted parts of the array and places the lowest/greatest
// into a new sorted part of the array.
void swap (UserData list[], int firstindex, int lastindex)
{
    // assign first index of unsorted array value to a placeholder
    UserData temp = list[firstindex];
    // assign lowest/greatest value to first index of unsorted
    // array
    list[firstindex] = list[lastindex];
    // swap lowest/greatest element that was just assigned
    // to first index of unsorted array with the placeholder value
    list[lastindex] = temp;
    return;
}

// getChoice will determine if two elements are less than or greater than
// one another. If so, it will return true, otherwise return false. It
// requires the array and two indices in order to iterate through the array, plus
// the boolean function to compare based on low to high or high to low.
int getChoice (UserData list[], int startindex, int lastindex, Comparer ComesFirst)
{
    // placeholder variable for index of starting
    // position
    int indexofchoice = startindex;
    int loop;
    // compare index's value with rightmost remaining indices to determine
    // if its value is less/greater than the other
    for (loop = startindex+1; loop <= lastindex; loop++)
    {
        // if the element to its right is less/greater than its left,
        // set that lower/greater value to a placeholder variable
        // and get ready to return that value
        if (ComesFirst(list[loop], list[indexofchoice]) == true) indexofchoice = loop;
    }
    // return placeholder variable to return lowest/greatest element's index
    return indexofchoice;
}

