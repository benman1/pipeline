#include "load_step.hpp"
#include "types.hpp"
#include "types.hpp"
#include <iostream>
#include <type_traits>
#include <list>


void print_vector(Vector *input) {
    for(int i=0; i<input->size; i++) {
        std::cout << input->array[i] << " ";
    }
    std::cout << "\n";
    return;
}

int main() {
    Vector* my_vector = new Vector(10);
    for(int i=0; i<10; i++) {
        my_vector->array[i] = 0.1 * i;
        //std::cout << my_vector[i];
    }
    std::cout << "before... \n";
    print_vector(my_vector);

    STEP_FN step1 = load_step("step1.so", "step1");
    std::list<STEP_FN> pipeline;
    pipeline.push_back(step1);

    for(STEP_FN step: pipeline) {
        my_vector = step(my_vector);
    }
    std::cout << "\nafter... \n";
    print_vector(my_vector);
    return 0;
}