#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <random>
// #include <Eigen/Dense>

// using namespace Eigen;
using namespace std;

const char *path1="data_files/plot.csv";

int make_file(int x){
    ofstream create_file("data_files/plot.csv");
    ofstream myfile;
    myfile.open("data_files/plot.csv");

    int x_range, y_range; 
    double index;

    double a = 1; 
    double U = 1; 
    double r; 
    double velocity_x, velocity_y; 

    index = 0.1; 
    x_range = 5;
    y_range = 5;

    myfile << "i"  << "," << "j" << "," << "u"  << "," << "v" << "\n";
    for(double i = -0.5*x_range; i <= 0.5*x_range; i += index){
        for(double j = -0.5*y_range; j <= 0.5*y_range; j += index){
            r = pow((pow(i,2)*pow(j,2)),0.5);

            velocity_x = (0.75*a)*(U/r + (U*i)/pow(r,3)) + (0.25*pow(a,3))*(U/pow(r,3) - (3*U*i)/(pow(r,5)));
            velocity_y = (0.75*a)*(U/r) + (0.25*pow(a,3))*(U/pow(r,3));

            double normalized_x = log(velocity_x);
            double normalized_y = log(velocity_y);

            if((pow(pow(i,2) + pow(j,2), 0.5) > a) && velocity_x < 500 && velocity_y < 500){
                myfile << i  << "," << j << "," << normalized_x  << "," << normalized_y << "\n";
            }
        }
    }

    cout << "ran" << endl;

    myfile.close();

    return(0);
}

int main(void) {
    cout << "Begin" << endl;

    make_file(0);

    cout << "End" << endl;
}