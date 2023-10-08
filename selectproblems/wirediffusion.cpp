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

default_random_engine generator;
normal_distribution<double> stochastic_opening(0,0.25);

int reset_vecs(int x){

    return(0);
}

double compute_Diffusion(double length, double time_Duration, double delta_T, double delta_X){

    ofstream create_file(path1);
    ofstream myfile;
    myfile.open(path1);

    double discrete_Length = length / delta_X; 

    vector<double> vec_concentations(discrete_Length, 0); 
    vector<double> vec_concentations_temp(discrete_Length, 0); 

    double D_t = 0.9;
    double total_diffusion, x_diffusion, y_diffusion;

    myfile << "length,";
    for(double length_setter = 0; length_setter < length; length_setter += delta_X){
        myfile << length_setter << ",";
    }
    myfile << "\n"; 

    for(int x = 0; x < discrete_Length; x++){
        double scaling_Factor = 0.1; 
        double temp_Loc = length * (x / discrete_Length); 
        vec_concentations[x] = scaling_Factor * (2 * temp_Loc + 2 * sin(2 * M_PI * temp_Loc) + (3 / 4) * sin(2 * M_PI * temp_Loc));
    }

    for(double time_counter = 0; time_counter <= time_Duration; time_counter += delta_T){ 

        vec_concentations[0] = 0.1; 
        vec_concentations[vec_concentations.size() - 1] = 0; 

        myfile << "y" << time_counter << ","; 

        for(int x = 0; x < discrete_Length; x++){

            myfile << vec_concentations[x] << ","; 

            if((x >= 1) && (x < discrete_Length - 1)){
                x_diffusion = delta_T * delta_X * D_t * (vec_concentations[x + 1] - (2 * vec_concentations[x]) + vec_concentations[x - 1]);
            }
            else if(x == 0){
                x_diffusion = delta_T * delta_X * D_t * (vec_concentations[x + 1] - (vec_concentations[x]));
            }
            else if(x == discrete_Length - 1){
                x_diffusion = delta_T * delta_X * D_t * (vec_concentations[x - 1] - (vec_concentations[x]));
            }
            else{
                cout << "something is quite bad" << endl;
            }
            vec_concentations_temp[x] = vec_concentations[x] + x_diffusion; 
        }
        myfile << "\n"; 

        vec_concentations = vec_concentations_temp; 
    }
    
    return(0);
}


int main(void) {
  cout << "Begin" << endl;

  compute_Diffusion(1, 10000, 10, 0.01);

  cout << "End" << endl;
}