#include "Node.h"

Node::Node(int _lo, int _hi) {
  lo = _lo;
  hi = _hi;
  line = nullptr;
  left = nullptr;
  right = nullptr;
}

Node::~Node() {}

int Node::get_lo() {
  return lo;

}
int Node::get_hi() {
  return hi;
}

int Node::calculate_mid() {
  return lo + (hi - lo) / 2;
}