//////////////
// demonstration of topological sort
//
// This code will read in a series of activities and constraints
// It will build a graph using the information and then perform a sort
// that will be based on the activity constraints.
//
// As output, it will print the constraints and then the sorted activity
// order
//////////

#include <stdio.h>
#include <stdlib.h>

// theFile is the name of the file to be processed
#define theFile "startofday.in"

// MaxItems is the number of vertices that are allowed in the problem
// An array is used, but it could have been a linked list, in which case
// It would have been dynamically allocated
#define MaxItems 50

// MaxReqTextSize is the maximum number of characters that can be held
// as a description of an activity
#define MaxReqTextSize 80

// White, Grey and Black are simply flags used to designate if a vertex is
// a tree edge (white), a back edge (grey) or is either a forward or cross edge (black)
#define White 'w'
#define Gray 'g'
#define Black 'b'

// A stack is used to push the parent vertices for retrieval
// It will push vertex indices in the order of last to start for the
// topographical result, and then pop them to show the final result
// Stack data simply consists of the index of a vertex in the adjacency array
typedef struct
{
    int nv; //index of a graph vertex
} StackData;

// We need the stack code, unmodified from the Kalicharan provided SW
#include "stack.h"

// An edge structure contains the index of its child and a pointer to
// The next edge.  In the topographical sort, weight is not used, but
// has been allocated for commonality with other graph processes such as
// determining a shortest path between two vertices
typedef struct gEdge
{
    int child, weight; //'child' is the location of the child vertex
    struct gEdge *nextEdge;
} GEdge, *GEdgePtr;

// A vertex contains information that supports traversal.  In the topological
// sort, id (the vertex number), color, and linkage are used.

typedef struct
{
    int id;
    char colour;
    GEdgePtr firstEdge;
} GVertex;

// A graph is simply the number of vertices and an array of vertices.
// Its really an adjacancy list (see the arrary of vertices depicted in Fig 7-9
typedef struct graph
{
    int numV;
    GVertex vertex[MaxItems+1];
} *Graph;

// A reqtype is simply an array to hold the activity text, with an extra
// character allocated for the NULL at the end of the string of characters
typedef struct reqtype
{
    char des [MaxReqTextSize+1];
} ReqDesc;

// declarations of all of the functions called in the topological sort

// printAcrtivityRequirements prints a list of all of the activity constraints in the form
// of X -> Y, where X is the activity requirement that must be satisfied before
// activity Y
void printActivityRequirements(Graph);

// buildTopSortGraph constructs a graph from the file provided and fills
// the requirement description array from the file
void buildTopSortGraph(FILE *, Graph, int numActivityRequirements, ReqDesc[], int numOfReqDescriptions) ;

// topologicalSort examines a graph, producing a result as long as there are no
// cyclic dependencies (A must happen before B which must happen before A).
// It prints its result as a list of the ordered activities, whwre the activity description
// is provided in the table ReqDesc[]
void topologicalSort(Graph, ReqDesc[]);

// dfTopSort recursively builds the resulting topographical sort order
// by tracing vertices from vertexIndex until either a cyclic dependency is
// detected of there are no more vertices to consider.  The vertices are pushed
// on to a stack (a FIFO) so that the stack, at the end of the processing,
// will have the list of the vetices with the start of the sort at the top of
// the stack and the last vertex at the end of the stack
void dfTopSort(Graph, Stack, int vertexIndex);

// newGraph controls the creation of the graph structure.  it will allocate
// space for the graph and, using a file for the data, populate the graph
// structure given the total number of activities
Graph newGraph(int numActivities);

// This helper function will generate a Vertex, filling in its id and setting
// its linkage to NULL
GVertex newGVertex(int vertexIdNum);

// This helper function mallocs an edge in support of the linked list of edges
// for a vertex.  It initializes the child vertex index and sets weight (unused) to 1.
GEdgePtr newGEdge(int childIndex, int weight);

// addEdge adds the edge created through a call to newGEdge and links it to the linked
// list of edges for a vertex.  The vertex to be added to the parent in such a way that
// child vertices are sorted as they are added.
void addEdge(int PVertex, int CVertex, int weight, Graph G);

// newStackData creates an item to be pushed (or popped) from the stack.  The item
// will be initialized to contain the index of a vertex and returned to the caller
StackData newStackData(int vertexIdx);

