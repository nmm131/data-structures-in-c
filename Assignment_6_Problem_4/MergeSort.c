#include "UserData.h"
#include "SortADTs.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static void merge(UserData A[], int lo, int mid, int hi, UserData T[], Comparer ComesFirst);
static void mergeSort(UserData A[], int lo, int hi, UserData T[], Comparer ComesFirst);
static void merge(UserData A[], int lo, int mid, int hi, UserData T[], Comparer ComesFirst);

void MergeSort (UserData list[], int ListSize, Comparer ComesFirst)
{
    UserData *T = (UserData *) malloc( sizeof (UserData) * ListSize);
    if (T == NULL)
    {
        printf ("Unable to allocate sufficient space for merge copy.. exiting\n");
        exit (0);
    }
    mergeSort (list, 0, ListSize-1, T, ComesFirst);
    free (T);
}

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

void merge(UserData A[], int lo, int mid, int hi, UserData T[], Comparer ComesFirst)
{
    int i = lo;
    int j = mid + 1;
    int k = lo;
    while (i <= mid || j <= hi)
    {
        if (i > mid) T[k++] = A[j++];          //A[lo..mid]  completely processed
        else if (j > hi) T[k++] = A[i++];      //A[mid+1..hi]  completely processed
        else if (ComesFirst(A[i], A[j])) T[k++] = A[i++]; //neither part completed
        else T[k++] = A[j++];
    }
    for (i = lo; i <= hi; i++) A[i] = T[i];   //copy merged elements from T to A
} //end merge


