#include "pipeline.hpp"


extern "C" Vector* step1(Vector *input) {
        for(int i=0; i<input->size; i++) {
            input->array[i] *= 5;
        }
        return input;
}
