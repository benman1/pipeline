#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <dlfcn.h>


class Vector {
    public:
        long size;
        double* array;
        Vector(long size) {
            this->size = size;
            this->allocate();
        };
        void display();
    private:
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
        std::map<const char*, transformer*> pipeline;
};
