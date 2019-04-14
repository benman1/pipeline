# Pipelining
Create a dynamic workflow pipeline. Pipeline steps can be loaded as libraries (e.g. .so files).

For now, pipeline steps are functions, i.e. they are static (no state). I might change this later.

The pipeline can be defined in terms of transformations that get a vector and pass a vector (by reference, obviously). In the pipeline.cpp file, a file, pipeline.lst, is read that contains a processing step in each line; shared library file name and function are separated by space:
```bash
step1.so step1
```

These steps are then applied one by one.

## Dependencies
* dlopen library

## Walkthrough
For the dynamic loading to work, make sure you expose your step functions as C API. In most cases, a simple extern "C" will do.

For example, step1.cpp:
```cpp
#include "pipeline.hpp"

extern "C" Vector* step1(Vector *input) {
    for(int i=0; i<input->size; i++) {
        input->array[i] *= 5;
    }
    return input;
}
```

Compile this into a shared library like so:
```bash
g++ -fPIC step1.cpp -shared -o step1.so -std=gnu++11
```

In order to run the pipeline, provide a configuration, define a vector, and execute (run_pipeline.cpp):
```cpp
#include "pipeline.hpp"


int main() {
    // initialize vector with some elements
    Vector* my_vector = new Vector(10);
    for(int i=0; i<10; i++) {
        my_vector->array[i] = 0.1 * i;
    }

    Pipeline* pipeline = new Pipeline("pipeline.lst");
    pipeline->exe(my_vector);
    return 0;
}
```

Compile run_pipeline.cpp as follows:
```bash
g++ -std=c++1z run_pipeline.cpp pipeline.cpp -o run_pipeline
```

Executing you initialize a vector and then apply the step(s):
```
before...
0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9
Loading step function step1 from step1.so

after...
0 0.5 1 1.5 2 2.5 3 3.5 4 4.5
```

