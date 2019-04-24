# Pipelining
Create a dynamic workflow pipeline. Pipeline steps can be loaded as libraries (e.g. .so files).

The pipeline can be defined in terms of transformations that get a vector and pass a vector (by reference, obviously). In the pipeline.cpp file, a file, pipeline.lst, is read that contains a processing step in each line; shared library file name and a name for the transformation are separated by space (pipeline.lst):
```bash
step1.so step1
```

These steps are then applied one by one. I might add a more complex architecture later.

Pipeline steps, transformers, are classes; they can have a state including parameters that adapt based on data. I might add a more complete example for this later.

## Dependencies
* dlopen library

## Walkthrough
For the dynamic loading to work, make sure you expose factory functions that return your transformer class using C linkage (using "extern).

For example, step1.cpp:
```cpp
#include "pipeline.hpp"

class multiplier : public transformer {
   public:
    DataPoint<>* transform(DataPoint<>* input) {
        for (unsigned i = 0; i < input->x.size(); i++) {
            input->x[i] *= 5.0;
        }
        return input;
    }
    multiplier() {
        name = "Multiplier";
    }
};

extern "C" transformer* transformer_factory() { return new multiplier; }
```

Compile this into a shared library like so:
```bash
g++ -fPIC transformers/step1.cpp -shared -o step1.so -std=c++1z
```

In order to run the pipeline, provide a configuration, define a vector, and execute (run_pipeline.cpp):
```cpp
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
```

Compile run_pipeline.cpp as follows:
```bash
g++ run_pipeline.cpp -o run_pipeline -std=c++1z
```

Executing you initialize a vector and then apply the step(s):
```
./run_pipeline
Loading transformer class from step1.so
0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9

0 0.5 1 1.5 2 2.5 3 3.5 4 4.5
```

