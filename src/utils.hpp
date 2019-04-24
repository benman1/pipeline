#pragma once

#include <chrono>
#include <random>
#include <cstdlib>


namespace utils {

    std::default_random_engine random_generator;
    std::normal_distribution<double> distribution (0.0, 1.0);
    std::uniform_real_distribution<double> unif(0.0, 1.0);

    // Utility function in order to make sure that 
    // random numbers are generated consistently; 
    // This should be called once, in main
    void init_rand_gen(unsigned seed) {
        random_generator.seed(seed);
        srand(seed);
    }

    void init_rand_gen() {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        random_generator.seed(seed);
        srand(seed);
    }


    int random(int min, int max) {
        return (rand() % max) + min;
    }

    // single random number between 0 and 1
    double random() {
        return unif(random_generator);
    }

    double randn() {
        return distribution(random_generator);
    }

    // truncated normal distribution
    double trunc_randn() {
        double r = randn();
        if (r > 2.0) return 2.0;
        if (r < -2.0) return -2.0;
        return r;
    }
}
