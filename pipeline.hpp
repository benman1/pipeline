#pragma once
#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "vector.hpp"

class transformer {
   public:
    std::string name;
    virtual DataPoint* transform(DataPoint*) = 0;
    bool trainable = true;  // whether transformer parameters are updated
    // virtual void reset()=0;
    // virtual void load(const char* filename)=0;
    // virtual void save(const char* filename)=0;
};

typedef transformer* (*TransformerFactory)();

class Pipeline {
   public:
    DataPoint* exe(DataPoint* input) {
        input->x.display();

        for (const auto& transformer : this->pipeline) {
            std::cout << "Applying " << transformer->name << "\n";
            input = transformer->transform(input);
            //input->x.display();
        }
        return input;
    };
    Pipeline(const char* pipeline_filename) {
        std::ifstream pipeline_file(pipeline_filename);
        std::string str;
        std::istringstream iss;
        while (std::getline(pipeline_file, str)) {
            std::vector<std::string> result;
            iss = std::istringstream(str);
            for (std::string s; iss >> s;) {
                result.push_back(s);
            }

            this->add(result[0].c_str());
        }
    };
    void add(const char* filename) {
        transformer* my_transformer = load_transformer(filename);
        this->pipeline.push_back(my_transformer);
    };
    void clear() { this->pipeline.clear(); };

   private:
    // Given a filename of a shared library to load, load a factory function
    // of type TransformerFactory that initializes the new transformer class.
    // The factory function must be called "transformer_factory"
    // This follows the pattern in https://www.linuxjournal.com/article/3687
    transformer* load_transformer(const char* filename){
        using std::cerr;
        using std::cout;

        cout << "Loading transformer class from " << filename << "\n";

        void* handle = dlopen(filename, RTLD_NOW);
        if (!handle) {
            cerr << "Can't open " << filename << "\n";
            cerr << dlerror() << "\n";
            exit(-1);
        }

        TransformerFactory my_factory =
            (TransformerFactory)dlsym(handle, "transformer_factory");
        transformer* my_transformer = my_factory();

        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            cerr << "Cannot load symbol transformer_factory and execute it\n";
            dlclose(handle);
            exit(-1);
        }

        return my_transformer;
    };
    std::vector<transformer*> pipeline;
};
