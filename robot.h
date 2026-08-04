#pragma once
#include <vector>
#include <string>

class Map;

class Robot
{
    public:
		// Spatial coordinates defining the microstate of our agent
        struct Position
        {
            double x;
            double y;
        };
        
        // Constructor setting initial conditions: Position, mechanical error (epsilon), 
        // fictitious temperature (T), and maximum displacement (d_max)
        Robot(double x0, double y0, double ERR, double TEMP, double STLE);
        Position get_position();
        
        // Main execution of the Monte Carlo Markov Chain
        void simulation(Map& map, int N, std::ofstream& fout);
        void print_road(std::string filename);
        void print_intensity(Map& map, std::string filename);
        void print_randomwalk(int N_sim, int N_step, Map& map, double x0, double y0); 
    
    private:

        Position pos;
        double error; // Epsilon (mechanical inaccuracy inducing forced diffusion)
        double temperature; // Fictitious temperature driving the stochastic resonance
        double step_length; // d_max, dictates spatial resolution of the gradient mapping
        
        std::vector<Position> pos_list; // History of the visited states
        
        // Proposes a new trial state in the phase space
        Position new_pos(Position& old_position);
        
        // Evaluates thermodynamic transition probability
        bool metropolis(double old_potential, double new_potential);
        
        // Executes a single Monte Carlo step (trial + evaluation + structural noise)
        void step(Map& map);
};
