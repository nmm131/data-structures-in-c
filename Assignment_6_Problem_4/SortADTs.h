#ifndef SORTADTS_H_INCLUDED
#define SORTADTS_H_INCLUDED

#include "UserData.h"
#include <stdbool.h>

// Comparer is a typedef that gives us a shorthand way of expressing the
// comparison function that will be called by these sort functions.
// it says that Comparer is a function that receives 2 UserData and
// returns a bool.  The intent is to compare "first" to "second"
// and return a bool.
//      If the comparer is supposed to support a low to high sort,
//          first < second returns true.
//      If the comparer is supposed to support a high to low sort,
//          first > second returns true.
// NEVER code a <= or >= on the comparison functions used for the
// sort functions!!
//
typedef  bool Comparer (UserData first, UserData second) ;

// InsertionSort is a function for sorting an array by continuously swapping an element
// with the adjacent element on its left if it is greater/less than that element. It
// decides whether to sort by increasing/decreasing from a given boolean function which
// decides if two elements are greater/less than one another. InsertionSort is also given
// the array of UserData integers to sort and the number of elements it contains, so that
// the loop knows when to stop sorting.
void InsertionSort (UserData list[], int ListSize,   Comparer);

// SelectionSort is a function for sorting an array by finding the next lowest/greatest
// element and swapping it with the front element. This repeats itself, each time ignoring
// the previously placed elements at the front. It decides whether to sort by increasing/decreasing
// from a given boolean function which decides if two elements are greater/less than one another.
// SelectionSort is also given the array of UserData integers to sort and the number of elements it
// contains, so that the loop knows when to stop sorting.
void SelectionSort (UserData list[], int ListSize,   Comparer);

// HeapSort is a function for sorting an array after arranging it in a heap (binary tree). It starts
// with the last non-leaf and swaps its value with its child's value if it is greater/less than that
// element. This repeats right to left and up the tree until a maximum/minimum remains as the root.
// Then the root is moved to the last element and the heap is reformed except for the last item.
// This repeats until the tree is sorted. It decides whether to sort by increasing/decreasing from
// a given boolean function which decides if two elements are greater/less than one another and if
// the heap should be a max-heap or min-heap. HeapSort is also given the array of UserData integers
// to sort and the number of elements it contains, so that the loop knows when to stop sorting.
void HeapSort      (UserData list[], int ListSize,   Comparer);

// MergeSort is a function for sorting an array by splitting an array in two halves. Then each half
// is recursively split in half until the array size becomes just 1 element. Then two arrays are
// merged in sorted order, until all separated elements have been merged back into one full-sized
// array. It decides whether to sort by increasing/decreasing from a given boolean function which
// decides if two elements are greater/less than one another. MergeSort is also given the array of
// UserData integers to sort and the number of elements it contains, so that the loop knows when
// to stop sorting.
void MergeSort     (UserData list[], int ListSize,   Comparer);

// QuickSort is a function for sorting an array by taking a pivot point and moving elements greater
// to one side while moving elements less than to the other. Then a recursive sort of the left and
// right sides will leave the entire array sorted. It decides whether to sort by increasing/decreasing
// from a given boolean function which decides if two elements are greater/less than one another.
// QuickSort is also given the array of UserData integers to sort and the number of elements it contains,
// so that the loop knows when to stop sorting.
void QuickSort     (UserData list[], int ListSize,   Comparer);

// ShellSort is a function for sorting an array by comparing two elements an interval apart. They get
// swapped if necessary, then the algorithm moves onto the next adjacent elements until all elements
// have been passed over. Then the interval is set to 1 and each element gets swapped with the adjacent
// element if it is greater/less than that element until it is in its final, sorted position. ShellSort
// is also given the array of UserData integers to sort and the number of elements it contains, so that
// the loop knows when to stop sorting.
void ShellSort     (UserData list[], int ListSize,   Comparer);

#endif // SORTADTS_H_INCLUDED
