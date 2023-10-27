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

double calculate_diffusion(double time_Duration, double delta_T, int trials){
    ofstream create_file(path1);
    ofstream myfile;
    myfile.open(path1);

    srand ( time(NULL) );

    double delta_X = 0; // amount that x position changes by
    double delta_Y = 0; // amount that y position changes by
    double delta_Theta = 0; // amount that y position changes by

    double start_X = 0;
    double start_Y = 0;
    double start_Theta = 0;

    double velocity = 10 * pow(10,-6) *  delta_T; 
    double x_velocity = velocity * cos(1); 
    double y_velocity = velocity * sin(1); 

    if(trials < 2){ // Changes depending if we are interested in a single path, or many
        myfile << "time,x,y,t,squared\n"; // labeling the columns in our excel file
    }
    else{
        myfile << "x\n";
    }

    for(int counter = 0; counter < trials; counter++){
        
        double temp_X = start_X; // variable to store object position in x
        double temp_Y = start_Y; // variable to store object position in y
        double temp_Theta = start_Theta; // variable to store orientation
        double total_X = 0; 
        double average_X = 0; 
        double squared_X = 0; 
        double mean_squared_X = 0; 

        for(double i = 0; i < time_Duration; i += delta_T){
            
            double mu = 1;
            double a = 1; 
            double Kb = 1.381 * pow(10,-23); 
            // double T = 250 * sin(M_PI * i / 100) + 298; 
            double T = 298; 
            // double D_c = (Kb * T) / (6 * M_PI * mu * a); 
            double D_c = 0.1 * delta_T;
            double D_r = 0.05 * delta_T; 

            if(trials < 2){ // If we are only interested in 1 trials, I'll output the whole path
                myfile << i << "," << temp_X << "," << temp_Y << "," << T << "," << squared_X << "\n"; // writing x and y positions to excel file
            }

            double angle_Random = (float) rand()/RAND_MAX * 360; 
            double radian_Random = angle_Random * (M_PI / 180);  

            double angle_orientation_Random = (float) rand()/RAND_MAX * 360; 
            double radian_orientation_Random = angle_orientation_Random * (M_PI / 180);  

            delta_Theta = radian_orientation_Random * pow(delta_T,0.5) * pow(2 * D_r,0.5);
            temp_Theta = temp_Theta + (M_PI / 180) + delta_Theta;

            // cout << delta_Theta << " , " << pow(delta_T,0.5) * pow(2 * D_r,0.5) << " , " << D_r << " , " << D_c << endl;

            delta_X = delta_T * x_velocity * cos(temp_Theta) + cos(radian_Random) * pow(delta_T,0.5) * pow(2 * D_c,0.5);
            delta_Y = delta_T * y_velocity * sin(temp_Theta) + sin(radian_Random) * pow(delta_T,0.5) * pow(2 * D_c,0.5);

            //delta_X = delta_T * x_velocity * cos(temp_Theta);
            //delta_Y = delta_T * y_velocity * sin(temp_Theta);

            // cout << delta_X << "," << delta_Y << endl;

            temp_X = temp_X + (delta_X);
            temp_Y = temp_Y + (delta_Y);
        
            total_X += temp_X; // this is used to compute the average X position later
            double postition_Temp = pow(pow(temp_X,2) + pow(temp_Y, 2), 0.5);
            squared_X = pow(postition_Temp,2); // this captures squared X for later
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

    calculate_diffusion(10, 0.001, 1); // enter time in ms, enter delta_T in ms, enter delta_Position in microns

    cout << "End" << endl;
}

