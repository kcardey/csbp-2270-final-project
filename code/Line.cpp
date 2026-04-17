#include <iostream>
#include "Line.h"

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