#include "pipeline.hpp"


int main() {
    // initialize vector with some elements
    Vector* my_vector = new Vector(10, 0.0);
    Vector* targets = new Vector(1, 1.0);
    DataPoint *row = new DataPoint(my_vector, targets);
    for(int i=0; i<10; i++) {
        (*my_vector)[i] = 0.1 * i;
    }

    Pipeline* pipeline = new Pipeline("pipeline.lst");

    for(long i=0; i<100; i++) {
        row = pipeline->exe(row);
        //row->y->display();
    }
    return 0;
}