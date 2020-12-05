#ifndef USERDATA_H_INCLUDED
#define USERDATA_H_INCLUDED

// UserData struct contains two char array elements
// called firstName and lastName to allow for a student's name to be set
// to a maximum number of characters (20) and
// a NULL (zero byte) at the end
// it also contains a single chararacter element that holds a degree
// and a float that holds a GPA
typedef struct {
    char firstName[21];
    char lastName[21];
    char degree;
    float GPA;
    } UserData;

#endif // USERDATA_H_INCLUDED