// the test main will:
//  1. open the data file and read in the number of activities and activity requirements
//  2. create a graph for the number of activities specified
//  3. finalize the graph by reading in all of the activity requirements, filling
//          the graph linked lists for each vertex and capturing the activity
//          descriptions
//  4. log all of the activity requirements
//  5. using the graph, it will do a topological sort.  If the sort works, the
//`         sorter will print out the end result.  If there is a cyclic dependency in
//          the activity requirements, it will log an error and exit
//  6. with the work complete, the file will be closed and we are done
//
//  NOTE: This code does NOT free the allocated linked lists for each vertex.  This should be
//          added!!!
int main()
{
    int numActivities, numActivityRequirements;
    ReqDesc ReqText[MaxItems];

    // Open the file and get the number of activities and the number of activity
    // requirements.  Exit if file open issue or the data is too large for
    // the static allocations
    FILE * in = fopen(theFile, "r");
       if (in == NULL)
    {
        printf ("Unable to open the file.. exiting");
        exit(0);
    }
    fscanf(in, "%d %d", &numActivities, &numActivityRequirements);
    if (numActivities > MaxItems)
    {
        printf("\nToo many items. Only %d allowed.\n", MaxItems);
        exit(1);
    }
    // Create a graph, sized to the number of activities just read in
    Graph G = newGraph(numActivities);
    // complete the graph by reading in and generating linked lists of
    // all of the child vertices for each parent vertex from the file
    buildTopSortGraph(in, G, numActivityRequirements, ReqText, numActivities);
    // traverse the graph and print out the requirements for each vertex
    printActivityRequirements(G);
    // do the topographical sort and log the results.
    topologicalSort(G, ReqText);
    // we are done, so close the file and exit
    fclose(in);
    return 0;
} // end main

// Allocate the graph structure.  Assume the allocation works
Graph newGraph(int numActivities)
{
    // allocate the graph and fill in the user provided number of activities
    Graph p = (Graph) malloc(sizeof(struct graph));
    p -> numV = numActivities;
    return p;
} //end newGraph

// Build the graph and read in the activity descriptions
void buildTopSortGraph(FILE * in, Graph G, int numActivityRequirements, ReqDesc ReqText[], int numActivities)
{
    int preID, postID;
    int h;
    // fill each vertex in the array and set its activity index
    // note that the zero item is not used
    for (h = 1; h <= G -> numV; h++)
    {
        G -> vertex[h] = newGVertex(-1); //create a vertex node
        G -> vertex[h].id = h;           //IDs run from 1 to h
    }
    // now read in the activity constraints.  These become edges in the adjacency list
    // pre and pst ids are the indices of the vertices that represent the activity that
    // must be completed before the post-id activity
    for (h = 1; h <= numActivityRequirements; h++)
    {
        fscanf(in, "%d %d", &preID, &postID); //get an activity requirement
        addEdge(preID, postID, 1, G);  //weights are not important; set to 1
    }
    // now read in the explanation of the activities themselves
    int loop;
    for (loop = 0; loop < numActivities; loop++)
    {
        int req;

        fscanf(in, "%d", &req);
        // in the loop, read a character at a time until the end of line or too
        // many characters have been read
        char ch = getc(in);
        int count = 0;
        while ((ch != '\n') && (ch != EOF))
        {
            // exit if the activity description is too large
            if (count >= MaxReqTextSize)
            {
            printf ("Activity description is longer than the %d allowed characters!! exiting..", MaxReqTextSize);
            exit(0);
            }
            // otherwise, move the character into the description and make sure the string ends with a NULL
            ReqText[req].des[count] = ch;
            count++;
            ReqText[req].des[count] = 0;
            // get the next character (or the indicator that an end of the line has been reached)
            ch = getc(in);
        }
    }
} //end buildTopSortGraph

// Build a vertex, given the vertex id
GVertex newGVertex(int vertexIdNum)
{
    // allocate a temporary copy of a vertex.  Fill it with the vertex id and return it
    // Note that the initial state of a vertex is that it does not have any linkage to its first
    // possible edge, in case there turn out to be no edges for the vertex
    GVertex temp;
    temp.id = vertexIdNum;
    temp.firstEdge = NULL;
    return temp;
}

