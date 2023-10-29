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

const char *path1="../data_files/wirediffusion.csv";

double compute_Diffusion(double length, double time_Duration, double delta_T, double delta_X){

    ofstream create_file(path1);
    ofstream myfile;
    myfile.open(path1);

    // determines discrete compartments needed for our vector
    double discrete_Length = length / delta_X; 

    // initializes vectors 
    vector<double> vec_concentations(discrete_Length, 0); 
    vector<double> vec_concentations_temp(discrete_Length, 0); 

    // definitions and initializations
    double D_t = 0.9;
    double total_diffusion, x_diffusion, y_diffusion;

    // this is just some arbitrary junk I used to make graphing a tad easier
    myfile << "length,";
    for(double length_setter = 0; length_setter < length; length_setter += delta_X){
        myfile << length_setter << ",";
    }
    myfile << "\n"; 

    // setting the initial conditions 
    for(int x = 0; x < discrete_Length; x++){
        double scaling_Factor = 0.1; 
        double temp_Loc = length * (x / discrete_Length); 
        vec_concentations[x] = scaling_Factor * (2 * temp_Loc + 2 * sin(M_PI * temp_Loc) + (3 / 4) * sin(5 * M_PI * temp_Loc));
    }

    for(double time_counter = 0; time_counter <= time_Duration; time_counter += delta_T){ 

        // hard clamps position 0 to 0.1 and position L to 0 (simulating open end) 
        vec_concentations[0] = 0.1; 
        vec_concentations[vec_concentations.size() - 1] = 0; 

        // 
        myfile << "y" << time_counter << ","; 

        for(int x = 0; x < discrete_Length; x++){

            myfile << vec_concentations[x] << ","; 

            // calculating diffusion via second derivative
            if((x >= 1) && (x < discrete_Length - 1)){
                x_diffusion = delta_T * delta_X * D_t * (vec_concentations[x + 1] - (2 * vec_concentations[x]) + vec_concentations[x - 1]);
            }
            else if(x == 0){ // used for edge case at position 0
                x_diffusion = delta_T * delta_X * D_t * (vec_concentations[x + 1] - (vec_concentations[x]));
            }
            else if(x == discrete_Length - 1){ // used for edge case at position L
                x_diffusion = delta_T * delta_X * D_t * (vec_concentations[x - 1] - (vec_concentations[x]));
            }
            else{ // just in case we go out of bounds 
                cout << "something is quite bad" << endl;
            }

            vec_concentations_temp[x] = vec_concentations[x] + x_diffusion; // updating positions
        }

        myfile << "\n"; 
        vec_concentations = vec_concentations_temp; // setting vec for next time point
    }
    return(0);
}


int main(void) {
    cout << "Begin" << endl;

    compute_Diffusion(1, 100000, 10, 0.01); // length, time, delta t, delta x 

    cout << "End" << endl;
}