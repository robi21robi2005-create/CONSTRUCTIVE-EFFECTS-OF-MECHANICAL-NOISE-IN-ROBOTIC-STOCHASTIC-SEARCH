#pragma once
#include <vector>

class Map
{
    public:
    	// Defines a single localized source (Gaussian peak) in the scalar field
        struct Peak
        {
            double x0;
            double y0;
            double amplitude; // The peak intensity (effective attractive force)
            double sigma; // The spatial spread (variance) determining the basin of attraction
        };

        Map(double x1, double x2, double y1, double y2);
        void add_peak(double x, double y, double A, double S);
        
        // Returns the superposition of the field intensity V(x,y) at a specific coordinate
        double intensity(double x, double y);
        
        // Checks if the agent remains within the defined physical boundaries
        bool inside(double x, double y);
        void print_map(int N);
        void linear_intensity(double x1, double y1, double x2, double y2);
    private:
        double x_min;
        double x_max;
        double y_min;
        double y_max;
        std::vector<Peak> peaks; // Stores the multiple local extrema
        
        // The mathematical generator for the Gaussian distribution
        double generator_function(double x, double y, Peak& peak);
};
