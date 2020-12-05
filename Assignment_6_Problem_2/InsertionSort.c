#include "UserData.h"
#include "SortADTs.h"
#include <stdbool.h>

void InsertionSort (UserData list[], int n,  Comparer ComesFirst)
{
    int h;
    for (h = 1; h < n; h++)
    {
        UserData key = list[h];
        int k = h -1;
        while (k >= 0 && ComesFirst (key, list[k]))
        {
            list[k+1] = list[k];
            --k;
        }
        list[k+1] = key;
    }
}

