#include "random.h"
#include "potential.h"
#include "robot.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <filesystem>

int main()
{
	// Initialize the pseudo-random number generator (PRNG) seed for reproducibility.
    set_seed(11);
    
    // Physical and simulation control parameters
    double x, y, e, t, d; // e = mechanical error (epsilon), t = fictitious temperature (T), d = max step size (d_max)
    int N_robot, N_field, N_sim, N_step; // Ensemble size and Monte Carlo steps limits
    double x_min, x_max, y_min, y_max; // Spatial boundaries of our system
    
    // Parameters for the Gaussian potential peaks: 
    // x,y coordinates, Amplitude (a), and Variance (s^2)
    double x1, y1, a1, s1, x2, y2, a2, s2;
    std::ifstream fin_test("D:\\Egyetem\\szakdolgozat\\input\\test.txt");
    if(!fin_test)
    {
        std::cout << "error while opening: |test.txt|";
        return 1;
    }
    
    // Read the thermodynamic and spatial configuration from the input file
    fin_test >> x >> y >> d >> N_robot >> N_field >> N_sim >> N_step >> x_min >> x_max >> y_min >> y_max >> x1 >> y1 >> a1 >> s1 >> x2 >> y2 >> a2 >> s2 >> t >>e;
    
    // Initialize the two-dimensional scalar field (potential surface)
    Map map(x_min, x_max, y_min, y_max);
    map.add_peak(x1, y1, a1, s1);
    map.add_peak(x2, y2, a2, s2);
    
    // Deploy the virtual agent into the field at starting coordinates (x,y)
    // subject to the mechanical error (e), fictitious temperature (t), and maximum displacement (d)
    Robot robot(x, y, e, t, d);
    std::ofstream fout ("simulation.txt");
    
    // Run the main Monte Carlo simulation to search for the global maximum
    robot.simulation(map, N_robot, fout);
    
    // Output the spatial trajectory (the random walk path) of the agent
    std::string filename = "road.txt";
    map.print_road(filename);
    
    // Export a 1D cut of the potential landscape to verify the potential barrier Delta V
    map.linear_intensity(x_min, y_max, x_max, y_min);
    return 0;
}
