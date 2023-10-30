import ctypes # for calling cpp

clibrary = ctypes.CDLL("test1.so");  # dynamic link library

cpp_function = clibrary.func; 

cpp_function.argtypes = [ctypes.c_int]; 
cpp_function.restype = ctypes.c_int; # note: in fact, `restype` must actually be singlar here

count_to = 1000000000; 
z = cpp_function(count_to); 

print(z); 


