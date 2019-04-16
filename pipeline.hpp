#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <dlfcn.h>


class Vector {
    public:
        long size;
        long size_y;
        double* array;
        double* target;
        Vector(long size) {
            this->size = size;
            this->size_y = 1
            this->allocate();
        };
        Vector(long size, long size_y) {
            this->size = size;
            this->size_y = size_y;
            this->allocate();
        };
        void display();
    private:
        void allocate() {
            array = new double[size];
            target = new double[size_y];
        }
};

typedef Vector* (*STEP_FN)(Vector*);

class Pipeline {
    public:
        Vector* exe(Vector* input);
        Pipeline(const char* config_file_name);
        void add(const char*, const char*);
        void clear();

    private:
        STEP_FN load_step(const char* so_file_name, const char* function_name);
        std::list<STEP_FN> pipeline;
};
