#include "UserData.h"
#include "SortADTs.h"
#include <stdbool.h>
#include <stdlib.h>

static int getRand (int lowValue, int HighValue);
static int qpartition(UserData list[], int loIndex, int hiIndex, Comparer ComesFirst);
static void qswap(UserData list[], int firstIndex, int secondIndex);
static void mysort (UserData list[], int loIndex, int hiIndex, Comparer ComesFirst);

void QuickSort (UserData list[], int listLength,  Comparer ComesFirst)
{
    mysort(list, 0, listLength-1, ComesFirst);
}

void mysort (UserData list[], int loIndex, int hiIndex, Comparer ComesFirst)
{
    //sorts list[lo] to list[hi] in ascending order
    if (loIndex < hiIndex)
    {
        int dp = qpartition (list, loIndex, hiIndex, ComesFirst);
        mysort (list, loIndex, dp, ComesFirst);
        mysort (list, dp+1, hiIndex, ComesFirst);
    }
}

int getRand(int lowValue, int highValue)
{
    //returns a random integer from m to n, inclusive
    int offset = rand()/(RAND_MAX + 1.0) * (highValue - lowValue + 1);
    return lowValue + offset;
}


int qpartition(UserData list[], int loIndex, int hiIndex, Comparer ComesFirst)
{
    //choose a random element as the pivot
    qswap(list, loIndex, getRand(loIndex, hiIndex));
    UserData pivot = list[loIndex];
    --loIndex;
    ++hiIndex;
    while (loIndex < hiIndex)
    {
        do --hiIndex;
        while (ComesFirst (pivot, list[hiIndex]));
        do ++loIndex;
        while (ComesFirst (list[loIndex], pivot));

        if (loIndex< hiIndex) qswap(list, loIndex, hiIndex);
    }
    return hiIndex;
}


void qswap(UserData list[], int first, int second)
{
    //swap list[first] and list[second]
    UserData hold = list[first];
    list[first] = list[second];
    list[second] = hold;
}

