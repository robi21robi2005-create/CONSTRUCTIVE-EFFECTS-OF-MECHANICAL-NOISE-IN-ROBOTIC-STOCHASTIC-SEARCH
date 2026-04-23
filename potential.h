#pragma once
#include <vector>

class Map
{
    public:
        struct Peak
        {
            double x0;
            double y0;
            double amplitude;
            double sigma;
        };

        Map(double x1, double x2, double y1, double y2);
        void add_peak(double x, double y, double A, double S);
        double intensity(double x, double y);
        bool inside(double x, double y);
        void print_map(int N);
        void linear_intensity(double x1, double y1, double x2, double y2);
    private:
        double x_min;
        double x_max;
        double y_min;
        double y_max;
        std::vector<Peak> peaks;
        double generator_function(double x, double y, Peak& peak);
};