#include <iostream>
#include <dlfcn.h>
#include "types.hpp"

STEP_FN load_step(const char* file_name, const char* function_name){
    using std::cout;
    using std::cerr;

    cout << "Loading step function " << function_name << " from " << file_name << "\n";

    void* handle = dlopen(file_name, RTLD_LAZY);

    if(!handle) {
        cerr << "Can't open " << file_name << "\n";
        return NULL;
    }

    dlerror();
    STEP_FN hello = (STEP_FN) dlsym(handle, function_name);
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol " << function_name << " and cast it to STEP_FN \n";
        dlclose(handle);
        return NULL;
    }

    return hello;
}