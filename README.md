# Pipelining
Create a dynamic workflow pipeline. Pipeline steps can be loaded as libraries (e.g. .so files).

For now, pipeline steps are functions, i.e. they are static (no state). I might change this later.

The pipeline can be defined in terms of transformations that get a vector and pass a vector (by reference, obviously). In the pipeline.cpp file, a file, pipeline.lst, is read that contains the processing steps:
```bash
step1.so step1
```

These steps are then applied one by one.

## Dependencies
* dlopen library

## Comments
For the dynamic loading to work, make sure you expose your step functions as C API. In most cases, a simple extern "C" will do.

For example (lifted from dlopen tutorial), hello.cpp:
```cpp
#include <iostream>

extern "C" void hello() {
    std::cout << "hello" << '\n';
}
```

Compile this into a shared library like so:
```bash
g++ -fPIC step1.cpp -shared -o step1.so -std=gnu++11
```

Compile pipeline.cpp as follows:
```bash
g++ -std=c++1z pipeline.cpp -o pipeline
```
