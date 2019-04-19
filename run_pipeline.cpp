#include "pipeline.hpp"


int main() {
    // initialize vector with some elements
    Vector* my_vector = new Vector(10);
    for(int i=0; i<10; i++) {
        my_vector->array[i] = 0.1 * i;
    }
    DataPoint *row = new DataPoint(my_vector);

    Pipeline* pipeline = new Pipeline("pipeline.lst");
    pipeline->exe(row);
    return 0;
}