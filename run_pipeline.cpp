#include "pipeline.hpp"

int main() {
    // initialize vector with some elements
    Vector<double> my_vector(10, 0.0);
    Vector<double> targets(5, 1.0);
    DataPoint<double>* row = new DataPoint<double>(my_vector, targets);
    for (unsigned i = 0; i < 10; i++) {
        my_vector.at(i) = 0.1 * i;
    }

    Pipeline* pipeline = new Pipeline("pipeline.lst");

    for(unsigned epoch=0; epoch<100; epoch++)
        pipeline->exe(row);
    return 0;
}
