CONSTRUCTIVE EFFECTS OF MECHANICAL NOISE IN ROBOTIC STOCHASTIC SEARCH

This repository contains the custom object-oriented C++ framework used to investigate
the application of the Metropolis algorithm for localizing global maxima in complex, 
unknown scalar fields.

Overview
While Simulated Annealing and the Metropolis algorithm are highly efficient in 
software-based computational physics, deploying these algorithms on physical 
differential-drive robots introduces unavoidable hardware constraints. A real robotic 
system cannot return exactly to its original position after a rejected step. 
This simulation investigates the impact of this physical noise by treating the 
mechanical error as a forced continuous random walk within an ε-radius. 
Counterintuitively, the introduction of this mechanical noise acts as a constructive 
catalyst against static entrapment, demonstrating macroscopic stochastic resonance 
and improving the search algorithm's efficiency.

Code Structure
The simulation is divided into core physical components:

main.cpp: The primary execution script that initializes the pseudo-random 
number generator, sets the thermodynamic and spatial boundaries, and deploys 
the virtual agent into the thermal bath.

potential.h / potential.cpp: Defines the continuous two-dimensional potential surface 
(the energy landscape). The scalar field is constructed using a superposition of 
Gaussian functions to deliberately generate local and global maxima for rigorous testing.

random.h / random.cpp: The stochastic engine driving the Monte Carlo simulation. 
It utilizes the Mersenne Twister engine to prevent unwanted statistical correlations 
during long Markov chain generation.

robot.h / robot.cpp: Contains the core physics logic for the autonomous agent. 
It evaluates the thermodynamic transition probabilities using a modified Metropolis 
acceptance criterion. Crucially, it implements the non-ideal robotic behavior by forcing
a localized diffusion step (simulating mechanical noise, ε) whenever a move 
is rejected.

Input and Output
The simulation reads initial physical constraints, the mechanical error 
parameter (ε), the fictitious temperature (T), and the maximum 
step size (dₘₐₓ) from an input file named test.txt.

The spatial trajectory of the continuous random walk is exported to road.txt.

The final coordinates and the measured scalar field intensity are logged in 
simulation.txt to evaluate convergence on the global maximum.  A 1D diagonal slice 
of the potential field is generated in output_linear_intensity.txt to analytically 
validate the local topography and potential barriers.
