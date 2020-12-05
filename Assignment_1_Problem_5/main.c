#include <stdio.h>
#include <stdlib.h>

//numStruct is a struct type that has 2 fields
typedef struct numStruct {
    int a;
    int b;
} numStructType;

//switch int values using pointers and return nothing
void Swap(int *I, int *J) {
    //save one pointer int to a temporary int variable
    int temp = *I;
    //set first int to second, then set second int to temp
    *I = *J;
    *J = temp;
}

//switch struct int values using pointers and return nothing
void SwapStructs(numStructType *ptr1, numStructType *ptr2) {
    //save one pointer struct to a temporary struct variable
    numStructType temp = *ptr1;
    //set first struct to second, then set second struct to temp
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

int main()
{
    //initialize variables
    int I = 1;
    int J = -1;
    numStructType ptr1;
    numStructType ptr2;
    //set struct integers
    ptr1 = (numStructType){.a = 10, .b = 20};
    ptr2 = (numStructType){.a = 30, .b = 40};

    //print int values before and after calling Swap
    printf("Before call..I=%d, J=%d\n", I, J);
    Swap(&I, &J);
    printf("After call..I=%d, J=%d\n", I, J);

    //print struct int values before and after calling SwapStructs
    printf("Before SwapStructs..ptr1 contains %d and %d\n", ptr1.a, ptr1.b);
    printf("Before SwapStructs..ptr2 contains %d and %d\n", ptr2.a, ptr2.b);
    SwapStructs(&ptr1, &ptr2);
    printf("After SwapStructs..ptr1 contains %d and %d\n", ptr1.a, ptr1.b);
    printf("After SwapStructs..ptr2 contains %d and %d\n", ptr2.a, ptr2.b);

    return 0;
}
