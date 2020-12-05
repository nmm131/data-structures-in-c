#ifndef USERDATA_H_INCLUDED
#define USERDATA_H_INCLUDED

// The UserData struct defines what each node in the LL
// contains.
//

// User data in each node contains an integer and char array
typedef struct {
    int taskNumber;
    char taskName[80];
} UserData, *UserDataPtr;


#endif // USERDATA_H_INCLUDED
