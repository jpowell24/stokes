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

const char *path1="../data_files/activelatticewalk.csv";

double calculate_diffusion(double time_Duration, double delta_T, double delta_Position, int trials){
    ofstream create_file(path1);
    ofstream myfile;
    myfile.open(path1);

    srand ( time(NULL) );

    double delta_X = 0; // amount that x position changes by
    double delta_Y = 0; // amount that y position changes by

    double start_X = 0;
    double start_Y = 0;

    if(trials < 2){ // Changes depending if we are interested in a single path, or many
        myfile << "x,y\n"; // labeling the columns in our excel file
    }
    else{
        myfile << "x\n";
    }

    for(int counter = 0; counter < trials; counter++){
        
        double temp_X = start_X; // variable to store object position in x
        double temp_Y = start_Y; // variable to store object position in y
        double total_X = 0; 
        double average_X = 0; 
        double squared_X = 0; 
        double mean_squared_X = 0; 

        for(double i = 0; i < time_Duration; i += delta_T){
            
            double velocity = 20 * pow(10,-6);
            double D_c = 0.1 * pow(10,-6); 
            double D_r = 0.05; 

            if(trials < 2){ // If we are only interested in 1 trials, I'll output the whole path
                myfile << temp_X << "," << temp_Y << "\n"; // writing x and y positions to excel file
            }

            double angle_Random = (float) rand()/RAND_MAX * 360; 
            double radian_Random = angle_Random * (M_PI / 180);  

            double rotation_angle_Random = (float) rand()/RAND_MAX * 360; 
            double rotation_radian_Random = angle_Random * (M_PI / 180);  

            delta_X = velocity * cos(rotation_radian_Random) * pow(delta_T,0.5) * pow(2 * D_c,0.5) + cos(radian_Random) * pow(delta_T,0.5) * pow(2 * D_c,0.5);
            delta_Y = velocity * sin(rotation_radian_Random) * pow(delta_T,0.5) * pow(2 * D_c,0.5) + sin(radian_Random) * pow(delta_T,0.5) * pow(2 * D_c,0.5);

            // cout << delta_X << "," << delta_Y << endl;

            temp_X = temp_X + delta_T * (delta_X * delta_Position);
            temp_Y = temp_Y + delta_T * (delta_Y * delta_Position);
        
            total_X += temp_X; // this is used to compute the average X position later
            squared_X += pow(temp_X,2); // this captures squared X for later
            mean_squared_X = squared_X / (i + 1); // finds mean squared X for this timepoint

            // myfile << mean_squared_X << ","; 
        }

        //myfile << "\n"; 

        if(trials > 1){ // used when we are interested in many simulations, and or, the average of X
            average_X = total_X / (time_Duration / delta_T);
            myfile << average_X << "\n"; 
        }
    }

    myfile.close(); 
    return (0);
}

int main(void) {
    cout << "Begin" << endl;

    calculate_diffusion(10, 0.01, 1 * pow(10,-6), 10000); // enter time in s, enter delta_T in s, enter delta_Position in m

    cout << "End" << endl;
}

