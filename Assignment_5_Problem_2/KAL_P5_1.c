// Program P5.1 from Kalicharan, modified to make it easier
// to document and understand.
//
// It uses recursive implementations of pre, in and post order
// traversals.
//
// An additonal modification is the addition of the parent linkage
// that can be used to traverse from a node back through its parent.
//
// This program is designed to demonstrate building a binary tree. It
// consists of functions and definitions for the binary tree including
// building a tree, pre-order/in-order/post-order transversal, visit
// (printing a node’s name) and deleting the binary tree. AllocationCount
// will tell how many things are currently dynamically allocated.
// It uses a recursive routine, that is a routine which calls itself.
// It is used in this program while searching a tree to delete all
// of its nodes and free memory.

// printf and reading a FILE support
#include <stdio.h>
// we will use strcpy() and strcmp() from string.h
#include <string.h>
// stdlib provides the definition of NULL and the declarations for
// malloc() and free()
#include <stdlib.h>

// this is an int constant that limits a node/read-in-word's name to a maximum
// length, or number of characters, to this set value
#define MaxWordSize 20
// this is a string constant that sets the name of the file to open and read in
// words from
#define FILENAME "btree.in"

// To make sure we are allocating and deallocating dynamic memory,
// variable AllocationCount is declared and referenced by any other
// code that does dynamic memory allocation and deallocation
int AllocationCount = 0;

// NodeData struct contains one char array element
// called word to allow for a node's name to be set
// to a MaxWordSize number of characters (20) and
// a NULL (zero byte) at the end
typedef struct {
    char word[MaxWordSize+1];
} NodeData;

// TreeNode struct contains two elements pertaining
// to characteristics of a node including
// one NodeData struct type to hold a node's name
// and a struct of its own type called treeNode
// to allow for pointers to adjacent nodes such
// as parent and left/right subtrees
typedef struct treeNode {
    NodeData data;
    struct treeNode *left, *right, *parent;
} TreeNode, *TreeNodePtr;

// BinaryTree struct contains one TreeNode struct
// point element to be used as a binary tree.
// The TreeNode struct is important as it will be
// the binary tree's root node and is referenced as
// -> root
typedef struct {
    TreeNodePtr root;
} BinaryTree;

// buildTree creates all nodes for a binary tree and assigns each one a word
// with maximum length as its name. The word is grabbed from an opened file
// and this function allocates memory for each newly created
// node. It takes a file name and a binary tree root node as arguments.
// It returns the node which gets created and assigned a name.
TreeNodePtr buildTree         (FILE * in, TreeNodePtr nodeParent);
// Pre-order traversal of a tree.
// First visit the root node, then the left subtree and finally the right subtree.
// Every node may represent a subtree itself.
void        preOrder          (TreeNodePtr nodeP);
// In-order traversal of a tree.
// First visit the left subtree, then the root and finally the right subtree.
// Every node may represent a subtree itself.
void        inOrder           (TreeNodePtr nodeP);
// Post-order traversal of a tree.
// First visit the left subtree, then the right subtree and finally the root node.
// Every node may represent a subtree itself.
void        postOrder         (TreeNodePtr nodeP);
// Visit takes a node to print and display its name, a letter.
// It returns nothing
void        visit             (TreeNodePtr nodeP);
// deleteTree() deletes the frees the storage that was allocated by the call
// to buildTree()
void deleteTree(TreeNodePtr nodeParent);

// the main takes no arguments, but opens a file to read in
// if the file cannot be opened, it prints a message and
// exits the program. It prints AllocationCount throughout
// its lifetime to provide insight into how many items
// have currently dynamically allocated memory.
// It is responsible for building a binary tree then
// conducting pre-order/in-order/post-order transversals
// while printing out the results as names of nodes in
// the order of the respective transversal. After all
// transversals, the tree is deleted by searching for the lowest
// node using post-order transversal and deleting and freeing
// that node until no nodes exist. Then the binary tree root is
// set to NULL to reflect that the binary tree no longer exists.
// Then the main calls an in-order transversal to prove the
// tree no longer exists and that no node names are printed
// and displayed. The main then
// closes the file which data is being read from.
int main()
{
    // try to open a file
    FILE * in = fopen(FILENAME, "r");
    // if the file doesn't exists or is empty
    // print and display an error message and exit the program
    if (in == NULL) {
        printf ("Unable to open file %s... exiting\n", FILENAME);
        exit (0);
    }
    // print and display number of items currently dynamically
    // allocated
    printf("Allocation count starts at %d\n", AllocationCount);
    // initialize a new binary tree to prepare for building its nodes
    BinaryTree bt;
    // build the binary tree using the newly initialized binary tree
    // create nodes for each of the words contained in the file
    // it takes a NULL argument along with the file name because
    // the node parent (in this case the root) is still NULL
    // from being newly initialized
    bt.root = buildTree(in, NULL);
    printf("Allocation count after tree build is %d\n", AllocationCount);
    // Dp a pre-order traversal of a tree.
    // First visit the root node, then the left subtree and finally the right subtree.
    printf("\nThe pre-order traversal is: ");
    preOrder(bt.root);
    // Do an in-order traversal of a tree.
    // First visit the left subtree, then the root and finally the right subtree.
    printf("\n\nThe in-order traversal is: ");
    inOrder(bt.root);
    // Do a post-order traversal of a tree.
    // First visit the left subtree, then the right subtree and finally the root node.
    printf("\n\nThe post-order traversal is: ");
    postOrder(bt.root);
    printf("\n\n");
    // delete the binary tree and free all node memory
    printf("Starting tree deletion...\n");
    deleteTree(bt.root);
    // set the tree to NULL to reflect the binary tree no longer exists
    bt.root = NULL;
    // prove the binary tree does not exist by printing and displaying
    // AllocationCount to equal zero and conduct a final in-order transversal
    // Nothing will print
    printf("\nAllocation count after deleting the tree is %d\n", AllocationCount);
    printf("\n\nThe in-order traversal is now: \n");
    inOrder(bt.root);
    printf("back from call to in-order. Nothing should have printed.\n");
    // close the file being read
    fclose(in);
} // end main


