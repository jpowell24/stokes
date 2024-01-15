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

double pos_neg(int x){
    double temp = (float) rand()/RAND_MAX;  
    double temp2 = 0;  
    if(temp > 0.5){
        temp2 = 1;  
    }
    else if(temp <= 0.5){
        temp2 = -1;   
    }
    else{
        cout << "Broken!" << endl;  
    }
    return(temp2);  
}


double calculate_diffusion(double time_Duration, double delta_T, int trials){
    ofstream create_file(path1);  
    ofstream myfile;  
    myfile.open(path1);  

    srand (time(NULL));   // randomly seeds random generator according to time (i.e., different each run)

    // double velocity = 20 * pow(10,-6);  

    double velocity = 1;   

    double radius = 0.000001;   // in meters
    double mu = 1;   

    // double M_r = pow(8 * M_PI * mu * pow(radius,3),-1);   // calculating viscous rotational mobility for a sphere
    double K_b = 1.38 * pow(10,-23);   // Boltzmann's constant (which, by the way, was solved by Schrodinger and not Boltzmann)
    double temperature = 298;   // picking standard room temp
    // double D_r = M_r * K_b * temperature;   // calculating diffusion coefficient of rotation for sphere

    double M_t = pow(6 * M_PI * mu * radius,-1);  
    double D_t = M_t * K_b * temperature;   // calculating the translational diffusion coefficient

    default_random_engine generator;  
    normal_distribution<double> distribution(0,1);   // generates noise according to standard normal distribution with mean 0, variance 1

    double test = random(0) * 360;   // somehow this is needed to generate a ra6\mndom angle---don't ask

    double angle_Random = random(0) * 360;   // generate random angle
    double radian_Random = angle_Random * (M_PI / 180);    // convert to radians

    double delta_X = 0;   // amount that x position changes by
    double delta_Y = 0;   // amount that y position changes by

    double start_X = 0;   // determine starting x at midway
    double start_Y = 0;   // determine starting y at midway

    if(trials < 2){ // Changes depending if we are interested in a single path, or many
        myfile << "x,y,t\n";   // labeling the columns in our excel file
    }
    else{
        // myfile << "x,meansquared\n";  
    }

    for(int counter = 0;   counter < trials;   counter++){ // this is used to run many simulations, for N particles 

        double temp_X = start_X;   // variable to store object position in x
        double temp_Y = start_Y;   // variable to store object position in y

        double total_X = 0;   
        double average_X = 0;   
        double squared_X = 0;   
        double mean_squared_X = 0;   

        for(double i = 0;   i < time_Duration;   i += delta_T){

            normal_distribution<double> distribution(0,1);   // noise gaussian
            double noise = distribution(generator);   // generate noise

            double angle_noise_Random = pos_neg(0) * random(0) * 360;   // generate random angle for noise
            double radian_noise_Random = angle_noise_Random * (M_PI / 180);    // convert to radians 

            if(trials < 2){ // If we are only interested in 1 trials, I'll output the whole path
                myfile << temp_X << "," << temp_Y <<  "," << temperature << "\n";   // writing x and y positions to excel file
            }

            delta_X = sqrt(2 * D_t * delta_T) * noise * cos(radian_noise_Random);   // solve change in x
            delta_Y = sqrt(2 * D_t * delta_T) * noise * sin(radian_noise_Random);   // solve change in y

            temp_X = temp_X + delta_X;   // sets new coordinates
            temp_Y = temp_Y + delta_Y;  

            // cout << " , " << D_t << endl;  

            total_X += temp_X;   // this is used to compute the average X position later

            double postition_Temp = pow(pow(temp_X,2) + pow(temp_Y, 2), 0.5);  
            squared_X = pow(postition_Temp,2);   // this captures squared X for later
            mean_squared_X = squared_X / (i + 1);   // finds mean squared X for this timepoint

            myfile << mean_squared_X << ",";   
        }

        if(trials > 1){ // used when we are interested in many simulations, and or, the average of X
            // average_X = total_X / (time_Duration / delta_T);  
            // myfile << average_X << "," << squared_X << "\n";   
        }
        myfile << "\n";  
    } 

    myfile.close();   
    return (0);  
}


int main(void) {
    cout << "Begin" << endl;   // 0.00002
    calculate_diffusion(10, 0.01, 3000);   // enter time in ms, enter delta_T in ms, enter delta_Position in microns
    cout << "End" << endl;  
}

