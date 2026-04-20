#include "LiChaoTree.h"
#include <iostream>
#include <utility>

using namespace std;

LiChaoTree::LiChaoTree() {
  count = 0;
  root = new Node*;
  *root = nullptr;
}

LiChaoTree::~LiChaoTree() {}

Node* LiChaoTree::init_node(int lo, int hi) {
  return new Node(lo, hi);
}

void LiChaoTree::insert(Line* line) {
  count += 1;
  if (*root == nullptr) {
    Node* new_node = init_node(LO, HI);
    new_node->line = (line);
    *root = new_node;
  } else {
    insert_helper(*root, line);
  }
}

void LiChaoTree::insert_helper(Node* node, Line* line) {
  // if node doesn't have a line, add the line to the node
  if (node->line == nullptr) {
    node->line = line;
    return;
  }

  // calculate the midpoint of the node
  int lo = node->get_lo();
  int hi = node->get_hi();
  int mid = node->calculate_mid();

  // set default winner and loser
  Line* winner = node->line;
  Line* loser = line;

  // swap if loser beat winner
  if (loser->evaluate(mid) < winner->evaluate(mid)) {
    std::swap(winner, loser);
    node->line = winner;
  }

  // prevent infinite recursion
  if (hi - lo <= 1) return;

  // determine if we push left or right
  if (loser->evaluate(hi) < winner->evaluate(hi)) {
    // push right
    if (node->right == nullptr) {
      node->right = init_node(mid, hi);
    }
    insert_helper(node->right, loser);
  } else {
    // push left
    if (node->left == nullptr) {
      node->left = init_node(lo, mid);
    }
    insert_helper(node->left, loser);
  }
}

void LiChaoTree::remove(Line* line) {
  LiChaoTree* new_tree = new LiChaoTree();
  rebuild(new_tree, *root, line);
  count = new_tree->count;
  *root = *new_tree->root;
  delete new_tree;
}

void LiChaoTree::rebuild(LiChaoTree* new_tree, Node* node, Line* line) {
  if (node != nullptr) {
    rebuild(new_tree, node->left, line);
    rebuild(new_tree, node->right, line);

    if (line != node->line) {
      new_tree->insert(node->line);
    } else {
      delete node;
    }
  }
}

Line* LiChaoTree::query(int val) {
  // start at the root
  Node* cursor = *root;
  if (!cursor) return nullptr;

  // default the winner to the root node's line
  Line* winner = cursor->line;

  while (cursor) {
    // update winner if cursor's line is better
    if (cursor->line->evaluate(val) < winner->evaluate(val)) {
      winner = cursor->line;
    }

    // update the cursor left or right
    int mid = cursor->calculate_mid();
    cursor = val < mid ? cursor->left : cursor->right;
  }

  return winner;
}

int LiChaoTree::size() {
  return count;
}

bool LiChaoTree::is_empty() {
  return *root == nullptr;
}

Node* LiChaoTree::get_root() {
  return *root;
}

void LiChaoTree::print_tree(Node* node, int depth) {
  if (node == nullptr) return;

    // indent based on depth
    for (int i = 0; i < depth; i++) {
      cout << "  ";
    }

    cout << "[" << node->get_lo() << ", " << node->get_hi() << "] ";
    
    if (node->line != nullptr) {
      int m, k;
      node->line->details(m, k);
      cout << "Line: y = " << m << "x + " << k;
    } else {
      cout << "Line: None";
    }

    cout << endl;

    // recursively print children
    print_tree(node->left, depth + 1);
    print_tree(node->right, depth + 1);
}