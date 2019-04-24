#pragma once
#include <iostream>
#include <string>

template <class T = double>
class Vector {
   public:
    Vector(unsigned size) {
	this->size_ = size;
	this->allocate();
    };
    Vector(unsigned size, T val) {
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
    inline T& at(const unsigned index) {
        #if defined(_DEBUG) || defined(NDEBUG)
        if (index >= size_) {
            std::cerr << "Array index " << index << " out of bounds!\n";
            exit(-1);
        }
        #endif
        return array[index];
        }
    inline T& operator[](unsigned index) {
        #if defined(_DEBUG) || defined(NDEBUG)
        if (index >= size_) {
            std::cerr << "Array index " << index << " out of bounds!\n";
            exit(-1);
        }
        #endif
        return array[index];
    }
    inline unsigned size() { return size_; }
    inline ~Vector() { delete array; }

   private:
    unsigned size_;
    T* array;
    void allocate() { array = new T[size_]; }
};


template<class Tx = double, class Ty = double>
class DataPoint {
   public:
    DataPoint(Vector<Tx>& x) { this->x = x; }
    DataPoint(Vector<Tx>& x, Vector<Ty>& y) {
	this->x = x;
	this->y = y;
    }
    Vector<Tx> x = NULL;
    Vector<Ty> y = NULL;
};
