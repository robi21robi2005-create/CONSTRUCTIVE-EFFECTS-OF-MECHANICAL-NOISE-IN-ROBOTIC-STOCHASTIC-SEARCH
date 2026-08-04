#include "random.h"
#include <random>
#include <cmath>

// Mersenne Twister engine. Highly reliable for generating unbiased Markov chains
// and preventing unwanted statistical correlations in long simulations.
std::mt19937 gen;

void set_seed(unsigned int seed)
{
    gen.seed(seed);
}

// Generates a uniform float in [0, 1) used to test the Metropolis Boltzmann factor
double random_01()
{
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(gen);
}

// Generates an isotropic scattering angle [0, 2*pi) for the unbiased 2D random walk
double random_angle()
{
    static std::uniform_real_distribution<double> dist(0.0, 2.0 * M_PI);
    return dist(gen);
}

// Generates a random radial displacement in [0, x], controlling the spatial mobility 
// (used both for regular exploration steps d_max and the mechanical noise epsilon)
double random_step(double x)
{
    std::uniform_real_distribution<double> dist(0.0, x);
    return dist(gen);
}
