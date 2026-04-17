#include "Line.h"
#include <iostream>

using namespace std;

Line::Line(int _m, int _k) {
  m = _m;
  k = _k;
}

Line::~Line() {}

int Line::evaluate(int _x) {
  return (m * _x) + k;
}

void Line::details(int& _m, int& _k) {
  _m = m;
  _k = k;
}

void Line::print_details() {
  int m, k;
  details(m, k);
  cout << "y = " << m << "x + " << k << endl;
}