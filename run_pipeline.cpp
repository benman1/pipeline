#include "pipeline.hpp"


int main() {
    // initialize vector with some elements
    Vector my_vector(10, 0.0);
    Vector targets(5, 1.0);
    DataPoint *row = new DataPoint(my_vector, targets);
    for(unsigned i=0; i<10; i++) {
        my_vector.at(i) = 0.1 * i;
    }

    Pipeline* pipeline = new Pipeline("pipeline.lst");

    DataPoint* result;
    //for(unsigned epoch=0; epoch<50; epoch++) {
    result = pipeline->exe(row);
    return 0;
}