// Add an edge from the parent (PVertex) to the child (CVertex)
void addEdge(int PVertex, int CVertex, int weight, Graph G)
{
    //create an edge to CVertex with a given weight
    GEdgePtr ep = newGEdge(CVertex, weight); //create edge vertex
    // add it to the list of edges in PVertex
    // it is added so that the list is in order by vertex id
    GEdgePtr prev, curr;
    prev = curr = G -> vertex[PVertex].firstEdge;
    // This will traverse forward in the vertex linked list until
    // a sorted position is determined
    while (curr != NULL && CVertex > G -> vertex[curr -> child].id)
    {
        prev = curr;
        curr = curr -> nextEdge;
    }

    if (prev == curr)
    {
        ep -> nextEdge = G -> vertex[PVertex].firstEdge;
        G -> vertex[PVertex].firstEdge = ep;
    }
    else
    {
        ep -> nextEdge = curr;
        prev -> nextEdge = ep;
    }
} //end addEdge

// allocate a new edge and fill in its id and weight(not used in the sort).
// the edge is returned with its forward pointer NULLed in case it is
// inserted either at the start or end of the list
GEdgePtr newGEdge(int childIndex, int weight)
{
    //return a pointer to a new GEdge node
    GEdgePtr p = (GEdgePtr) malloc(sizeof (GEdge));
    p -> child = childIndex;
    p -> weight = weight;
    p -> nextEdge = NULL;
    return p;
}

// Stack data simply consists of a vertex ID.  This function
// makes a stack item and returns it.
StackData newStackData(int vertexIdx)
{
    StackData temp;
    temp.nv = vertexIdx;
    return temp;
} //end newStackData

// Here is the topological sort, given the graph and the table
// of activity descrioptions.
void topologicalSort(Graph G, ReqDesc R[])
{
    // We'll need a stack, so initialize it
    Stack S = initStack();
    int h;
    // start by settying all vertices to White, indicating they have not
    // been processed
    for (h = 1; h <= G -> numV; h++) G -> vertex[h].colour = White;
    // Starting at the first vertex index, execute a sort that will
    // traverse from this index, finding / processing those vertices that
    // must be done before the activity (vertex).
    // dfTopSort will print out the activities in their sorted order
    for (h = 1; h <= G -> numV; h++)
        if (G -> vertex[h].colour == White) dfTopSort(G, S, h);
    // done!.  Print out the list of activities
    printf("\nTopological sort of activities is: \n");
    h = 1;
    while (!empty(S))
    {
        int idx = G -> vertex[pop(S).nv].id;
        printf ("    %2d.%s (Activity %d)\n", h, R[idx].des, idx);
        h++;
    }
    printf("\n");
} //end topologicalSort

// dfTopSort is a recursive routine that will traverse vertices starting with
// vertex s.
void dfTopSort(Graph G, Stack S, int s)
{
    // our vertex is now being analyzed, so its colour goes from White to Gray
    G -> vertex[s].colour = Gray;
    GEdgePtr edge = G -> vertex[s].firstEdge;
    // traverse its outgoing edges
    while (edge != NULL)
    {
        // we should NOT find a forward edge that is being analyzed.  If we do,
        // it indicates that the edges have a circular dependency.  If that happens
        // then there is no solution an we log the issue and exit
        if (G -> vertex[edge -> child].colour == Gray)
        {
            printf ("Cyclic activity dependency detected.  Unable to sort\n");
            printf ("Activities involve activity numbers %d and %d.. exiting\n", s, G->vertex[edge->child].id);
            exit(1);
        }
        // if the child is colored black, it has been analyzed, so skip it
        // otherwise, recall dfTopSort to continue the traversal
        if (G -> vertex[edge -> child].colour == White)
            dfTopSort(G, S, edge -> child);
        // advance th edge to the next one in Vertex[s] list
        edge = edge -> nextEdge;
    }
    // we have finished processing edges and are at the lowest part of the traversal
    // push the id on the stack so that when we pop the stack it will be in the order
    // first activity down to last activity
    //
    // mark the vertex finished
    G -> vertex[s].colour = Black;
    push(S, newStackData(s));
} //end dfTopSort

// This support routine simply prints the list of activity descriptions
void printActivityRequirements(Graph G)
{
    int h;
    printf("The Activity Requirements are: \n\n");
    for (h = 1; h <= G -> numV; h++)
    {
        int preID = G -> vertex[h].id;
        GEdgePtr p = G -> vertex[h].firstEdge;
        if (p == NULL) continue; //no requirement where this item comes first
        while (p != NULL)
        {
            printf("%d -> %d", preID, G -> vertex[p -> child].id);
            if (p -> nextEdge != NULL) printf(", "); //print comma except after last
            p = p -> nextEdge;
        }
        printf("\n");
    }
} //end printActivityRequirements


