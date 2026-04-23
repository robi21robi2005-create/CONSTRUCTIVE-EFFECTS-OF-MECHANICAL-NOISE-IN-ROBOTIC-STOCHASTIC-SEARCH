#include "random.h"
#include <random>
#include <cmath>

std::mt19937 gen;

void set_seed(unsigned int seed)
{
    gen.seed(seed);
}

double random_01()
{
    static std::uniform_real_distribution<double> dist(0.0, 1.0);   // static, hogy a dist csak egyszer jojjon letre
    return dist(gen);
}

double random_angle()
{
    static std::uniform_real_distribution<double> dist(0.0, 2.0 * M_PI);
    return dist(gen);
}

double random_step(double x)
{
    std::uniform_real_distribution<double> dist(0.0, x);
    return dist(gen);

}