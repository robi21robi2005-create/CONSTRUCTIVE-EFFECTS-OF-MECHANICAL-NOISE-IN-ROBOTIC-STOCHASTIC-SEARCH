#pragma once
#include <vector>
#include <string>

class Map;

class Robot
{
    public:

        struct Position
        {
            double x;
            double y;
        };
        Robot(double x0, double y0, double ERR, double TEMP, double STLE);
        Position get_position();
        void simulation(Map& map, int N, std::ofstream& fout);
        void print_road(std::string filename);
        void print_intensity(Map& map, std::string filename);
        void print_randomwalk(int N_sim, int N_step, Map& map, double x0, double y0); 
    
    private:

        Position pos;
        double error;
        double temperature;
        double step_length;
        
        std::vector<Position> pos_list;
        Position new_pos(Position& old_position);
        bool metropolis(double old_potential, double new_potential);
        void step(Map& map);
};