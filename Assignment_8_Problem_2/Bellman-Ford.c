// Bellman-Ford
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxWordSize 20
#define MaxVertices 50

typedef struct gEdge {
    int child, weight; //'child' is the location of the child vertex
    struct gEdge *nextEdge;
} GEdge, *GEdgePtr;

typedef struct {
    char id[MaxWordSize+1], color;
    int parent, cost;
    GEdgePtr firstEdge;
} GVertex;

typedef struct graph {
    int numV;
    GVertex vertex[MaxVertices+1];
} *Graph;

typedef struct {
    int node_id;
    int weight;
} UserData, *UserDataPtr;


#define Infinity 999999

// test files supported with the code
#define testfile "TravelToBoston.in"


// function prototypes
void buildGraph(FILE * in, Graph G);
void initSingleSource(Graph G, int startRoom);
void printGraph(Graph G);
Graph newGraph(int numVertices);
int BellmanFord (Graph G, int start, int end);
void followPath(Graph, int vertexNum);
void relax (Graph G, int u, int v, int weight);
void printAllCostPaths(Graph G, int start, int end);
void getUserOptions ( Graph G, int numVertices, int *sourceIndex, int *destinationIndex);

int main()
{
    int numVertices;

    Graph G;
    // open the data file and build the graph
    FILE * in = fopen(testfile, "r");
    if (in == NULL) {
        printf ("Unable to open file \"%s\"", testfile);
        exit(0);
    }
    fscanf(in, "%d", &numVertices);
    G = newGraph(numVertices);
    buildGraph(in, G);
    // dump the graph vertex and edge content
    printGraph(G);
    // get the user options
    int sourceIndex, destinationIndex;
    getUserOptions (G, numVertices, &sourceIndex, &destinationIndex);
    printf ("\n\n");
    // run a BellmanFord for a source vertex to either
    // a specific vertex (1 to numVertices) or all vertices (0)
    BellmanFord(G, sourceIndex, destinationIndex);
    // close the file and exit
    fclose(in);
    return 0;
} // end main

void getUserOptions ( Graph G, int numVertices, int *sourceIndex, int *destinationIndex)
{
    while (1) {
        printf ("\nYour choices for a source vertex are: \n");
        for (int i=1; i <= numVertices; i++)
            printf ("\t%3d - %s\n", i, G->vertex[i].id);
        printf ("Enter a number from 1 to %d: ", numVertices);
        int sidx;
        int result = scanf ("%d", &sidx);
        fflush (stdin);
        *sourceIndex = sidx;
        if ( (result == 1) && (sidx >= 1) && (sidx <= numVertices)) {
            while (1) {
                printf ("\nYour choices for a destination vertex are: \n");
                printf ("\t%3d - %s\n", 0, "All vertices");
                for (int i=1; i <= numVertices; i++)
                    printf ("\t%3d - %s\n", i, G->vertex[i].id);
                printf ("Enter a number from 1 to %d: ", numVertices);
                int didx;
                int result = scanf ("%d", &didx);
                fflush (stdin);
                *destinationIndex = didx;
                if ( (result == 1) && (didx >= 0) && (didx <= numVertices)) {
                    break;
                } else printf ("Illegal destination vertex.. reenter...\n");
            }
            break;
        } else printf ("Illegal source vertex.. reenter...\n");
    }
}


void relax (Graph G, int u, int v, int weight)
{
    if ((G->vertex[u].cost + weight < G->vertex[v].cost)  ) {
        G->vertex[v].cost = G->vertex[u].cost + weight;
        G->vertex[v].parent = u;
    }
}


int BellmanFord (Graph G, int start, int end)
{
    int pass;
    initSingleSource(G, start);
    for (pass = 1; pass < G->numV; pass++)
        for (int h = 1; h <= G->numV; h++) {
            {
                if (G->vertex[h].cost != Infinity) {
                    GEdgePtr p = G->vertex[h].firstEdge;
                    while (p != NULL) {
                        relax (G, h, p->child, p->weight);
                        p = p->nextEdge;
                    }
                }
            }
        }
    for (int h = 1; h <= G->numV; h++) {
        GEdgePtr p = G->vertex[h].firstEdge;
        while ( (p != NULL) && (G->vertex[h].cost != Infinity)
                && (G-> vertex[p->child].cost != Infinity) ) {
            if (G->vertex[h].cost + p->weight < G-> vertex[p->child].cost) {
                printf ("\nNo solution.. graph has negative weight for %s\n",
                        G->vertex[h].id);
                // return 1;
            }
            p = p->nextEdge;
        }
    }
    printAllCostPaths(G, start, end);
    return 0;
}

