#pragma once
#include <iostream>
#include <string>

class Vector {
   public:
    Vector(unsigned size) {
	this->size_ = size;
	this->allocate();
    };
    Vector(unsigned size, double val) {
	this->size_ = size;
	this->allocate();
	for (unsigned i = 0; i < size; i++) {
	    this->array[i] = val;
	}
    };
    void display(){
        for (unsigned i = 0; i < this->size_; i++) {
            std::cout << this->array[i] << "\t";
        }
        std::cout << "\n";
        return;
    };
    void display(std::string header){
        std::cout << header << "\n";
        display();
        return;
    };
    inline double& at(const unsigned index) {
	if (index >= size_) {
	    std::cerr << "Array index " << index << " out of bounds!\n";
	    exit(-1);
	}
	return array[index];
    }
    inline double& operator[](unsigned index) { return array[index]; }
    inline unsigned size() { return size_; }
    inline ~Vector() { delete array; }

   private:
    unsigned size_;
    double* array;
    void allocate() { array = new double[size_]; }
};

class DataPoint {
   public:
    DataPoint(Vector& x) { this->x = x; }
    DataPoint(Vector& x, Vector& y) {
	this->x = x;
	this->y = y;
    }
    Vector x = NULL, y = NULL;
};
