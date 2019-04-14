#pragma once


class Vector {
    public:
        long size;
        double* array;
        Vector(long size) {
            this->size = size;
            array = new double[size];
        };
};

typedef Vector* (*STEP_FN)(Vector*);
