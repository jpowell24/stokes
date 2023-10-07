#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
// #include <Eigen/Dense>

// using namespace Eigen;
using namespace std;

const char *path1="../data_files/circularlatticewalk.csv";

double calculate_diffusion(double time_Duration, double delta_T, double delta_Position, int trials){
    ofstream create_file(path1);
    ofstream myfile;
    myfile.open(path1);

    srand ( time(NULL) );

    double radius = 0.000001; // in meters

    double M_r = pow(8 * M_PI * 1 * pow(radius,3),-1); // calculating viscous rotational mobility for a sphere
    double K_b = pow(1.38,-23); // Boltzmann's constant (which, by the way, was solved by Schrodinger and not Boltzmann)
    double temperature = 298; // picking standard room temp
    double D_r = M_r * K_b * temperature;// calculating diffusion coefficient of rotation for sphere

    double delta_X; // amount that x position changes by
    double delta_Y; // amount that y position changes by

    double start_X = 0;
    double start_Y = 0;

    double temp_X = start_X; // variable to store object position in x
    double temp_Y = start_Y; // variable to store object position in y

    myfile << "x,y\n"; // defining x axis
    for(double i = 0; i < time_Duration; i += delta_T){

        myfile << temp_X << "," << temp_Y << "\n"; 
        // cout << "running: " << temp_X << "," << temp_Y << endl;


        double angle_Random = (float) rand()/RAND_MAX * 360; 
        double radian_Random = angle_Random * (M_PI / 180);  

        delta_X = cos(radian_Random);
        delta_Y = sin(radian_Random);

        // cout << delta_X << "," << delta_Y << endl;

        temp_X = temp_X + delta_T*(delta_X * delta_Position);
        temp_Y = temp_Y + delta_T*(delta_Y * delta_Position);
    }

    myfile.close(); 
    return (0);
}

int main(void) {
    cout << "Begin" << endl;

    calculate_diffusion(10, 0.01, 1, 1); // enter time in s, enter delta_T in s, enter delta_Position in meters, enter number of particles 

    cout << "End" << endl;
}

