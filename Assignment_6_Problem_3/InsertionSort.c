// the definition of what the UserData typedef consists of
#include "UserData.h"
// declaration of the sort ADT(s) to be called
#include "SortADTs.h"
// we use bool true and false
#include <stdbool.h>

// InsertionSort is responsible for swapping an observed element to its left
// adjacent spot until it is in its final spot. It takes an array to arrange
// UserData integers for based on a boolean which decides whether to arrange
// low to high or high to low. It also takes an integer in case a data
// element were to be added. It returns nothing.
void InsertionSort (UserData list[], int n,  Comparer ComesFirst)
{
    // h is index of observed UserData
    int h;
    // iterate over every element in the array
    // h starts at 1 so that k can exist left of it, at the first index
    // it increments until all data is iterated over
    for (h = 1; h < n; h++)
    {
        // assign observed element's data to temporary UserData type variable
        UserData key = list[h];
        // k is index left of temporary UserData
        int k = h -1;
        // while both k exists in the array and the less/greater than condition
        // is met, swap observed element with its left adjacent element
        // repeat this until the condition is no longer met and k remains
        // at final spot for observed element to be placed
        while (k >= 0 && ComesFirst (key, list[k]))
        {
            list[k+1] = list[k];
            --k;
        }
        // place observed element at the furthest left index
        list[k+1] = key;
    }
}

