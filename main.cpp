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
    //std::vector<double> T(2);
    //std::vector<double> err(101);

    std::ifstream fin_test("D:\\Egyetem\\szakdolgozat\\input\\test.txt");
    if(!fin_test)
    {
        std::cout << "error while opening: |test.txt|";
        return 1;
    }

    /*std::ifstream fin_error("D:\\Egyetem\\szakdolgozat\\input\\error.txt");
    if(!fin_error)
    {
        std::cout << "error while opening: |error.txt|";
        return 3;
    }*/
    fin_test >> x >> y >> d >> N_robot >> N_field >> N_sim >> N_step >> x_min >> x_max >> y_min >> y_max >> x1 >> y1 >> a1 >> s1 >> x2 >> y2 >> a2 >> s2 >> t >>e;
    /*for (int i = 0; i < err.size(); i++)
    {
        fin_error >> err[i];
    }*/

    Map map(x_min, x_max, y_min, y_max);
    map.add_peak(x1, y1, a1, s1);
    map.add_peak(x2, y2, a2, s2);
    //Robot robot(x, y, e, t, d);
    //robot.print_randomwalk(N_sim, N_step, map, x, y);
    /*std::filesystem::create_directory("test_error_fixed_t_0.03");
    for (int i = 0; i < err.size(); i++)
    {
        Robot robot(x, y, err[i], t, d);
        std::ostringstream filename;
        filename << "test_error_fixed_t_0.03/test_" << std::fixed << std::setprecision(3) << t << "_err_" << err[i] << ".txt";
        std::ofstream fout (filename.str());
        if (!fout)
        {
            std::cerr << "Error" << filename.str() << std::endl;
            return 4;
        }
        std::cout<<"T = " << t << " and e = " << err[i] << " is running " << std::endl;
        for (int j = 0; j < N_sim; j++)
        {
            robot.simulation(map, N_robot, fout);
        }
    }*/

    

    /*
    std::ifstream fin_temp ("D:\\Egyetem\\szakdolgozat\\input\\temperature.txt");
    if(!fin_temp)
    {
        std::cout << "error while opening: |temperature.txt|";
        return 2;
    }

    for (int i = 0; i <= T.size(); i++)
    {
        fin_temp >> T[i];
    }
    */
    
    //fin_test >> x >> y >> d >> N_robot >> N_field >> N_sim >> x_min >> x_max >> y_min >> y_max >> x1 >> y1 >> a1 >> s1 >> x2 >> y2 >> a2 >> s2 >> t >> e ;
    

    
    
    //std::cout<<map.intensity(-3,3)<<" "<< map.intensity(3, -3) << std::endl;
    //map.print_map(N_field);
    map.linear_intensity(x_min, y_max, x_max, y_min);
    //Robot robot(x, y, e, t, d);
    //std::ofstream fout ("final_test.txt");
    //std::string fajl1 = "final_road.txt";
    //std::string fajl2 = "final_int.txt";
    //robot.simulation(map, N_robot, fout);
    //robot.print_road(fajl1);
    //robot.print_intensity(map, fajl2);

    /*mastd::filesystem::create_directory("test_error");

    for (int i = 0; i < T.size(); i++)
    {
        for (int j = 0; j < err.size(); j++)
        {
            Robot robot(x, y, err[j], T[i], d);
            std::ostringstream filename;
            filename << "test_error/test_" << std::fixed << std::setprecision(2) << T[i] << "_err_" << err[j] << ".txt";
            std::ofstream fout (filename.str());
            if (!fout)
            {
                std::cerr << "Error" << filename.str() << std::endl;
                return 4;
            }
            std::cout<<"T = " << T[i] << " and e = " << err[j] << " is running " << std::endl;
            for (int j = 0; j < N_sim; j++)
            {
                robot.simulation(map, N_robot, fout);
            }
        }
        
    }ma*/
    
    //robot.print_road(fajl1);
    //robot.print_intensity(map, fajl2);
    //return 0;





    /*std::ifstream fin_seed("D:/Egyetem/szakdolgozat/map_input_files/seed.txt");
    if(!fin_seed)
    {
        std::cout << "error while opening: |seed.txt|";
        return 4;
    }
    int s;
    fin_seed >> s; 14 16
    fin_seed.close();

    set_seed(s);
    
    std::ofstream fout_01("D:/Egyetem/szakdolgozat/map_output_files/011.txt");
    std::ofstream fout_an("D:/Egyetem/szakdolgozat/map_output_files/01.txt");

    for (int i = 0; i < 10000; i++ )
    {
        fout_01 << std::fixed << std::setprecision(6) << random_01() << " ";
    }
    fout_01.close();
    fout_an.close();
    std::cout << "numbers are ready";*/

    /*std::ifstream fin_map("D:/Egyetem/szakdolgozat/map_input_files/map_in.txt");
    std::ifstream fin_peak1("D:/Egyetem/szakdolgozat/map_input_files/peak1.txt");
    std::ifstream fin_peak2("D:/Egyetem/szakdolgozat/map_input_files/peak2.txt");

    if (!fin_map)
    {
        std::cout<< "error while opening: |map_in.txt|";
        return 1;
    }
    if (!fin_peak1)
    {
        std::cout<< "error while opening: |peak1.txt|";
        return 2;
    }
    if (!fin_peak2)
    {
        std::cout<< "error while opening: |peak2.txt|";
        return 3;
    }

    int N_map;
    double x_min, x_max, y_min, y_max;
    double x1, y1, A1, S1;
    double x2, y2, A2, S2;

    fin_map >> N_map >> x_min >> x_max >> y_min >> y_max;
    fin_map.close();

    fin_peak1 >> x1 >> y1 >> A1 >> S1;
    fin_peak2 >> x2 >> y2 >> A2 >> S2;

    Map map(x_min, x_max, y_min, y_max);
    map.add_peak(x1, y1, A1, S1);
    map.add_peak(x2, y2, A2, S2);

    map.print_map(N_map);
    */    return 0;
}