void initSingleSource(Graph G, int startVertex)
{
    int i;
    for (i = 1; i <= G -> numV; i++) {
        G -> vertex[i].cost = Infinity;
        G -> vertex[i].parent = 0;
    }
    G -> vertex[startVertex].cost = 0;
} //end initSingleSource

void printAllCostPaths (Graph G, int start, int end)
{
    for (int i = 1; i <= G->numV; i++) {
        if ( (end == 0) || (end == i) ) {
            if (G-> vertex[i].cost == Infinity) {
                printf ("%s is unreachable from %s\n",G->vertex[i].id, G->vertex[start].id ) ;
            } else {
                printf ("Cost to %s: %2d, Path starting in ", G->vertex[i].id, G->vertex[i].cost);
                followPath(G, i);
                printf ("\n");
            }
        }
    }
}

void followPath(Graph G, int vertexNum)
{
    if (vertexNum != 0) {
        followPath(G, G -> vertex[vertexNum].parent);
        if (G -> vertex[vertexNum].parent != 0) {
            printf(" -> ");
            printf("%s %d\n", G -> vertex[vertexNum].id, G->vertex[vertexNum].cost);
        } else
            printf("%s\n", G -> vertex[vertexNum].id);
    }
} //end followPath



Graph newGraph(int numVertices)
{
    if (numVertices > MaxVertices) {
        printf("\nToo big. Only %d vertices allowed.\n", MaxVertices);
        exit(1);
    }
    Graph p = (Graph) malloc(sizeof(struct graph));
    p -> numV = numVertices;
    return p;
} //end newGraph

void buildGraph(FILE * in, Graph G)
{
    int numEdges, weight;
    GVertex newGVertex(char[]);
    void addEdge(char[], char[], int, Graph);
    char nodeID[MaxWordSize+1], adjID[MaxWordSize+1];
    int h;
    for (h = 1; h <= G -> numV; h++) {
        G -> vertex[h] = newGVertex("");      //create a vertex node
        fscanf(in, "%s", G -> vertex[h].id);   //read the name into id
        G->vertex[h].color = 'W';
    }
    for (h = 1; h <= G -> numV; h++) {
        fscanf(in, "%s %d", nodeID, &numEdges); //parent id and numEdge
        for (int k = 1; k <= numEdges; k++) {
            fscanf(in, "%s %d", adjID, &weight); //get child id and weight
            addEdge(nodeID, adjID, weight, G);
        }
    }
    return;
} //end buildGraph

GVertex newGVertex(char name[])
{
    GVertex temp;
    strcpy(temp.id, name);
    temp.firstEdge = NULL;
    return temp;
}

void addEdge(char X[], char Y[], int weight, Graph G)
{
    GEdgePtr newGEdge(int, int);
    //add an edge X -> Y with a given weight
    int h, k;
    //find X in the list of nodes; its location is h
    for (h = 1; h <= G -> numV; h++) if (strcmp(X, G -> vertex[h].id) == 0) break;

    //find Y in the list of nodes; its location is k
    for (k = 1; k <= G-> numV; k++) if (strcmp(Y, G -> vertex[k].id) == 0) break;

    if (h > G -> numV || k > G -> numV) {
        printf("No such edge: %s -> %s\n", X, Y);
        exit(1);
    }

    GEdgePtr ep = newGEdge(k, weight); //create edge vertex
    // add it to the list of edges, possible empty, from X;
    // it is added so that the list is in order by vertex id
    GEdgePtr prev, curr;
    prev = curr = G -> vertex[h].firstEdge;
    while (curr != NULL && strcmp(Y, G -> vertex[curr -> child].id) > 0) {
        prev = curr;
        curr = curr -> nextEdge;
    }

    if (prev == curr) {
        ep -> nextEdge = G -> vertex[h].firstEdge;
        G -> vertex[h].firstEdge = ep;
    } else {
        ep -> nextEdge = curr;
        prev -> nextEdge = ep;
    }
} //end addEdge

GEdgePtr newGEdge(int c, int w)
{
    //return a pointer to a new GEdge node
    GEdgePtr p = (GEdgePtr) malloc(sizeof (GEdge));
    p -> child = c;
    p -> weight = w;
    p -> nextEdge = NULL;
    return p;
}

void printGraph(Graph G)
{
    int h;
    for (h = 1; h <= G -> numV; h++) {
        printf("%s: ", G -> vertex[h].id);
        GEdgePtr p = G -> vertex[h].firstEdge;
        while (p != NULL) {
            printf("%s %d ", G -> vertex[p -> child].id, p -> weight);
            p = p -> nextEdge;
        }
        printf("\n");
    }
    printf("\n");
} //end printGraph
