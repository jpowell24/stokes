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

const char *path1="../data_files/targetedwalk2d.csv";

double random(int x){
    return((float) rand()/RAND_MAX);
}


double calculate_diffusion(double time_Duration, double delta_T, double delta_Position){
    ofstream create_file(path1);
    ofstream myfile;
    myfile.open(path1);

    srand (time(NULL)); // randomly seeds random generator according to time (i.e., different each run)

    default_random_engine generator;
    normal_distribution<double> distribution(0,1); // random velocity parameters
    double velocity = distribution(generator); // assign random velocity

    double test = random(0) * 360; // somehow this is needed to generate a random angle---don't ask

    double angle_Random = random(0) * 360; // generate random angle
    double radian_Random = angle_Random * (M_PI / 180);  // convert to radians

    int total_Space = 1000; // defines total vetor length
    double delta_X = 0; // amount that x position changes by
    double delta_Y = 0; // amount that y position changes by

    double start_X = (total_Space/2) - 1; // determine starting x at midway
    double start_Y = (total_Space/2) - 1; // determine starting y at midway

    double temp_X = start_X; // variable to store object position in x
    double temp_Y = start_Y; // variable to store object position in y

    double Dc = 1; // define diffusion coefficient

    myfile << "x,y\n"; // defining x axis
    for(double i = 0; i < time_Duration; i += delta_T){

        normal_distribution<double> distribution(0,1); // noise gaussian
        double noise = distribution(generator); // generate noise

        double angle_noise_Random = random(0) * 360; // generate random angle for noise
        double radian_noise_Random = angle_noise_Random * (M_PI / 180);  // convert to radians 

        // cout << noise << "," << angle_noise_Random << "," << radian_noise_Random << endl;

        myfile << temp_X << "," << temp_Y << "\n"; 
        // cout << "running: " << temp_X << "," << temp_Y << endl;

        delta_X = velocity * delta_T * cos(radian_Random) + sqrt(2 * Dc * delta_T) * noise * cos(radian_noise_Random); // solve change in x
        delta_Y = velocity * delta_T * sin(radian_Random) + sqrt(2 * Dc * delta_T) * noise * sin(radian_noise_Random); // solve change in y

        // cout << delta_X << "," << delta_Y << endl; 

        temp_X = temp_X + (delta_X * delta_Position);
        temp_Y = temp_Y + (delta_Y * delta_Position);
    
    }

    myfile.close(); 
    return (0);
}




int main(void) {
    cout << "Begin" << endl;

    calculate_diffusion(1000, 1, 1); // enter time in ms, enter delta_T in ms, enter delta_Position in microns

    cout << "End" << endl;
}

