#include "pipeline.hpp"


void Vector::display() {
    for(int i=0; i<this->size; i++) {
        std::cout << this->array[i] << " ";
    }
    std::cout << "\n";
    return;
}

STEP_FN Pipeline::load_step(const char* file_name, const char* function_name) {
    using std::cout;
    using std::cerr;

    cout << "Loading step function " << function_name << " from " << file_name << "\n";

    void* handle = dlopen(file_name, RTLD_LAZY);

    if(!handle) {
        cerr << "Can't open " << file_name << "\n";
        exit(1);
    }

    dlerror();
    STEP_FN hello = (STEP_FN) dlsym(handle, function_name);
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol " << function_name << " and cast it to STEP_FN \n";
        dlclose(handle);
        exit(1);
    }

    return hello;
}

void Pipeline::add(const char* file_name, const char* function_name) {
    STEP_FN step1 = load_step(file_name, function_name);
    this->pipeline.push_back(step1);
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

Vector* Pipeline::exe(Vector* input) {
    input->display();

    for(STEP_FN step: this->pipeline) {
        input = step(input);
    }
    std::cout << "\nafter... \n";
    input->display();
    return input;
}