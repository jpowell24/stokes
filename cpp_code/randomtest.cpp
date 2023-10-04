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

const char *path1="../data_files/randomwalk2d.csv"; // the file we are outputting to

double calculate_diffusion(double time_Duration, double delta_T, double delta_Position){
    ofstream create_file(path1);
    ofstream myfile;
    myfile.open(path1);

    srand ( time(NULL) ); // seeding the random number generator with the current time

    int total_Space = 1000; // defines total vetor length
    double delta_X = 0; // amount that x position changes by
    double delta_Y = 0; // amount that y position changes by

    double start_X = (total_Space/2) - 1;  
    double start_Y = (total_Space/2) - 1;

    double temp_X = start_X; // variable to store object position in x
    double temp_Y = start_Y; // variable to store object position in y

    myfile << "x,y\n"; // defining x axis
    for(double i = 0; i < time_Duration; i += delta_T){

        myfile << delta_X << "," << delta_Y << "\n"; 

        double angle_Random = (float) rand()/RAND_MAX * 360; // generating a random angle
        double radian_Random = angle_Random * (M_PI / 180); // converting to radians

        delta_X = cos(radian_Random); // finding change in x
        delta_Y = sin(radian_Random); // finding change in y

        cout << delta_X << "," << delta_Y << endl;    
    }

    myfile.close(); 
    return (0);
}

int main(void) {
    cout << "Begin" << endl;

    calculate_diffusion(1000, 1, 1); // enter time in ms, enter delta_T in ms, enter delta_Position in microns

    cout << "End" << endl;
}

