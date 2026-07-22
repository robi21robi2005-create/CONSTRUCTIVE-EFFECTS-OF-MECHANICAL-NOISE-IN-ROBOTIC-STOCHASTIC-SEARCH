#include "potential.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>

Map::Map(double x1, double x2, double y1, double y2)
{
    x_min = x1;
    x_max = x2;
    y_min = y1;
    y_max = y2;
}

void Map::add_peak(double x, double y, double A, double S)
{
    Peak p;
    p.x0 = x;
    p.y0 = y;
    p.amplitude = A;
    p.sigma = S;
    peaks.push_back(p);
}

double Map::intensity(double x, double y)
{
    double sum = 0.0;
    for (int i = 0; i < peaks.size(); i++)
    {
        sum += generator_function(x, y, peaks[i]);
    }
    return sum;
}

bool Map::inside(double x, double y)
{
    if (x >= x_min && x <= x_max && y >= y_min && y <= y_max)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Map::print_map(int N)
{
    std::ofstream fout("map_one.txt");

    double dx = (x_max - x_min) / (N-1);
    double dy = (y_max - y_min) / (N-1);

    for (int i = 0; i < N; i++)
    {
        double y = y_min + i * dy;

        for (int j = 0; j < N; j++)
        {
            double x = x_min + j * dx;
            fout << std::fixed << std::setprecision(10) << intensity(x, y);
            if(j < N-1)
            {
                fout << " ";
            } 
        }
        fout << '\n';
    }
    fout.close();
    std::cout << "Map is printed successfully";
}

void Map::linear_intensity(double x1, double y1, double x2, double y2)
{
    double d = 0.01;
    std::ofstream fout("output_linear_intensity.txt");
    while (x1 <= x2 && y1 >= y2)
    {
        if (x1<0)
        {
            fout << std::fixed << std::setprecision(6) << -sqrt(x1*x1 + y1*y1) << " " << -intensity(x1,y1) << std::endl;
        }
        else
        {
            fout << std::fixed << std::setprecision(6) << sqrt(x1*x1 + y1*y1) << " " << -intensity(x1,y1) << std::endl;
        }
        x1 = x1 + d;
        y1 = y1 - d;
    }
    fout.close();
}


double Map::generator_function(double x, double y, Peak& p)
{
    double dx = x - p.x0;
    double dy = y - p.y0;
    double I = p.amplitude * exp(-(dx * dx + dy * dy) / (2 * p.sigma * p.sigma));
    return I;
}
