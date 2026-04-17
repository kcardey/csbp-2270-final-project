#include <iostream>
#include <fstream>
#include <sstream>

#include "LiChaoTree.h"
#include "Line.h"

using namespace std;

int main() {
  // load the lines file
  ifstream file("../app/lines.txt");
  string line;

  LiChaoTree* tree = new LiChaoTree();

  // generate the Li Chao Tree
  while (getline(file, line)) {
    stringstream ss(line);
    string mStr, kStr;
    getline(ss, mStr, '|');
    getline(ss, kStr, '|');

    Line* line = new Line(std::stof(mStr), std::stof(kStr));
    tree->insert(line);
  }

  int val;

  // get value input from the user
  while(true) {
    cout << "Enter a number between " << LO << " and " << HI <<": ";
    cin >> val;

    if (LO <= val && val <= HI) {
      break;
    }

    cout << endl;
    cout << "Please enter a valid number" << endl;
  }
  
  

  // query the tree for the winner
  Line* winner = tree->query(val);

  // display this info to the user
  cout << endl;
  cout << "Line Winner" << endl;
  cout << "====================" << endl;

  int m;
  int k;
  winner->details(m, k);
  cout << "y = " << m << "x + " << k << endl;

  return 0;
}