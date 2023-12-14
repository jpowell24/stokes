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

const char *path1="../data_files/latticewalk.csv";   // the file we will output data to

// Call via: enter time in ms, enter delta_T in ms, enter delta_Position in microns, enter the number of trials (and or particles)
double calculate_diffusion(double time_Duration, double delta_T, double delta_Position, int trials){
    ofstream create_file(path1);   // opens / creates our excel file
    ofstream myfile;  
    myfile.open(path1);  

    srand ( time(NULL) );   // seeds our random number with the current time (i.e., new seed each run)

    int total_Space = 1000;   // defines total vetor length
    double delta_X = 0;   // amount that x position changes by
    double delta_Y = 0;   // amount that y position changes by

    double start_X = 0;   // defines starting coordinate as 0,0---but can be any coordinate
    double start_Y = 0;  

    if(trials < 2){ // Changes depending if we are interested in a single path, or many
        myfile << "x,y\n";   // labeling the columns in our excel file
    }
    else{
        myfile << "x,meansquared\n";  
    }

    for(int counter = 0;   counter < trials;   counter++){ // this is used to run many simulations, for N particles 

        double temp_X = start_X;   // variable to store object position in x
        double temp_Y = start_Y;   // variable to store object position in y
        double total_X = 0;   
        double average_X = 0;   
        double squared_X = 0;   
        double mean_squared_X = 0;   

        for(double i = 0;   i < time_Duration;   i += delta_T){
            
            if(trials < 2){ // If we are only interested in 1 trials, I'll output the whole path
                myfile << temp_X << "," << temp_Y << "\n";   // writing x and y positions to excel file
            }

            double switch_Ramdom = (float) rand()/RAND_MAX;   // generate a random number between 0 and 1

            if(switch_Ramdom > 0.75){ // causing delta_X to increase by 1 if random number is above 0.5
                delta_X = 1;  
            }
            else if(switch_Ramdom <= 0.75 && switch_Ramdom > 0.5){
                delta_X = -1;  
            }
            else if(switch_Ramdom <= 0.5 && switch_Ramdom > 0.25){ // causing delta_Y to increase by 1 if random number is above 0.5
                delta_Y = 1;  
            }
            else if(switch_Ramdom <= 0.25){
                delta_Y = -1;  
            }
            else{
                cout << "It's broken" << endl;  
            }

            // note that delta_Position is a scaling factor, and has no real value here
            temp_X = temp_X + delta_T*(delta_X * delta_Position);   // updating X position
            temp_Y = temp_Y + delta_T*(delta_Y * delta_Position);   // updating Y position

            total_X += temp_X;   // this is used to compute the average X position later
            squared_X += pow(temp_X,2);   // this captures squared X for later
            mean_squared_X = squared_X / (i + 1);   // finds mean squared X for this timepoint

            // myfile << mean_squared_X << ",";   

        }

        //myfile << "\n";   
        
        if(trials > 1){ // used when we are interested in many simulations, and or, the average of X
            average_X = total_X / (time_Duration / delta_T);  
            myfile << average_X << "," << mean_squared_X << "\n";   
        }

    }

    myfile.close();   // closes excel file 
    return (0);  
}

int main(void) { // I like really short mains :) 
    cout << "Begin" << endl;  
    calculate_diffusion(1000, 1, 1, 10000);   
    cout << "End" << endl;  
}

