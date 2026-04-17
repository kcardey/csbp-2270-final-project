#ifndef Node_H__
#define Node_H__

#include "Line.h"

// Node is the core object stored in the Li Chao tree. Similar to a
// standard Binary Search Tree (BST) each node stores a piece of data
// as well as pointers to its left and right children. However, the
// data being stored by a Li Chao is a pointer to a Line, which is a 
// linear function, rather than a static value. Additionally, the node
// must also store a range of integer values (lo and hi) for which the
// Line is the winner at the midpoint of these values.

class Node {
  private:
    int lo; // the low end of the range
    int hi; // the high end of the range
  public:
    Line* line;
    Node* left;
    Node* right;
    
    // values for both lo and hi must be set in the constructor call
    // and are static for the lifetime of the class instance.
    Node(int _lo, int _hi);

    // Destructor
    ~Node();

    // getter function to access the private lo variable value
    int get_lo();

    // getter function to access the private hi variable value
    int get_hi();

    // calculates the midpoint of the range
    int calculate_mid();
};

#endif