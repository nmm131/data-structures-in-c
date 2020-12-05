// Program P5.2 from Kalicharan, reformatted and ready for documentation  and modification
//
// The program demonstrates how to form a BST and display it.  It uses a file containing
// text as the input and the BST is formed from the integers.  Each integer has
// an occurrence frequency, which is incremented whenever the identical integer is
// found in the file.
//
// After creating the BST, it is traversed and the output is written into a file.

// The traversal done is an in-order.  When done against a BST, it will execute
// visits in a sorted manner!  That's why the file produced has the integers in
// increasing order.


// stdio provides access to file processing and console processing
#include <stdio.h>
// stdlib provides malloc and free dynamic memory allocations
#include <stdlib.h>
// ctype gives us the following
// isalpha - looks at a character and returns 0 if it is not an alphanumeric
//           and non 0 if it is
// tolower - returns a lower case version of a character (eg. A becomes a)
#include <ctype.h>

// stdbool defines "bool", "true" and "false"
// it is used whenever a boolean is being produced, used, or passed back to a caller
#include <stdbool.h>

// this is a string constant that sets the name of the file to open and read in
// integers from
#define INFILENAME "integers.in"
// this is a string constant that sets the name of the file to open and write in
// integers
#define OUTFILENAME "integersFreq.out"

// To make sure we are allocating and deallocating dynamic memory,
// variable AllocationCount is declared and referenced by any other
// code that does dynamic memory allocation and deallocation
int AllocationCount = 0;

// NodeData struct contains two integer elements, one
// called num to allow for a node's number value to be set
// and the other called freq to count how many times it is
// referenced within a file
typedef struct {
    int num;
    int freq;
} NodeData;

// TreeNode struct contains two elements pertaining
// to characteristics of a node including
// one NodeData struct type to hold a node's integer
// value and a struct of its own type called treeNode
// to allow for pointers to adjacent nodes such
// as parent and left/right subtrees
typedef struct treeNode {
    NodeData data;
    struct treeNode *left, *right;
} TreeNode, *TreeNodePtr;

// BinaryTree struct contains one TreeNode struct
// point element to be used as a binary tree.
// The TreeNode struct is important as it will be
// the binary tree's root node and is referenced as
// -> root
typedef struct {
    TreeNodePtr root;
} BinaryTree;

// getInt is a utility that reads integers from a file
bool        getInt     (FILE *, int *aNum );

// newTreeNode dynamically allocated a tree node, fills
// in the user data and clears the left and right side links
TreeNodePtr newTreeNode (NodeData nodeInformation);

// newNodeData is a utility that packages an integer and a frequency
// into a user data struct called NodeData
NodeData    newNodeData (int aNum, int frequency);

// findOrInsert traverses a binary search tree looking for a node
// that matches the user criteria.  In this case, it is an integer.
// It either returns the pointer to the matching node
// or it links the node into the tree at its proper, sorted location
TreeNodePtr findOrInsert(BinaryTree, NodeData nodeInformation);

// inOrder does a traversal of the BST that will write a file
// with the traversal results.
void        inOrder     (FILE *, TreeNodePtr);

// deleteTree() deletes the frees the storage that was allocated by the call
// to buildTree()
void deleteTree(TreeNodePtr nodeParent);

// main will do the following:
//      1. It opens both an input and output file.  Failure to be able to
//          open the files will result in program termination
//      2. It will build a BST from the file integers and maintain a
//          count of the number of occurrences of each integer
//      3. It will write the integers and their occurrences in a file
int main()
{
    // integer is a scratch array used to get complete integers from the file
    int integer;

    // open the input file and exit if it does not open
    FILE * in = fopen( INFILENAME, "r");
    if (in == NULL) {
        printf ("Unable to open file %s... exiting", INFILENAME);
        exit (0);
    }

    // the input file opened, so open the output file.
    // it it does not open, close the input file and exit
    FILE * out = fopen( OUTFILENAME, "w");
    if (out == NULL)
    {
        printf ("Unable to open file %s for output... exiting", OUTFILENAME);
        fclose (in);
        exit(0);
    }
    // print and display the number of items currently
    // dynamically allocated
    printf("Allocation count starts at %d\n\n", AllocationCount);

    // both files are open, declare the binary search tree (bst)
    // and initialize its root as NULL
    BinaryTree bst;
    bst.root = NULL;

    // get integers and insert them into the BST.
    // since new nodes will have a frequency of 0 and matching
    // nodes will have a current frequency, bump the frequency
    // in either case to reflect their occurrence in the text
    while (getInt(in, &integer) == true) {
        if (bst.root == NULL)
            bst.root = newTreeNode(newNodeData(integer, 1));
        else {
            TreeNodePtr node = findOrInsert(bst, newNodeData(integer, 0));
            node -> data.freq++;
        }
    }
    // print and display the number of items currently
    // dynamically allocated after building the tree
    printf("Allocation count after tree build is %d\n\n", AllocationCount);

    // The file has been processed.  Write out the results by using
    // an in-order traversal and writing as the "visit"
    fprintf(out, "\nIntegers       Frequency\n\n");
    inOrder(out, bst.root);
    fprintf(out, "\n\n");

    // delete the binary tree and free all node memory
    deleteTree(bst.root);
    // set the tree to NULL to reflect the binary tree no longer exists
    bst.root = NULL;
    // prove the binary tree does not exist by printing and displaying
    // AllocationCount to equal zero and conduct a final in-order transversal
    // Nothing will print
    printf("\nAllocation count after deleting the tree is %d\n\n", AllocationCount);
    inOrder(out, bst.root);
    printf("Back from inOrder.. nothing should have printed.\n");

    // close both files and return.  We're done!!
    fclose(in);
    fclose(out);

    return 0;
} // end main

