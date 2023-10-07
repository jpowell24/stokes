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

const char *path1="../data_files/latticewalk.csv"; // the file we will output data to

double calculate_diffusion(double time_Duration, double delta_T, double delta_Position){
    ofstream create_file(path1); // opens / creates our excel file
    ofstream myfile;
    myfile.open(path1);

    srand ( time(NULL) ); // seeds our random number with the current time (i.e., new seed each run)

    int total_Space = 1000; // defines total vetor length
    double delta_X = 0; // amount that x position changes by
    double delta_Y = 0; // amount that y position changes by


    // double start_X = (total_Space/2) - 1;  
    // double start_Y = (total_Space/2) - 1;

    double start_X = 0; // defines starting coordinate as 0,0---but can be any coordinate
    double start_Y = 0;

    double temp_X = start_X; // variable to store object position in x
    double temp_Y = start_Y; // variable to store object position in y

    myfile << "x,y\n"; // labeling the columns in our excel file
    for(double i = 0; i < time_Duration; i += delta_T){

        myfile << temp_X << "," << temp_Y << "\n"; // writing x and y positions to excel file

        double switch_x_Ramdom = (float) rand()/RAND_MAX; // generate a random number between 0 and 1
        double switch_y_Ramdom = (float) rand()/RAND_MAX;

        if(switch_x_Ramdom > 0.5){ // causing delta_X to increase by 1 if random number is above 0.5
            delta_X = 1;
        }
        else{
            delta_X = -1;
        }

        if(switch_y_Ramdom > 0.5){ // causing delta_Y to increase by 1 if random number is above 0.5
            delta_Y = 1;
        }
        else{
            delta_Y = -1;
        }

        // note that delta_Position is a scaling factor, and has no real value here
        temp_X = temp_X + delta_T*(delta_X * delta_Position); // updating X position
        temp_Y = temp_Y + delta_T*(delta_Y * delta_Position); // updating Y position
    }

    myfile.close(); // closes excel file 
    return (0);
}

int main(void) {
    cout << "Begin" << endl;
    calculate_diffusion(1000, 1, 1); // enter time in ms, enter delta_T in ms, enter delta_Position in microns
    cout << "End" << endl;
}

