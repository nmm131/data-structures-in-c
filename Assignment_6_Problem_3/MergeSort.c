// the definition of what the UserData typedef consists of
#include "UserData.h"
// declaration of the sort ADT(s) to be called
#include "SortADTs.h"
// we use bool true and false
#include <stdbool.h>
// we use rand to generate random numbers
#include <stdlib.h>
// we use printf
#include <stdio.h>

// merge will combine two arrays into one, in sorted order of low to high or high to low
// based on the given boolean function. It takes two UserData arrays and low and high values of
// those arrays in order to combine them in sorted order. It returns nothing.
static void merge(UserData A[], int lo, int mid, int hi, UserData T[], Comparer ComesFirst);
// mergeSort will sort the array by splitting it in halves, then recursively splitting those
// halves until the arrays consist of 1 element. They get joined together in sorted order
// until the whole array is sorted. It is given two UserData arrays and low and high values
// of the arrays used in conjunction with the boolean function to determine how to rearrange
// data elements when they are being merged back into a single array. It returns nothing.
static void mergeSort(UserData A[], int lo, int hi, UserData T[], Comparer ComesFirst);
// merge will combine two arrays into one, in sorted order of low to high or high to low
// based on the given boolean function. It takes two UserData arrays and low and high values of
// those arrays in order to combine them in sorted order. It returns nothing.
static void merge(UserData A[], int lo, int mid, int hi, UserData T[], Comparer ComesFirst);

// mergeSort is responsible for sorting an array by splitting the array into halves. Then
// each half is recursively split until the arrays consist of just 1 element. Each array
// is then merged in sorted order, until eventually the full-sized array remains. It takes
// two arrays of UserData integer values, two integer values for comparison and a boolean
// function to compare those two integer values based on a low to high or high to low sequence.
// It returns nothing.
void MergeSort (UserData list[], int ListSize, Comparer ComesFirst)
{
    // allocate memory for temporary array to be used while splitting the
    // actual array of unsorted data
    UserData *T = (UserData *) malloc( sizeof (UserData) * ListSize);
    // check if memory has been dynamically allocated
    if (T == NULL)
    {
        // no memory has been allocated, so print an error message
        // and exit the program
        printf ("Unable to allocate sufficient space for merge copy.. exiting\n");
        exit (0);
    }
    // call mergeSort to sort the array by splitting it and
    // merging it together in sorted order based on a boolean
    // condition of low to high or high to low
    mergeSort (list, 0, ListSize-1, T, ComesFirst);
    // release allocated memory of the temporary array
    // because the array will have been sorted and its use
    // is no longer required in memory
    free (T);
}

// mergeSort will sort a given array by splitting it in halves, then recursively splitting those
// halves until the arrays consist of 1 element. They get joined together in sorted order
// until the whole array is sorted. It knows how to insert array elements based on their low and
// high values and the check is done in the boolean function to determine which is less/greater than
// the other.
void mergeSort(UserData A[], int lo, int hi, UserData T[], Comparer ComesFirst)
{
    if (lo < hi)   //list contains at least 2 elements
    {
        int mid = (lo + hi) / 2; //get the mid-point subscript
        mergeSort(A, lo, mid, T, ComesFirst); //sort first half
        mergeSort(A, mid + 1, hi, T, ComesFirst); //sort second half
        merge(A, lo, mid, hi, T, ComesFirst); //merge sorted halves
    }
} //end mergeSort

// merge will take two UserData arrays and those arrays' low, middle and high values.
// it will combine arrays based on low, middle and high values, assuring the boolean
// condition to arrange based on low to high or high to low. It checks that the low
// and high values are on their respective sides of the middle value so assure
// the array is in sorted order.
void merge(UserData A[], int lo, int mid, int hi, UserData T[], Comparer ComesFirst)
{
    // initialize variables for comparing low, middle and high values
    int i = lo;
    int j = mid + 1;
    int k = lo;
    // rearrange elements so that low and high values are moved
    // to their respective sides, left and right of the middle value
    while (i <= mid || j <= hi)
    {
        if (i > mid) T[k++] = A[j++];          //A[lo..mid]  completely processed
        else if (j > hi) T[k++] = A[i++];      //A[mid+1..hi]  completely processed
        else if (ComesFirst(A[i], A[j])) T[k++] = A[i++]; //neither part completed
        else T[k++] = A[j++];
    }
    for (i = lo; i <= hi; i++) A[i] = T[i];   //copy merged elements from T to A
} //end merge


