#include "pipeline.hpp"


void Vector::display() {
    for(unsigned i=0; i<this->size; i++) {
        std::cout << (this->array)[i] << " ";
    }
    std::cout << "\n";
    return;
}

// Given a filename of a shared library to load, load a factory function
// of type TransformerFactory that initializes the new transformer class.
// The factory function must be called "transformer_factory"
// This follows the pattern in https://www.linuxjournal.com/article/3687
transformer* Pipeline::load_transformer(const char* file_name) {
    using std::cout;
    using std::cerr;

    cout << "Loading transformer class from " << file_name << "\n";

    void* handle = dlopen(file_name, RTLD_NOW);
    if(!handle) {
        cerr << "Can't open " << file_name << "\n";
        cerr << dlerror() << "\n";
        exit(-1);
    }

    TransformerFactory my_factory = (TransformerFactory) dlsym(handle, "transformer_factory");
    transformer *my_transformer = my_factory();

    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol transformer_factory and execute it\n";
        dlclose(handle);
        exit(-1);
    }

    return my_transformer;
}

void Pipeline::add(const char* file_name, const char* transformer_name) {
    transformer *my_transformer = load_transformer(file_name);
    auto it = this->pipeline.begin();
    this->pipeline.insert(it, my_transformer);
}

void Pipeline::clear() {
    this->pipeline.clear();
}

Pipeline::Pipeline(const char* pipeline_filename) {
    std::ifstream pipeline_file(pipeline_filename);
    std::string str;
    std::istringstream iss;
    while (std::getline(pipeline_file, str)) {
        std::vector<std::string> result;
        iss = std::istringstream(str);
        for(std::string s; iss >> s; ) {
            result.push_back(s);
        }

        this->add(result[0].c_str(), result[1].c_str());
    }
}

DataPoint* Pipeline::exe(DataPoint* input) {
    input->x.display();

    for(const auto& transformer: this->pipeline) {
        std::cout << transformer->name << "\n";
        input = transformer->transform(input);
        input->x.display();
    }
    return input;
}
