// the definition of what the UserData typedef consists of
#include "UserData.h"
// declaration of the sort ADT(s) to be called
#include "SortADTs.h"
// we use bool true and false
#include <stdbool.h>

// hsort is responsible for iterating through a given array in order to swap values
// based on the given boolean condition, either low to high or high to low. It is given
// the interval, or spanSize, from ShellSort function in order to properly compare
// two different values an interval apart.
// It returns nothing.
static void hsort(UserData list[], int ListSize, int spanSize, Comparer ComesFirst) ;

// ShellSort is responsible for swapping two elements an interval apart if
// the first is lower/greater than the other. It calls hsort to do the swapping
// and it creates the interval, or span size based on the given array. It also
// requires the number of elements in the array and a boolean function
// to determine if it is to sort values low to high or high to low.
// It returns nothing.
void ShellSort (UserData list[], int ListSize, Comparer ComesFirst)
{
    // start by determining the sequence span
    // the Knuth method (span = span*3 + 1 until span > ListSize) will be used
    int span_size = 0;
    int prev_span_size = 0;
    // find the highest span number
    while (span_size < ListSize) {
        // keep track of the highest span before we hit ListSize
        prev_span_size = span_size;
        span_size = 3 * span_size +1;
    }
    // The initial start span is the highest span for the ListSize
    span_size = prev_span_size;
    // execute the shell sorting using the span
    // after each shell sort, update the span and exit only after
    // the span has gone below 1
    while (span_size > 0) {
        hsort (list, ListSize, span_size, ComesFirst);
        // This update is the Knuth method that reduces the span number based on the
        // previous Knuth number used
        span_size = (span_size-1) / 3;
    }
} //end ShellSort

// hsort will swap values an interval apart given an array, an interval between elements,
// and a boolean function to determine how to sort, i.e. low to high or high to low.
// It determines the element indices an interval apart
void hsort(UserData list[], int ListSize, int spanSize, Comparer ComesFirst)
{
    int k;
    for (k = spanSize; k < ListSize; k++) {
        // determine the second element's index
        // an interval apart to compare with the
        // first element
        int j = k - spanSize;
        // set first's value to a placeholder
        UserData key = list[k];
        // iterate over the array until the interval becomes 1
        // this loops as long as the second element exists
        // and the boolean condition is met, i.e. first is
        // lower/greater than the second
        while (j >= 0 && ComesFirst (key, list[j])) {
            // swap elements the desired interval apart
            list[j + spanSize] = list[j];
            j = j - spanSize;
        }
        // place lowest/greatest value in its final spot
        list[j + spanSize] = key;
    }
} //end hsort

