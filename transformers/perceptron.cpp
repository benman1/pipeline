#include <iostream>
#include <cereal/archives/binary.hpp>
#include "../pipeline.hpp"
#include "../utils.hpp"

class perceptron : public transformer {
   public:
    DataPoint* transform(DataPoint* input) {
        if (!W) init(input->x.size(), input->y.size());

        Vector preds(size_y, 0.0);
        for (unsigned i = 0; i < size_y; i++) {
            preds.at(i) = bias[i];
            for (unsigned j = 0; j < size_x; j++) {
                preds.at(i) += W[i][j] * input->x.at(i);
            }
        }

        double tot_error = 0;
        if (this->trainable) {
            for (unsigned i = 0; i < size_y; i++) {
                error->at(i) = input->y.at(i) - preds.at(i);
                tot_error += error->at(i);
                bias[i] += learning_rate * error->at(i);
                for (unsigned j = 0; j < size_x; j++) {
                    W[i][j] = learning_rate * error->at(i);
                }
            }
        }
        std::cout << "Total error: " << tot_error << "\n";
        preds.display("Predictions");
        error->display("Error");
        return new DataPoint(input->x, preds);
    }

    float learning_rate = 0.02;
    Vector *error = nullptr;

    perceptron() {
        name = "Perceptron";
    }
    ~perceptron() {
        delete W;
        delete error;
        delete bias;
    }
   protected:
    double **W = nullptr;
    double *bias = nullptr;
    // w_ij is the weight from input neuron j to projection neuron i

    unsigned size_x, size_y;

    void init(unsigned size_x, unsigned size_y) {
        this->size_x = size_x;
        this->size_y = size_y;
        error = new Vector(size_y);

        bias = new double[size_y];
        // W needs to be initialized from random distribution (or similar)
        this->W = new double*[size_y];
        for (unsigned i = 0; i < size_y; i++) {
            W[i] = new double[size_x];
            for (unsigned j = 0; j < size_x; j++) {
                W[i][j] = utils::trunc_randn();
            }
        }
    }
};

extern "C" transformer* transformer_factory() { return new perceptron; }
