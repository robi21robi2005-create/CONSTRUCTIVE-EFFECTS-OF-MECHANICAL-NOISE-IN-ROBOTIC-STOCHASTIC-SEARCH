#pragma once

void set_seed(unsigned int seed);
double random_01();    // Uniform sampling between [0, 1] for the Boltzmann probability check
double random_angle(); // Uniform angular sampling for spatial exploration
double random_step(double x); // Uniform radial step sampling up to a characteristic length
