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

// defining path1 
const char *path1="../data_files/spherediffusion4.csv";

double random(int x){
    return((float) rand()/RAND_MAX);
}

double calculate_diffusion(double total_time, double delta_T, int trials){

    // creating our output .csv file at location path1
    ofstream create_file(path1);
    ofstream myfile;
    myfile.open(path1);

    default_random_engine generator;
    generator.seed(time(NULL)); // seeded with current time
    normal_distribution<double> distribution(0,1); // generates noise according to standard normal distribution with mean 0, variance 1

    double k_B = 1.38 * pow(10,-23); 
    double temperature = 298; 
    double mu = 1 * pow(10,-3); 
    double a = 1 * pow(10,-6);
    double gamma = 6 * M_PI * mu * a; 
    double D_t = (k_B * temperature) / (gamma);

    double X, Y, Z, delta_X, delta_Y, delta_Z; 
    double start_X, start_Y, start_Z = 0; 

    for(int N = 0; N < trials; N++){ // where N is the trial index
        
        // resetting X and Y for each new trial
        X = start_X; 
        Y = start_Y;
        Z = start_Z;  

        for(int time = 0; time < total_time; time += delta_T){

            double W_X = distribution(generator);
            double W_Y = distribution(generator);
            double W_Z = distribution(generator);             

            delta_X = sqrt(2 * D_t * delta_T) * W_X;
            delta_Y = sqrt(2 * D_t * delta_T) * W_Y;
            delta_Z = sqrt(2 * D_t * delta_T) * W_Z;

            X += delta_X; 
            Y += delta_Y; 
            Z += delta_Z; 

            
        }



    }


    return(0);
}




int main(void) {
    cout << "Begin" << endl; 
    calculate_diffusion(10, 0.01, 1); // enter time in s, enter delta_T in s
    cout << "End" << endl;
}