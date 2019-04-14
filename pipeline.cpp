#include "load_step.hpp"
#include "types.hpp"
#include "types.hpp"
#include <iostream>
#include <type_traits>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>



void print_vector(Vector *input) {
    for(int i=0; i<input->size; i++) {
        std::cout << input->array[i] << " ";
    }
    std::cout << "\n";
    return;
}

std::list<STEP_FN> load_pipeline(char* pipeline_filename) {
    typedef std::pair<const char *, const char *> StrLimits;
    std::list<STEP_FN> pipeline;

    std::ifstream pipeline_file("pipeline.lst");
    std::string str; 
    std::istringstream iss;
    while (std::getline(pipeline_file, str)) {
        std::vector<std::string> result;
        iss = std::istringstream(str);
        for(std::string s; iss >> s; ) {
            result.push_back(s);
        }

        STEP_FN step1 = load_step(result[0].c_str(), result[1].c_str());
        pipeline.push_back(step1);
    }
    return pipeline;
}

int main() {
    Vector* my_vector = new Vector(10);
    for(int i=0; i<10; i++) {
        my_vector->array[i] = 0.1 * i;
        //std::cout << my_vector[i];
    }
    std::cout << "before... \n";
    print_vector(my_vector);

    std::list<STEP_FN> pipeline = load_pipeline("pipeline.lst");

    for(STEP_FN step: pipeline) {
        my_vector = step(my_vector);
    }
    std::cout << "\nafter... \n";
    print_vector(my_vector);
    return 0;
}