#include "UserData.h"
#include "SortADTs.h"
#include <stdbool.h>

// function declarations
// swap is use to swap the contents of list locations firstindex and lastindex
static void swap_nodes (UserData list[], int firstindex, int lastindex);
// siftDown is a recursive mechanism that will swap the parent and child contents based
// on the criteria comparator provided by the caller
static void siftDown (UserData list[], int parentIndex, int listLength, Comparer ComesFirst);
// heapify is a utility function that will turn the list provided into a heap based on parent / child
// comparator provided by the caller
static void heapify(UserData list[], int ListLength, Comparer ComesFirst);


void HeapSort (UserData list[], int ListLength,  Comparer ComesFirst)
{
    heapify(list, ListLength, ComesFirst);
    int i;
    for ( i = ListLength - 1; i >= 1; i--) {
        swap_nodes(list, 0, i);
        ListLength = ListLength - 1;
        siftDown (list, 0, ListLength, ComesFirst);
    }
}

void heapify(UserData list[], int ListLength, Comparer ComesFirst)
{   int i;
    for (i = ListLength/2; i >= 0; i--)
        siftDown(list, i, ListLength, ComesFirst);
}

void swap_nodes (UserData list[], int firstindex, int lastindex)
{
    UserData temp = list[firstindex];
    list[firstindex] = list[lastindex];
    list[lastindex] = temp;
    return;
}

void siftDown (UserData list[], int parentIndex, int listLength, Comparer ComesFirst)
{

    // Compute the left and right child indices using a parent index that is assumed
    // zero based
    int leftChildIndex = 2 * (parentIndex + 1) - 1;
    int rightChildIndex = leftChildIndex + 1;

    int swapNodeIndex = parentIndex;

    if (leftChildIndex < listLength && !ComesFirst (list[leftChildIndex],list[parentIndex])) {
        swapNodeIndex = leftChildIndex;
    }

    if (rightChildIndex < listLength && !ComesFirst (list[rightChildIndex],  list[swapNodeIndex])) {
        swapNodeIndex = rightChildIndex;
    }

    if (swapNodeIndex != parentIndex) {
        swap_nodes(list, parentIndex, swapNodeIndex);
        siftDown(list, swapNodeIndex, listLength, ComesFirst);
    }
}

