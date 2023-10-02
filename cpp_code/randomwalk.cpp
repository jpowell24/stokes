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

const char *path1="../data_files/randomwalk.csv";

double calculate_diffusion(double time_Duration, double delta_T){
    ofstream create_file(path1);
    ofstream myfile;
    myfile.open(path1);

    srand ( time(NULL) );

    int total_Space = 100; // defines total vetor length
    int delta_X = 0; // amount that position changes by

    //myfile << "0";
    myfile << "time" << ","; // defining x axis
    for(int i = 0; i < time_Duration; i += delta_T){
        myfile << i << ","; 
    }
    myfile << "\n";

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    vector<int> position(total_Space - 1, 0); // initialize vector we use as our 1D landscape
    position[(total_Space / 2) - 1] = 1; // sets initial position at midway

    int temp_Position = 0; // variable to store object position
    for(int i = 0; i < position.size(); i++){ // used to find initial position
        if(position[i] == 1){
            temp_Position = i; 
        }
    }

    myfile << "object" << ","; // defining x axis
    for(double i = 0; i < time_Duration; i += delta_T){
        double temp_Random = (float) rand()/RAND_MAX; 
        if(temp_Random > 0.5){
            delta_X = 1; 
        }
        else if(temp_Random <= 0.5){
            delta_X = -1; 
        }
        else{
            cout << "Something bad happened" << endl;
        }

        if(temp_Position < position.size()){
            position[temp_Position] = 0; 
            temp_Position = temp_Position + delta_X; 
            position[temp_Position] = 1; 
        }
        else{ 
            temp_Position = position.size() - 1;
        }
        
        myfile << temp_Position << ","; 

    }


    myfile.close(); 
    return (0);
}




int main(void) {
    cout << "Begin" << endl;

    calculate_diffusion(100, 1); // enter time in ms, enter delta_T in ms

    cout << "End" << endl;
}

