#include <stdio.h>
#include <stdlib.h>

//timeStruct is a struct type that has 2 fields
typedef struct timeStruct {
    int hours;
    int minutes;
} timeStructType;

//function to get difference of time in minutes
int TimeDifference(timeStructType theStart, timeStructType theEnd) {
    //get theStart and theEnd time length in minutes
    int theStartInMins = (theStart.hours * 60 + theStart.minutes);
    int theEndInMins = (theEnd.hours * 60 + theEnd.minutes);

    //initialize timeDifference variable to be returned
    int timeDifference;

    //select which version of timeDifference to use
    if (theEndInMins < theStartInMins) {
            timeDifference = (theEndInMins - theStartInMins + 1440);
    } else {
            timeDifference = (theEndInMins - theStartInMins);
    }
    //return timeDifference in minutes
    return timeDifference;
    }

int main()
{
    //make instances of timeStruct using the typedef
    timeStructType theStart;
    timeStructType theEnd;

    //fill its fields
    theStart.hours = 11;
    theStart.minutes = 52;
    theEnd.hours = 14;
    theEnd.minutes = 43;

    //print contents of theStart and theEnd
    printf("theStart is HH:%d MM:%d\n", theStart.hours, theStart.minutes);
    printf("theEnd is HH:%d MM:%d\n\n", theEnd.hours, theEnd.minutes);

    //call TimeDifference (theStart, theEnd). On return, print out the number of minutes
    printf("Time from theStart to theEnd: %d minutes\n", TimeDifference(theStart, theEnd));

    //call TimeDifference (theEnd, theStart). On return, print out the number of minutes
    printf("Time from theEnd to theStart: %d minutes\n", TimeDifference(theEnd, theStart));
}
