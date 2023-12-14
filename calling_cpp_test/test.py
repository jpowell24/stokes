# for calling cpp
import ctypes
from ctypes import CDLL, POINTER
from ctypes import c_size_t, c_double
import pathlib

# for graphing
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

# for general use
import math

clibrary = ctypes.CDLL("test1.so");    # dynamic link library

# this seems useful: 
# https://asiffer.github.io/posts/numpy/

cpp_function1 = clibrary.func;   

cpp_function1.argtypes = [ctypes.c_int];   
cpp_function1.restype = ctypes.c_int;   # note: in fact, `restype` must actually be singlar here

count_to = 1000000000;   
# z = cpp_function1(count_to);   

# print(z);   

ND_POINTER_1 = np.ctypeslib.ndpointer(dtype=np.float64, 
                                      ndim=1,
                                      flags="C")


cpp_function2 = clibrary.print_array;   


cpp_function2.argtypes = [ND_POINTER_1, ctypes.c_double];   
cpp_function2.restype = ctypes.POINTER(ctypes.c_double);   

# create array X = [1 1 1 1 1]
X = np.ones(5);   
# call function

arr = [];   

cpp_function2(X, X.size);   

mat = cpp_function2(X, X.size);   

list = mat[:X.size]

arr = np.array(list);   

print(mat[1]);   
print(list);   
print(arr);   

clibrary.free_memory(mat);   


