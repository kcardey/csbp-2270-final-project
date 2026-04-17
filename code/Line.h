#ifndef Line_H__
#define Line_H__

// Line effectively stores the slope and offset of a linear function
// of the form y = mx + k. In the context of the Li Chao tree, it is
// the 'data' that is being stored in each node.

class Line {
  private:
    int m; // slope of the linear function
    int k; // offset of the linear function
  public:
    // values for both m and k must be set in the constructor call
    // and are static for the lifetime of the class instance.
    Line(int _m, int _k);

    // destructor
    ~Line();

    // evaluate calculates the result of the linear function (defined
    // as mx + k) for a given x value.
    int evaluate(int _x);

    // details is a helper function that returns the private values
    // for m and k, which ensures that these values are publically
    // accessible while remaining immutable.
    void details(int& _m, int& _k);
};

#endif