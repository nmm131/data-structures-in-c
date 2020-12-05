#ifndef USERDATA_H_INCLUDED
#define USERDATA_H_INCLUDED

// The UserData struct defines what each node in the LL
// contains.

// User data in each node contains a vertex number (starts at 1)
typedef struct {
    int Vertex;
} UserData, *UserDataPtr;

#endif // USERDATA_H_INCLUDED
