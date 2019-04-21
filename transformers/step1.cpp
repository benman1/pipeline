#include "../pipeline.hpp"

class multiplier : public transformer {
   public:
    DataPoint* transform(DataPoint* input) {
        for (unsigned i = 0; i < input->x.size(); i++) {
            input->x[i] *= 5.0;
        }
        return input;
    }
    multiplier() {
        name = "Multiplier";
    }
};

extern "C" transformer* transformer_factory() { return new multiplier; }
