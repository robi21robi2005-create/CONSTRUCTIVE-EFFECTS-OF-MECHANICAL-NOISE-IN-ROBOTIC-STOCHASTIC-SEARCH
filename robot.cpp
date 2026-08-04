#include "random.h"
#include "potential.h"
#include "robot.h"
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>

Robot::Robot(double x0, double y0, double ERR, double TEMP, double STLE)
{
    pos.x = x0;
    pos.y = y0;
    error = ERR; // Maps to the physical epsilon parameter (forced continuous diffusion)
    temperature = TEMP; // Fictitious thermal energy T (k_B = 1)
    step_length = STLE; // Bounds the maximum jump size d_max
}

Robot::Position Robot::get_position()
{
    return pos;
}

// Executes a complete Monte Carlo run of N independent steps
void Robot::simulation(Map& map, int N, std::ofstream& fout)
{
    pos_list.clear();
    pos_list.push_back(pos);
    for (int i = 0; i < N; i++)
    {
        step(map);
    }
    
    // Record the final state's intensity to evaluate convergence on the global maximum
    fout << std::fixed << std::setprecision(6) << pos_list[pos_list.size()-1].x << " " << pos_list[pos_list.size()-1].y << " " << map.intensity(pos_list[pos_list.size()-1].x, pos_list[pos_list.size()-1].y) << std::endl;
}

// Dumps the coordinate history to trace the 2D random walk trajectory
void Robot::print_road(std::string filename)
{
    std::ofstream fout_road(filename);

    for (int i = 0; i < pos_list.size(); i++)
    {
        fout_road << std::fixed << std::setprecision(6) << pos_list[i].x << " " << std::fixed << std::setprecision(6) << pos_list[i].y << std::endl;
    }

    std::cout << "The road output for | " << filename << " | is ready" << std::endl;
}

void Robot::print_intensity(Map& map, std::string filename)
{
    std::ofstream fout_intensity(filename);

    for (int i = 0; i < pos_list.size(); i++)
    {
        fout_intensity << i << " " << std::fixed << std::setprecision(6) << map.intensity(pos_list[i].x, pos_list[i].y) << std::endl;
    }

    std::cout << "The intensityfor | " << filename << " | is ready" << std::endl;
}

// Gathers statistics on the pure random walk component (calculating mean squared displacement <r^2>)
void Robot::print_randomwalk(int N_sim, int N_step, Map& map, double x0, double y0)
{
    std::ofstream fout_walk ("random_walk.txt");
    std::vector <double> values(N_step, 0.0);
    for (int i = 0; i < N_sim; i++)
    {
        std::cout << "Simulation: " << i << "is running" << std::endl;
        pos.x = x0;
        pos.y = y0;
        for (int j = 0; j < N_step;j++)
        {
            step(map);
            Position posi = get_position();
            double dx = pos.x - x0;
            double dy = pos.y - y0;
            double r = dx*dx + dy*dy;
            values[j] += r; // Accumulating r^2 to track the spatial diffusion rate over time
        }
    }
    for (int i = 0; i < values.size(); i++)
    {
        values[i] = values[i] / (double)N_sim; // Ensemble average
        fout_walk << i << " " << values[i] << std::endl;
    }
}

// Proposes a new microstate via a continuous isotropic random jump from the current coordinates
Robot::Position Robot::new_pos(Position& old_position)
{
    Position new_position;

    double actual_step_length = random_step(step_length);
    double actual_angle = random_angle();

    new_position.x = old_position.x + actual_step_length * cos(actual_angle);
    new_position.y = old_position.y + actual_step_length * sin(actual_angle);

    return new_position;
}


// The core thermodynamic acceptance rule.
// We seek the MAXIMUM of the field, so a potential INCREASE is favorable.
bool Robot::metropolis(double old_potential, double new_potential)
{
	// The Boltzmann factor. We use k_B = 1, so the fictitious T scales directly with the potential V.
    // Note: Delta V here is (new - old). If new < old, the exponent is negative, returning a fractional probability.
    double P = exp((new_potential - old_potential) / temperature);

    if (new_potential > old_potential)
    {
    	// Unconditionally accept moves migrating UP the local gradient (seeking the maximum)
        return true;
    }

    else if (random_01() <= P)
    {
    	// Stochastic acceptance: randomly accept a move DOWN the gradient to escape local topological traps
        return true;
    }

    else
    {
    	// Reject the unfavorable move
        return false;
    }
}

// Orchestrates a single trial move, evaluates it, and applies mechanical noise if rejected
void Robot::step(Map& map)
{
    Position old_positon = pos;
    double old_potential = map.intensity(old_positon.x, old_positon.y);
    Position new_position = new_pos(old_positon);

    if(map.inside(new_position.x, new_position.y))
    {
        double new_potential = map.intensity(new_position.x, new_position.y);
        
        // If the Metropolis criterion accepts the jump, update spatial memory and exit
        if(metropolis(old_potential, new_potential))
        {
            pos = new_position;
            pos_list.push_back(pos);
            return;
        }
    }
    // --- NON-IDEAL BEHAVIOR (MECHANICAL NOISE) ---
    // If the step is rejected (or hits the boundary), an ideal software agent perfectly returns to 'old_position'.
    // A physical robot cannot. We introduce forced, localized continuous diffusion representing positional inaccuracy.
    else
    {
        double error_step_length = random_step(error); // Scatter within a circle of radius epsilon
        double error_angle = random_angle();
        Position error_position;
        error_position.x = old_positon.x + error_step_length * cos(error_angle);
        error_position.y = old_positon.y + error_step_length * sin(error_angle);
        
        // If the noise-induced slip stays within bounds, update the state.
        // This structural fluctuation acts as a constructive catalyst to prevent static entrapment.
        if(map.inside(error_position.x, error_position.y))
        {
            pos = error_position;
        }
        else
        {
        	// If the error pushes the agent out of bounds, reset (hard wall constraint)
            pos = old_positon;
        }
        pos_list.push_back(pos);
    }
}