// buildTree takes a file name and a binary tree root node as arguments.
// It is responsible for searching the file for a name, creating a new
// node if the name exists and assigning it to the node's name, or struct
// item called "word."
// if the name is "@" or NULL then the search jumps to the next available
// subtree.
// It uses recursion to call itself and repeat this process for all existing
// nodes within the binary tree.
// Each time a node is created, memory is dynamically allocated
// for it. AllocationCount is increased to reflect the dynamically
// allocated memory. It returns the node which gets created and assigned
// a name.
TreeNodePtr buildTree   (FILE * in, TreeNodePtr nodeParent)
{
    // initialize a string variable to hold MaxWordSize number of
    // characters (20) and a NULL (zero byte) at the end
    char str[MaxWordSize+1];
    // look through the file for names
    fscanf(in, "%s", str);
    // check if the found string is not a name
    // but is an "@" character
    // i.e. NULL
    if (strcmp(str, "@") == 0) return NULL;
    // allocate memory for the node
    TreeNodePtr p = (TreeNodePtr) malloc(sizeof(TreeNode));
    // increase AllocationCount to reflect the newly created memory
    AllocationCount++;
    // set the node's name, or struct item called "word"
    strcpy(p -> data.word, str);
    // set the node's parent, or node which resides above it
    p -> parent = nodeParent;
    // set the node's left subtree node
    p -> left = buildTree(in, p);
    // set the node's right subtree node
    p -> right = buildTree(in, p);
    // return the node who's information was
    // just set
    return p;
} //end buildTree

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
        printf("Node ");
        visit(rootNode);
        printf("has been freed\n");
        // delete and free the selected node
        free(rootNode);
        // decrease AllocationCount to reflect the freed memory
        AllocationCount--;
    }
}

// Print and display a node's name, a letter,
// that takes the binary tree's root node as an argument
// It returns nothing
void visit(TreeNodePtr nodeP)
{
    // print and display the node's name, in this program it is
    // an letter, by accessing its structure's item called word
    printf("%s ", nodeP -> data.word);
} //end visit

// Pre-order traversal of a tree that takes the binary tree's root node as an argument
// First visit the root node, then the left subtree and finally the right subtree.
// Every node may represent a subtree itself.
// It returns nothing.
// It uses a recursive routine to call itself to traverse the tree via pre-order method
// and call visit() to print and display each currently
// looked at node's name
void preOrder(TreeNodePtr nodeP)
{
    // check that the node exists
    if (nodeP != NULL) {
        // print and display the existing node's name
        visit(nodeP);
        // repeat this function's logic at the left subtree's nodes
        // using recursion, calling this function again
        preOrder(nodeP -> left);
        // repeat this function's logic at the right subtree's nodes
        // using recursion, calling this function again
        preOrder(nodeP -> right);
    }
} //end preOrder

// In-order traversal of a tree that takes the binary tree's root node as an argument
// First visit the left subtree, then the root and finally the right subtree.
// Every node may represent a subtree itself.
// It returns nothing.
// It uses a recursive routine to call itself to traverse the tree via in-order method
// and call visit() to print and display each currently
// looked at node's name
void inOrder(TreeNodePtr nodeP)
{
    // check that the node exists
    if (nodeP != NULL) {
        // repeat this function's logic at the left subtree's nodes
        // using recursion, calling this function again
        inOrder(nodeP -> left);
        // print and display the existing node's name
        visit(nodeP);
        // repeat this function's logic at the right subtree's nodes
        // using recursion, calling this function again
        inOrder(nodeP -> right);
    }
} //end inOrder

// Post-order traversal of a tree that takes the binary tree's root node as an argument
// First visit the left subtree, then the right subtree and finally the root node.
// Every node may represent a subtree itself.
// It returns nothing.
// It uses a recursive routine to call itself to traverse the tree via post-order method
// and call visit() to print and display each currently
// looked at node's name
void postOrder(TreeNodePtr nodeP)
{
        // check that the node exists
        if (nodeP != NULL) {
        // repeat this function's logic at the left subtree's nodes
        // using recursion, calling this function again
        postOrder(nodeP -> left);
        // repeat this function's logic at the right subtree's nodes
        // using recursion, calling this function again
        postOrder(nodeP -> right);
        // print and display the existing node's name
        visit(nodeP);
    }
} //end postOrder
