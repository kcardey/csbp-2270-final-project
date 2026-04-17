#ifndef LiChowTree_H__
#define LiChowTree_H__

#include "Line.h"
#include "Node.h"

const int LO = -500; // minimum acceptable range value
const int HI = 500; // maximum acceptable range value

// Li Chao Tree is a type of Binary Search Tree where the data stored
// in each node is a linear function instead of a static data value. The
// specific linear function, called a Line, stored in each node is of the
// form y = mx + k and becomes the 'winner' by either minimizing or maximizing
// the output value given a specific input value. This particular implementation
// of a Li Chao Tree minimizes the output value.

class LiChaoTree {
  private:
    int count; // the number of non-deleted nodes in the tree
    Node** root;

    // insert_helper is a helper function to insert a Line to the tree
    // recursively. At each level, the Line is compared to the existing
    // Node's line. The winnng Line stays in that Node while the loser is
    // pushed down a level. If a Node without a Line is encountered, it simply
    // adds the Line to the Node and breaks the recursive loop.
    void insert_helper(Node* node, Line* line);

    // rebuild is a helper function to remove a Line from the tree
    // recursively. Removing a Line from the tree breaks the structure of the
    // tree entirely, so we must rebuild the tree without this Line.
    void rebuild(LiChaoTree* new_tree, Node* node, Line* line);
  public:
    // Constructor
    LiChaoTree();

    // Destructor
    ~LiChaoTree();

    // init_node initializes a new node from the heap.
    Node* init_node(int lo, int hi);

    // insert adds a Line to the Li Chao tree, creating a new Node in
    // the tree as needed. Utilizes the insert_helper function to add
    // new nodes to the tree recursively. This function has O(log n)
    // complexity.
    void insert(Line* line);

    // remove effectively deletes a line from the Li Chao tree by rebuilding
    // the entire tree. Utilizes the rebuild function to rebuild the tree
    // recursively. This function has O(n) complexity.
    void remove(Line* line);

    // query searches for the Line that evaluates to the minimum
    // possible output value for a given input value. This is 
    // accomplished by searching for the path from the root node
    // to a leaf node that contains the input value. Each line along
    // this path is compared to the others and the Line with the 
    // minimum output value is returned. This function has O(log n)
    // complexity.
    Line* query(int val);

    // size returns the number of nodes in the Li Chao Tree
    int size();

    // isEmpty returns true when the root node is null
    bool isEmpty();
};

#endif