#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

const char *path1="../data_files/spherediffusion2.csv";

double random(int x){
    return((float) rand()/RAND_MAX);
}


double calculate_diffusion(double time_Duration, double delta_T, double delta_Position, double velocity){
    ofstream create_file(path1);
    ofstream myfile;
    myfile.open(path1);

    srand (time(NULL)); // randomly seeds random generator according to time (i.e., different each run)

    double radius = 0.000001; // in meters
    double mu = 1; 

    double M_r = pow(8 * M_PI * mu * pow(radius,3),-1); // calculating viscous rotational mobility for a sphere
    double K_b = pow(1.38,-23); // Boltzmann's constant (which, by the way, was solved by Schrodinger and not Boltzmann)
    double temperature = 298; // picking standard room temp
    double D_r = M_r * K_b * temperature; // calculating diffusion coefficient of rotation for sphere

    double M_t = pow(6 * M_PI * mu * radius,-1);
    double D_t = M_r * K_b * temperature; // calculating the translational diffusion coefficient

    default_random_engine generator;
    normal_distribution<double> distribution(0,1); // generates noise according to standard normal distribution with mean 0, variance 1

    double test = random(0) * 360; // somehow this is needed to generate a random angle---don't ask

    double angle_Random = random(0) * 360; // generate random angle
    double radian_Random = angle_Random * (M_PI / 180);  // convert to radians

    double delta_X = 0; // amount that x position changes by
    double delta_Y = 0; // amount that y position changes by

    double start_X = 0; // determine starting x at midway
    double start_Y = 0; // determine starting y at midway

    double temp_X = start_X; // variable to store object position in x
    double temp_Y = start_Y; // variable to store object position in y

    myfile << "x,y\n"; // defining x axis
    for(double i = 0; i < time_Duration; i += delta_T){

        normal_distribution<double> distribution(0,1); // noise gaussian
        double noise = distribution(generator); // generate noise

        double angle_noise_Random = random(0) * 360; // generate random angle for noise
        double radian_noise_Random = angle_noise_Random * (M_PI / 180);  // convert to radians 

        double angle_rotation_Random = random(0) * 360; // generate random angle for rotational reorientation
        double radian_rotation_Random = angle_noise_Random * (M_PI / 180);  // convert to radians 

        myfile << temp_X << "," << temp_Y << "\n"; 

        // using the reorientation coefficient to reset the orientation
        radian_Random = radian_Random + sqrt(2 * D_r * delta_T) * radian_rotation_Random;

        delta_X = velocity * delta_T * cos(radian_Random) + sqrt(2 * D_t * delta_T) * noise * cos(radian_noise_Random); // solve change in x
        delta_Y = velocity * delta_T * sin(radian_Random) + sqrt(2 * D_t * delta_T) * noise * sin(radian_noise_Random); // solve change in y

        temp_X = temp_X + (delta_X * delta_Position); // sets new coordinates
        temp_Y = temp_Y + (delta_Y * delta_Position);
    
    }

    myfile.close(); 
    return (0);
}




int main(void) {
    cout << "Begin" << endl; // 0.00002
    calculate_diffusion(10, 0.001, 0.000001, 0.00002); // enter time in ms, enter delta_T in ms, enter delta_Position in microns
    cout << "End" << endl;
}

