#include "random.h"
#include "potential.h"
#include "robot.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <filesystem>

int main()
{
    set_seed(11);
    double x, y, e, t, d;
    int N_robot, N_field, N_sim, N_step;
    double x_min, x_max, y_min, y_max;
    double x1, y1, a1, s1, x2, y2, a2, s2;
    std::ifstream fin_test("D:\\Egyetem\\szakdolgozat\\input\\test.txt");
    if(!fin_test)
    {
        std::cout << "error while opening: |test.txt|";
        return 1;
    }
    fin_test >> x >> y >> d >> N_robot >> N_field >> N_sim >> N_step >> x_min >> x_max >> y_min >> y_max >> x1 >> y1 >> a1 >> s1 >> x2 >> y2 >> a2 >> s2 >> t >>e;
    Map map(x_min, x_max, y_min, y_max);
    map.add_peak(x1, y1, a1, s1);
    map.add_peak(x2, y2, a2, s2);
    Robot robot(x, y, e, t, d);
    std::ofstream fout ("simulation.txt");
    robot.simulation(map, N_robot, fout);
    std::string filename = "road.txt";
    map.print_road(filename);
    map.linear_intensity(x_min, y_max, x_max, y_min);
    return 0;
}