// getInt has the task of reading in integers from
// the file, updating the passed-in integer and returning
// a boolean indication if it was able to find/set an integer.
// The routine returns true if there is an integer and false if there is none
bool getInt(FILE * in, int *aNum)
{
    // initialize a counter to describe
    // how many integers are being read in
    int cmd;
    // read in a line from the file
    cmd = fscanf(in, "%d", &*aNum);
    // check that the number of integers being read in
    // is at least 1
    if (cmd == 1) {
        // at least 1 integer is being read in
        // so return that an integer was found
        return true;
    } else {
        // at least 1 integer is not being read in
        // so return that an integer was not found
        return false;
    }
} // end getInt

// findOrInsert searches a binary tree looking for nodeInformation
// in this implementation, the nodeInformation field "integer" is being
// looked at to see if there is a match.
//
// Because this is a binary tree, we can keep comparing if the
// value is less than us (indicating to proceed left), is us, or
// greater than us (indicating to proceed right).
// If we hit the end of a left traversal and the value has not been found,
// we add it to our left side and return it
// In a similar manner, if we hit the end of a right traversal and the
// value has not been found, we add it to the right side and return it
// the node we return will either be a new node (zero frequency) or a node
// that we have found.  That enables the caller to increment the frequency
// without knowing if this was a new node or a match
//
TreeNodePtr findOrInsert(BinaryTree bt, NodeData nodeInformation)
{
    // if the root is empty, just return a node with the nodeInformation in it
    if (bt.root == NULL) return newTreeNode(nodeInformation);

    // curr is the tree node currently at the top of the tree
    TreeNodePtr curr = bt.root;
    // loop until we have a match (returns in the loop will happen if
    // we hit the end of the tree
    while (nodeInformation.num != curr -> data.num) {
        // are we less than the node?
        if (nodeInformation.num < curr -> data.num) {
            // yes, need to go left if we can
            // NULL indicates we are at a left leaf, so add the new node
            // to the current leaf on the left side and return it
            if (curr -> left == NULL)
                return curr -> left = newTreeNode(nodeInformation);
            else
                // keep looking left since we are not at a leaf
                curr = curr -> left;
        } else {
            // we are greater than the current right side
            // need to go further right if we can
            // NULL indicates we are at a right leaf, so add the new node
            // to the current leaf on the right side and return it
            if (curr -> right == NULL)
                return curr -> right = newTreeNode(nodeInformation);
            else
                // keep looking right since we are not at a leaf
                curr = curr -> right;
        }
    }
    // we get here if the while completed, indicating we found a node
    // that matched a current node in the tree
    // return pointer to the node
    return curr;
} //end findOrInsert

// newTreeNode makes a node through dynamic allocation, initializing
// its left and right children to NULL and inserting the user data provided
// as nodeInformation.
// It returns the pointer to the tree node it just allocated and initialized
TreeNodePtr newTreeNode(NodeData nodeInformation)
{
    // allocate a tree node
    TreeNodePtr p = (TreeNodePtr) malloc(sizeof(TreeNode));
    // update AllocationCount to reflect the newly created memory
    AllocationCount++;
    // fill in the user data
    p -> data = nodeInformation;
    // NULL its links
    p -> left = p -> right = NULL;
    // give it back to the caller
    return p;
} //end newTreeNode

// inOrder does a go left, visit, go right traversal through recursively
// calling itself.  Instead of calling on a "visit", it accomplishes it
// by writing out the user data integer and occurrence count to the file
// provided
void inOrder(FILE * out, TreeNodePtr node)
{
    // if we are not NULL we cannot go further in the tree
    if (node!= NULL) {
        // go left
        inOrder(out, node -> left);
        // "visit" by printing the user information
        fprintf(out, "%d %2d\n", node -> data.num, node -> data.freq); /////////////%d = -15s///////////
        // go right
        inOrder(out, node -> right);
    }
    return;
} //end inOrder

// deleteTree() uses recursion to search the tree, delete and free up all of its nodes
// It returns nothing
void deleteTree(TreeNodePtr rootNode)
{
    // check if binary tree node is not NULL
    if (rootNode != NULL) {
        // delete node's left subtree
        deleteTree(rootNode->left);
        // delete node's right subtree
        deleteTree(rootNode->right);
        // display which node will be deleted and freed
        printf("Node %d has been freed\n", rootNode->data);
        // delete and free the node
        free(rootNode);
        // decrease AllocationCount to reflect the freed memory
        AllocationCount--;
    }
}

// newNodeData is a utility that builds a NodeData structure from
// the user data fields it receives as input.  In this case, it is a integer
// that is NULL terminated and an initial frequency of occurrence
NodeData newNodeData(int aNum, int frequency)
{
    // make a NodeData and fill it with the integer and frequency provided
    NodeData temp;
    temp.num = aNum;
    temp.freq = frequency;
    // return it with the packaging of the user data complete
    return temp;
} //end newNodeData
