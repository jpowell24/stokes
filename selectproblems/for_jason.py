import numpy as np
import matplotlib.pyplot as plt

def calculate_diffusion(total_time, delta_T):

    time_val = 0;   

    # defining variables
    D_t = 250 * pow(10, -12);   

    temp_X, delta_X = 0, 0;   
    start_X = 0;   

    # starting point defined as (start_X, start_Y, start_Z)
    X = np.array([start_X]);   

    # defining starting position of the particle
    temp_X = start_X;   

    for time in np.arange(0, total_time - delta_T, delta_T): 
        if temp_X < 0.1 * pow(10,-6) and temp_X > -0.1 * pow(10,-6):
            # randomly sampling noise in Gaussian distrib. with mean 0 and variance 1
            W_X = np.random.normal(0, 1);              

            # solving change in position for each dimension
            delta_X = np.sqrt(2 * D_t * delta_T) * W_X;   

            # using a temporary variable to track position
            temp_X += delta_X;   

            # appending new position to arrays storing position over time
            X = np.append(X, [temp_X]);   
        else: 
            time_val = time;   
            return X, time_val, D_t;   # returning coordinates and diffusion coefficient (for comparison later)

    return X, time_val, D_t;   # returning coordinates and diffusion coefficient (for comparison later)

trials = 1000;   
total_time = 20 * pow(10,-6);   
delta_T = 1 * pow(10,-8);   

stop_times = [];   # list of times

# running function <trials> times in order to gather average displacement values across random trials
for N in range(0, trials, 1):
    X, time_val, D_t = calculate_diffusion(total_time, delta_T);   

    if N == 0: # necessary to match all_X dimensions in subsequent N
        stop_times = time_val;   
    else:
        stop_times = np.vstack((stop_times, time_val));   # adding new vectors (X) to rows of all_X

plt.plot(np.linspace(1, trials, trials), stop_times);   
plt.xlabel('trail');   
plt.ylabel('stop time');   

print(str(np.mean(stop_times)) + " seconds")

plt.tight_layout();   
plt.show();   