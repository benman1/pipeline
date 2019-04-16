#include "pipeline.hpp"

class multiplier: public transformer {
    public:
        Vector* transform(Vector* input) {
            for(int i=0; i<input->size; i++) {
                input->array[i] *= 5;
            }
            return input;
        }
};

extern "C" transformer* transformer_factory() {
        return new multiplier;
}
