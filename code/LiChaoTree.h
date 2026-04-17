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
    Node** root;

    // insert_helper is a helper function to insert a Line to the tree
    // recursively. At each level, the Line is compared to the existing
    // Node's line. The winnng Line stays in that Node while the loser is
    // pushed down a level. If a Node without a Line is encountered, it simply
    // adds the Line to the Node and breaks the recursive loop.
    void insert_helper(Node* node, Line* line);
  public:
    // Constructor
    LiChaoTree();

    // Destructor
    ~LiChaoTree();

    // init_node initializes a new node from the heap.
    Node* init_node(int lo, int hi);

    // insert adds a Line to the Li Chao tree, creating a new Node in
    // the tree as needed. Utilizes the insert_helper function to add
    // new nodes to the tree recursively.
    void insert(Line* line);

    // query searches for the Line that evaluates to the minimum
    // possible output value for a given input value. This is 
    // accomplished by searching for the path from the root node
    // to a leaf node that contains the input value. Each line along
    // this path is compared to the others and the Line with the 
    // minimum output value is returned.
    Line* query(int val);
};

#endif