#include "UserData.h"
#include "SortADTs.h"
#include <stdbool.h>

static void swap (UserData list[], int firstindex, int lastindex);
static int getChoice (UserData List[], int startindex, int lastIndex, Comparer ComesFirst);

void SelectionSort (UserData list[], int ListLength,  Comparer ComesFirst)
{
    int index;
    for (index = 0; index < ListLength-1; index++)
    {
        int indexofchoice = getChoice(list, index, ListLength-1, ComesFirst);
        swap (list, index, indexofchoice);
    }
}

void swap (UserData list[], int firstindex, int lastindex)
{
    UserData temp = list[firstindex];
    list[firstindex] = list[lastindex];
    list[lastindex] = temp;
    return;
}

int getChoice (UserData list[], int startindex, int lastindex, Comparer ComesFirst)
{
    int indexofchoice = startindex;
    int loop;
    for (loop = startindex+1; loop <= lastindex; loop++)
    {
        if (ComesFirst(list[loop], list[indexofchoice]) == true) indexofchoice = loop;
    }
    return indexofchoice;
}

