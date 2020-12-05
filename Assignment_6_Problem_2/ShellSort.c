#include "UserData.h"
#include "SortADTs.h"
#include <stdbool.h>


static void hsort(UserData list[], int ListSize, int spanSize, Comparer ComesFirst) ;

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

void hsort(UserData list[], int ListSize, int spanSize, Comparer ComesFirst)
{
    int k;
    for (k = spanSize; k < ListSize; k++) {
        int j = k - spanSize;
        UserData key = list[k];
        while (j >= 0 && ComesFirst (key, list[j])) {
            list[j + spanSize] = list[j];
            j = j - spanSize;
        }
        list[j + spanSize] = key;
    }
} //end hsort

