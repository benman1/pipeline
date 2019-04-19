#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <dlfcn.h>


class Vector {
    public:
        long size;
        Vector(long size) {
            this->size = size;
            this->allocate();
        };
        Vector(long size, double val) {
            this->size = size;
            this->allocate();
            for(long i=0; i<size; i++) {
                this->array[i] = val;
            }
        };
        void display();
        inline double& operator[] (const long index) {
            return array[index];
        }
    private:
        double* array;
        void allocate() {
            array = new double[size];
        }
};

class DataPoint {
    public:
        Vector *x, *y;
        DataPoint(Vector *x) {
            this->x = x;
        }
        DataPoint(Vector *x, Vector *y) {
            this->x = x;
            this->y = y;
        }
};

class transformer {
    public:
        virtual DataPoint* transform(DataPoint*)=0;
        bool trainable=true;  // whether transformer weights are updated
        //virtual void reset()=0;
        //virtual void load(const char* filename)=0;
        //virtual void save(const char* filename)=0;
};

typedef transformer* (*TransformerFactory)();

class Pipeline {
    public:
        DataPoint* exe(DataPoint* input);
        Pipeline(const char* config_file_name);
        void add(const char*, const char*);
        void clear();

    private:
        transformer* load_transformer(const char* so_file_name);
        std::map<std::string, transformer*> pipeline;
};
