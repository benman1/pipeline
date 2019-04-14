#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>


class Vector {
    public:
        long size;
        double* array;
        Vector(long size) {
            this->size = size;
            array = new double[size];
        };
        void display();
};

typedef Vector* (*STEP_FN)(Vector*);

class Pipeline {
    public:
        Vector* exe(Vector* input);
        Pipeline(const char* config_file_name);

    private:
        STEP_FN load_step(const char* so_file_name, const char* function_name);
        std::list<STEP_FN> pipeline;
};
