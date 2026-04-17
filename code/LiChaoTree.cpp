#include "LiChaoTree.h"
#include <utility>

LiChaoTree::LiChaoTree() {
  root = new Node*;
  *root = nullptr;
}

LiChaoTree::~LiChaoTree() {}

Node* LiChaoTree::init_node(int lo, int hi) {
  return new Node(lo, hi);
}

void LiChaoTree::insert(Line* line) {
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
    // push left
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

    // calculate the midpoint
    int lo = cursor->get_lo();
    int hi = cursor-> get_hi();
    int mid = cursor->calculate_mid();

    // update the cursor left or right
    cursor = val < mid ? cursor->left : cursor->right;
  }

  return winner;
}