#include <iostream>

using namespace std;

// Compile / create library via: g++ -fPIC -shared -o test1.so test1.cpp

extern "C" {
    int func(int count_to){

        int num = 0; 

        for(int i = 1; i <= count_to; i++){
            num++;
        }
        return(num);

    }
}

extern "C" {
    double* print_array(double *v, int n){
        for (int i = 0; i < n; i++)
        {
            cout << v[i] << ",";
        }
        cout << "\n";
    return (v); 
    }
}

extern "C"{
    void free_memory(int *arr){
        free(arr);
    }
}
