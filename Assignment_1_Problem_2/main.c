#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//userDataStruct is a struct type that has 3 fields
typedef struct userDataStruct {
    //array sized to hold 30 characters and a NULL (zero byte) at the end
    char name[31];
    int age;
    int salary;
} userDataStructType;

//function to populate the array
int getData(char fileName[], userDataStructType userData[], int *numItems) {
    // attempt to open the file
    FILE * inputFile = fopen(fileName, "r");
    // exit if the file did not open
    assert(inputFile != NULL);
    // the file opened, so proceed and process its contents

    // read records from the file, printing out each record
    int count;
    int i = 0;

    do {
        // try to read in a record
        count = fscanf (inputFile, "%s%d%d", userData[i].name, &userData[i].age, &userData[i].salary);
        //increment a new numItems value
        i++;
    } while ((count == 3) && (i <= numItems));

        fclose (inputFile);
        //return new numItems value starting at 1
        return i-1;
}

//function to show array data
int showData(userDataStructType userData[], int numItems) {
    printf("\nThere are %d item(s) in the array:\n", numItems);
    for (int i = 0; i < numItems; i++) {
        printf("%s  %d  %d\n", userData[i].name, userData[i].age, userData[i].salary);
    }
    return 0;
}

int main()
{
    //initialize variables used for reading a file
    int numItems;
    char fileName[] = "Problem1_2DataFile.txt";
    //make array of userDataStruct using the typedef, fixed size at 10
    userDataStructType userData[10];

    //prompt user for number of people to get data for
    printf("Give me a number from 1 to 10: ");
    scanf("%d", &numItems);
    //check that number is within range
    if (numItems < 1 || numItems > 10) {
            printf("Number is outside the range of 1 to 10. Exiting Program\n");
            exit(0);
    }

    //populate array data and retrieve number of array items filled
    getData(fileName, userData, &numItems);
    //display contents of the array
    showData(userData, numItems);
}
