
#include <iostream>

extern std::string network;

int main()
{
    std::cout << network;
}

std::string network = R"NN(-1 -1  1 -1  1 -1 -1 -1  1  1 -1  1  1  1 -1 -1  1  1 -1 -1 -1 -1 -1 -1  1  1  1  1 -1  1 -1  1  1 -1 -1 -1  1 -1  1  1  1  1  1  1  1 -1 -1 -1 -1  1  1 
 1 -1  1  1  1 -1 -1 -1 -1 -1  1  1  1 -1  1 -1  1 -1  1 -1 -1  1 -1 -1 -1  1  1  1  1 -1 -1 -1 -1 -1 -1 -1  1  1  1  1  1 -1  1  1  1 -1  1  1 -1 -1 -1 
-1  1  1  1 -1 -1 -1 -1  1  1 -1  1 -1  1  1 -1 -1  1 -1 -1 -1  1  1 -1 -1 -1  1 -1 -1 -1 -1  1 -1 -1  1 -1  1  1  1 -1  1 -1  1 -1  1  1  1  1 -1 -1 -1 
-1 -1  1 -1  1 -1 -1 -1 -1 -1  1 -1 -1 -1  1  1  1  1 -1 -1 -1  1  1  1 -1  1  1 -1  1 -1  1 -1 -1  1  1  1  1 -1  1  1  1  1 -1  1  1 -1 -1  1  1  1  1 
 1  1  1 -1 -1 -1  1  1  1  1  1  1 -1  1  1  1 -1 -1  1 -1  1 -1 -1  1 -1  1  1 -1  1 -1 -1  1 -1 -1  1  1  1 -1  1  1  1  1  1  1  1  1 -1 -1  1 -1  1 
-1  1  1 -1  1 -1 -1  1 -1  1 -1 -1  1  1 -1  1  1 -1 -1  1  1 -1  1 -1 -1 -1  1 -1 -1  1  1 -1  1  1 -1  1  1  1 -1  1  1  1  1 -1  1  1 -1 -1 -1  1 -1 
 1 -1 -1 -1  1  1 -1 -1 -1  1 -1  1 -1  1  1 -1 -1  1  1 -1  1  1 -1  1 -1  1 -1 -1  1 -1  1 -1 -1  1 -1 -1  1 -1 -1 -1 -1 -1  1  1  1 -1 -1 -1  1  1 -1 
-1  1  1 -1  1 -1  1  1  1  1  1  1 -1 -1 -1  1  1 -1 -1  1 -1 -1  1 -1  1  1 -1  1 -1 -1 -1  1  1 -1  1  1  1  1 -1 -1  1  1 -1 -1 -1  1 -1  1 -1 -1 -1 
-1  1 -1 -1  1 -1 -1  1 -1 -1  1 -1 -1  1 -1  1 -1 -1 -1  1 -1 -1 -1  1  1 -1 -1 -1 -1 -1 -1  1  1  1  1  1  1  1  1 -1 -1  1 -1 -1  1  1 -1  1  1 -1 -1 
 1  1 -1 -1  1 -1 -1 -1  1 -1 -1  1 -1 -1 -1  1  1  1 -1 -1  1  1 -1  1 -1 -1 -1  1 -1 -1 -1 -1 -1  1 -1 -1  1  1 -1 -1  1  1  1 -1 -1  1 -1  1 -1  1 -1 
-1 -1 -1 -1 -1 -1 -1 -1  1  1  1 -1  1 -1  1  1 -1 -1  1 -1  1  1  1  1 -1  1  1  1  1 -1  1  1  1  1  1  1 -1  1 -1 -1  1  1  1 -1  1  1 -1  1 -1 -1 -1 
 1 -1  1 -1  1 -1 -1 -1  1  1  1 -1 -1  1 -1 -1  1 -1 -1  1 -1  1 -1  1 -1  1 -1 -1 -1  1  1 -1  1  1 -1  1 -1  1 -1  1  1  1 -1  1  1  1 -1  1  1  1  1 
 1  1  1 -1  1 -1 -1 -1  1  1 -1  1  1 -1 -1 -1  1 -1  1 -1  1  1 -1 -1  1 -1 -1  1 -1  1 -1  1  1  1 -1  1  1  1 -1  1 -1  1 -1 -1 -1  1 -1  1  1  1 -1 
 1 -1  1 -1  1 -1 -1  1 -1  1 -1  1 -1 -1  1 -1 -1  1  1  1  1  1 -1 -1 -1  1 -1  1  1 -1  1  1 -1  1  1 -1 -1  1 -1  1  1  1  1  1 -1 -1 -1 -1 -1 -1 -1 
 1 -1  1 -1  1 -1 -1  1  1 -1 -1  1  1  1  1 -1  1  1  1  1 -1  1 -1 -1 -1  1  1  1 -1 -1  1 -1  1 -1  1  1 -1  1 -1 -1 -1 -1  1  1  1 -1  1  1  1  1  1 
-1 -1  1  1  1 -1 -1  1  1  1  1 -1 -1  1  1 -1  1 -1  1  1 -1 -1 -1 -1  1 -1  1  1  1  1 -1 -1 -1  1 -1 -1 -1 -1 -1 -1  1  1  1  1 -1 -1 -1 -1 -1 -1  1 
 1 -1 -1 -1 -1  1 -1  1  1  1 -1 -1 -1 -1 -1 -1 -1  1  1 -1  1  1  1  1  1 -1 -1 -1 -1  1 -1 -1  1  1  1 -1 -1 -1  1 -1 -1 -1  1 -1  1  1  1 -1  1 -1 -1 
 1  1 -1 -1 -1 -1  1 -1 -1 -1 -1  1 -1 -1  1 -1 -1 -1 -1  1  1  1  1  1  1  1  1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1  1 -1 -1  1 -1  1 -1 -1  1 -1  1  1 
-1 -1  1  1  1  1  1 -1  1 -1 -1 -1 -1 -1 -1 -1  1 -1  1 -1  1  1  1  1  1 -1 -1 -1  1 -1 -1 -1  1 -1 -1 -1  1 -1 -1  1  1 -1  1  1 -1  1  1  1  1  1  1 
-1  1  1 -1  1 -1 -1  1 -1 -1  1  1  1  1 -1  1  1 -1 -1 -1 -1 -1  1  1  1  1  1 -1  1  1  1  1  1 -1  1 -1  1 -1  1 -1 -1 -1 -1 -1  1 -1 -1  1  1  1  1 
 1  1  1  1  1  1  1 -1 -1 -1  1 -1 -1  1 -1  1  1 -1 -1  1 -1  1  1 -1  1 -1 -1 -1 -1 -1  1 -1 -1  1 -1 -1  1  1  1 -1  1  1 -1  1  1  1  1 -1  1 -1  1 
 1 -1  1  1  1  1 -1 -1  1  1 -1  1 -1  1 -1  1 -1  1  1  1 -1  1  1 -1 -1 -1 -1  1 -1  1 -1  1  1  1  1  1  1  1 -1  1  1 -1 -1  1 -1 -1  1  1 -1 -1 -1 
 1 -1  1  1  1  1  1 -1  1 -1 -1 -1 -1  1 -1  1  1  1  1  1  1 -1 -1  1 -1 -1 -1  1  1 -1 -1  1 -1  1 -1  1 -1 -1  1 -1  1 -1 -1  1  1  1 -1  1 -1 -1  1 
 1 -1 -1 -1  1  1 -1 -1 -1  1  1 -1 -1  1  1  1  1  1  1 -1 -1  1 -1  1  1 -1  1  1 -1 -1  1 -1  1 -1 -1  1 -1 -1  1 -1  1  1 -1  1  1 -1  1 -1  1 -1  1 
 1  1 -1 -1 -1 -1 -1  1  1 -1  1  1  1 -1 -1  1  1  1 -1  1 -1  1 -1  1  1  1 -1 -1  1  1  1 -1 -1  1  1 -1  1  1 -1 -1 -1 -1  1 -1 -1  1  1 -1 -1 -1 -1 
-1  1 -1 -1 -1  1  1  1 -1  1  1  1  1  1  1 -1 -1 -1  1 -1 -1 -1  1 -1  1 -1  1 -1  1 -1 -1  1 -1  1 -1  1  1 -1  1 -1 -1  1 -1 -1 -1 -1  1  1 -1 -1  1 
 1  1 -1  1 -1 -1  1  1  1 -1 -1  1 -1 -1  1 -1 -1 -1  1  1 -1 -1  1  1 -1 -1  1  1  1  1  1  1  1 -1  1  1 -1 -1  1 -1  1 -1  1  1 -1  1  1  1  1 -1 -1 
 1 -1 -1  1  1  1 -1  1 -1  1 -1 -1 -1 -1 -1 -1 -1  1  1 -1  1  1 -1  1 -1 -1  1  1 -1 -1 -1 -1  1  1 -1  1  1 -1 -1 -1 -1  1  1  1  1 -1  1  1 -1 -1 -1 
-1 -1 -1 -1 -1  1  1 -1  1 -1 -1  1 -1  1  1 -1 -1  1  1 -1  1 -1 -1 -1 -1  1 -1  1 -1 -1 -1 -1  1  1  1 -1 -1 -1 -1  1 -1 -1 -1 -1 -1  1 -1 -1 -1 -1 -1 
 1  1  1  1 -1  1 -1 -1 -1  1  1 -1  1 -1 -1  1  1  1 -1 -1  1 -1  1 -1 -1 -1  1 -1 -1  1  1  1 -1 -1 -1 -1 -1 -1  1  1 -1  1 -1 -1 -1  1  1  1  1 -1  1 
 1  1  1 -1 -1  1 -1  1  1 -1  1  1 -1  1 -1  1 -1  1 -1 -1  1  1 -1 -1  1  1  1  1 -1 -1 -1  1  1  1 -1  1  1  1 -1  1  1  1  1  1 -1  1 -1  1 -1 -1  1 
-1  1  1 -1 -1  1  1  1  1  1 -1  1 -1  1  1  1 -1 -1 -1  1 -1  1  1  1 -1  1 -1 -1  1  1  1 -1 -1  1 -1 -1 -1  1  1 -1 -1  1 -1 -1 -1  1  1 -1 -1  1 -1 
-1  1  1 -1  1  1  1 -1 -1 -1 -1  1 -1  1 -1 -1 -1  1  1 -1 -1  1  1  1 -1  1 -1 -1 -1  1  1 -1 -1 -1  1  1 -1  1  1  1  1  1  1 -1  1  1 -1  1 -1 -1  1 
-1 -1 -1  1 -1 -1  1 -1 -1 -1 -1  1 -1 -1  1  1  1  1 -1  1 -1 -1 -1  1  1 -1  1 -1 -1  1  1  1  1 -1 -1 -1 -1 -1  1 -1 -1  1 -1 -1  1  1 -1 -1 -1 -1 -1 
-1 -1  1  1  1  1  1 -1 -1  1 -1  1  1  1  1 -1 -1 -1 -1  1 -1 -1  1  1  1 -1  1 -1 -1 -1 -1 -1 -1 -1 -1  1  1  1  1 -1 -1 -1 -1  1  1 -1  1  1 -1 -1  1 
-1  1  1  1 -1  1 -1 -1 -1  1  1 -1 -1  1 -1 -1 -1 -1  1  1 -1  1 -1  1  1 -1 -1 -1 -1  1  1 -1  1 -1 -1  1 -1  1 -1 -1 -1  1 -1  1  1  1 -1  1 -1 -1  1 
-1 -1 -1  1 -1  1  1  1 -1  1  1 -1 -1  1  1  1 -1  1 -1  1  1  1  1 -1 -1  1  1  1  1 -1 -1 -1  1 -1  1 -1  1  1 -1  1  1  1  1  1  1  1 -1  1  1  1 -1 
 1  1 -1 -1 -1  1 -1  1  1  1 -1  1  1  1 -1 -1 -1  1 -1  1  1 -1 -1  1 -1 -1 -1 -1 -1  1 -1 -1  1  1 -1  1  1 -1  1 -1  1 -1  1 -1  1 -1 -1 -1 -1 -1 -1 
-1  1  1 -1  1 -1  1 -1  1 -1  1  1  1  1  1  1 -1 -1 -1  1  1  1 -1  1  1 -1 -1 -1  1  1 -1  1 -1 -1  1  1 -1 -1  1  1 -1  1 -1 -1  1 -1 -1 -1  1 -1  1 
-1 -1 -1  1 -1 -1  1 -1 -1  1 -1 -1 -1 -1  1 -1  1 -1  1  1 -1 -1 -1 -1 -1 -1  1  1  1 -1 -1  1 -1  1  1 -1  1 -1 -1  1  1  1 -1  1  1  1 -1 -1 -1 -1 -1 
 1  1 -1 -1 -1  1 -1  1 -1  1  1  1  1  1  1  1 -1  1  1  1  1 -1 -1 -1 -1 -1 -1 -1  1 -1 -1 -1 -1 -1  1  1 -1 -1  1  1 -1  1  1  1  1 -1  1 -1 -1 -1 -1 
-1 -1  1  1 -1  1 -1  1 -1  1  1  1  1 -1  1  1 -1  1 -1 -1 -1  1  1 -1  1 -1  1 -1 -1 -1 -1 -1  1  1 -1 -1 -1  1  1  1  1  1 -1  1  1 -1 -1  1 -1  1  1 
-1 -1  1  1 -1 -1 -1 -1 -1 -1 -1  1 -1 -1  1  1 -1  1  1  1 -1  1  1  1  1 -1 -1  1  1 -1  1  1  1  1  1  1  1  1 -1 -1  1 -1  1  1 -1 -1  1  1 -1 -1  1 
 1 -1 -1 -1 -1  1 -1 -1 -1  1  1 -1  1  1  1 -1  1  1  1  1 -1  1  1  1 -1 -1  1  1 -1 -1 -1  1  1  1  1 -1 -1  1  1 -1  1 -1  1  1  1  1 -1  1  1 -1  1 
 1 -1  1 -1 -1  1 -1  1 -1 -1  1  1  1 -1  1 -1  1  1 -1 -1 -1  1 -1 -1  1  1  1 -1  1  1 -1 -1 -1 -1 -1 -1 -1  1  1  1  1 -1  1 -1 -1 -1  1 -1 -1  1  1 
-1 -1  1 -1  1 -1 -1 -1  1 -1  1 -1  1 -1  1  1 -1 -1  1  1 -1  1  1  1  1 -1  1  1 -1 -1  1 -1 -1  1 -1  1  1 -1  1  1  1 -1  1  1  1  1  1  1 -1 -1  1 
 1  1 -1 -1 -1  1 -1  1  1  1  1 -1  1  1  1  1  1 -1 -1  1 -1 -1 -1 -1  1 -1 -1  1  1  1 -1 -1  1  1  1 -1 -1 -1 -1 -1 -1 -1 -1  1 -1  1  1  1 -1  1 -1 
-1  1  1  1  1 -1  1  1  1 -1 -1  1 -1  1 -1 -1 -1 -1 -1  1 -1  1 -1  1 -1  1  1  1 -1 -1  1 -1 -1  1 -1 -1 -1 -1  1 -1  1  1  1  1  1 -1  1  1 -1 -1  1 
-1  1 -1  1 -1 -1 -1 -1 -1  1  1  1 -1  1 -1 -1 -1  1  1  1  1  1 -1  1  1  1  1 -1 -1  1  1 -1  1 -1  1  1  1  1  1 -1  1 -1 -1  1  1 -1 -1  1 -1  1 -1 
-1  1  1 -1  1  1  1 -1 -1  1  1 -1  1  1  1 -1  1 -1 -1 -1  1  1  1 -1 -1 -1  1 -1  1  1 -1  1  1 -1 -1 -1 -1  1  1 -1 -1 -1 -1  1  1 -1  1  1 -1 -1 -1 
 1  1  1  1  1 -1 -1  1 -1 -1 -1 -1  1  1  1  1  1  1  1  1 -1 -1 -1 -1  1 -1 -1 -1 -1  1  1 -1  1  1  1 -1 -1  1  1  1 -1  1 -1  1 -1 -1  1 -1  1 -1 -1 
-1  1  1  1 -1 -1  1  1 -1 -1 -1  1  1  1  1  1  1 -1  1  1  1 -1 -1 -1 -1 -1 -1 -1 -1  1 -1  1 -1  1  1 -1  1  1 -1  1 -1  1  1  1 -1 -1 -1  1 -1 -1  1 
-1  1 -1 -1 -1  1 -1 -1 -1  1  1  1 -1  1  1  1  1  1  1  1  1  1  1  1 -1 -1 -1 -1  1  1 -1 -1  1 -1 -1 -1 -1 -1 -1 -1 -1  1  1 -1 -1  1  1 -1  1 -1  1 
 1  1  1 -1 -1 -1 -1  1 -1  1  1  1 -1  1 -1  1  1 -1 -1 -1  1  1  1 -1  1 -1  1 -1 -1  1  1  1  1 -1  1 -1  1 -1  1  1  1 -1 -1 -1 -1  1  1 -1 -1 -1 -1 
 1  1  1  1 -1 -1 -1 -1  1  1 -1 -1  1 -1  1 -1 -1  1 -1  1  1  1  1  1 -1 -1  1  1  1  1  1 -1 -1  1  1  1 -1  1 -1  1  1  1  1 -1 -1 -1  1 -1 -1 -1 -1 
 1 -1  1 -1 -1 -1 -1  1 -1  1  1 -1 -1 -1  1  1 -1 -1  1 -1 -1  1  1  1 -1 -1 -1 -1 -1 -1 -1  1  1  1 -1  1  1  1  1  1 -1 -1 -1 -1 -1  1 -1  1 -1  1  1 
 1 -1  1 -1 -1 -1  1 -1 -1  1  1 -1  1 -1 -1  1  1  1 -1  1 -1  1 -1  1  1  1  1 -1  1 -1 -1  1 -1  1  1 -1  1 -1 -1  1  1 -1  1 -1 -1 -1 -1 -1 -1 -1  1 
-1  1 -1  1 -1  1 -1 -1 -1  1 -1 -1 -1 -1  1 -1  1 -1  1  1 -1  1  1  1 -1  1  1  1  1 -1 -1 -1  1  1  1 -1  1  1  1 -1 -1 -1 -1  1 -1  1 -1 -1 -1 -1  1 
 1  1 -1  1  1  1  1  1  1 -1 -1 -1 -1  1 -1  1 -1 -1 -1 -1 -1 -1  1  1 -1  1  1 -1  1 -1  1  1  1  1 -1  1 -1 -1 -1 -1 -1 -1  1 -1  1 -1  1  1 -1  1 -1 
 1 -1 -1 -1  1 -1  1  1 -1 -1  1 -1  1  1 -1 -1 -1 -1 -1 -1  1  1  1  1  1 -1 -1  1  1  1  1 -1  1 -1 -1  1 -1 -1 -1 -1  1  1  1  1 -1 -1  1 -1  1 -1  1 
-1  1 -1  1  1  1  1  1  1 -1  1 -1  1  1 -1 -1 -1  1 -1 -1  1 -1 -1 -1 -1  1 -1 -1 -1  1 -1  1 -1 -1 -1 -1 -1 -1 -1 -1  1  1  1  1 -1  1  1 -1 -1  1  1 
-1 -1  1 -1  1  1  1  1 -1  1  1  1  1  1 -1 -1  1  1 -1  1  1 -1  1  1 -1  1  1 -1  1  1 -1  1 -1 -1  1  1  1  1 -1  1  1 -1  1  1  1 -1 -1  1 -1  1  1 
-1 -1  1  1 -1  1 -1 -1 -1  1  1  1  1  1 -1 -1  1 -1 -1  1  1  1 -1  1  1  1  1 -1  1  1  1  1 -1  1  1  1  1 -1 -1 -1  1  1 -1  1 -1 -1 -1 -1 -1  1 -1 
-1 -1 -1  1 -1  1  1 -1 -1  1 -1 -1 -1 -1  1  1  1 -1 -1  1 -1 -1 -1 -1  1  1 -1  1  1 -1 -1 -1 -1  1  1  1 -1  1 -1  1 -1  1 -1 -1 -1 -1  1 -1  1 -1  1 
-1 -1 -1  1  1  1  1  1 -1  1 -1 -1 -1  1 -1  1 -1 -1  1  1 -1 -1  1 -1 -1 -1 -1 -1  1  1  1  1 -1  1 -1 -1  1 -1 -1  1 -1 -1  1  1  1  1 -1  1  1  1  1 
 1 -1  1  1 -1  1  1 -1  1 -1  1 -1  1  1 -1  1  1  1  1 -1  1  1 -1 -1  1 -1  1  1 -1  1 -1 -1 -1 -1 -1  1 -1  1 -1  1  1  1  1 -1 -1 -1  1 -1 -1  1 -1 
 1 -1 -1  1  1  1  1  1  1  1  1 -1  1 -1  1  1 -1  1 -1 -1 -1 -1  1  1  1  1  1  1 -1 -1 -1 -1  1 -1  1 -1 -1 -1 -1 -1 -1  1 -1 -1 -1 -1 -1  1 -1 -1  1 
 1  1 -1 -1  1  1 -1  1  1 -1  1  1 -1 -1  1 -1 -1  1 -1 -1 -1 -1  1 -1  1  1  1  1 -1  1  1  1  1 -1 -1 -1  1  1  1  1 -1  1  1 -1 -1 -1  1  1  1  1  1 
 1  1  1 -1 -1  1  1 -1 -1 -1  1 -1  1 -1 -1  1 -1  1  1  1 -1 -1 -1  1 -1 -1 -1  1 -1 -1 -1 -1  1  1  1 -1 -1  1  1 -1 -1 -1  1 -1  1 -1 -1  1  1 -1  1 
 1  1  1 -1  1  1 -1 -1 -1 -1 -1 -1  1  1 -1  1 -1  1  1 -1 -1 -1  1  1  1 -1 -1  1 -1  1  1 -1 -1  1 -1 -1 -1 -1 -1  1  1  1 -1  1 -1  1  1 -1 -1  1 -1 
 1 -1 -1 -1  1 -1  1 -1 -1 -1 -1 -1  1 -1 -1  1  1 -1 -1  1 -1  1  1  1  1  1 -1  1  1  1 -1  1 -1 -1 -1  1 -1 -1  1 -1  1  1  1 -1  1  1 -1  1  1  1  1 
-1 -1 -1 -1  1 -1  1  1  1 -1 -1  1 -1 -1  1  1 -1  1  1 -1 -1 -1 -1 -1  1  1  1  1 -1  1  1 -1 -1 -1  1 -1  1  1 -1 -1  1  1 -1 -1  1 -1  1  1 -1 -1  1 
-1  1  1 -1  1 -1  1 -1 -1  1 -1  1 -1 -1 -1  1 -1  1  1 -1 -1 -1 -1 -1 -1  1  1  1  1 -1 -1 -1  1 -1 -1 -1 -1 -1 -1  1 -1 -1 -1 -1 -1  1  1 -1 -1  1 -1 
 1 -1 -1  1  1 -1  1  1  1 -1 -1 -1 -1  1  1  1 -1 -1 -1  1  1  1 -1 -1  1  1  1 -1 -1 -1 -1 -1 -1  1  1  1  1 -1 -1 -1 -1  1  1  1  1  1  1  1  1  1 -1 
-1  1 -1  1 -1 -1 -1 -1  1 -1 -1 -1  1 -1  1 -1  1  1 -1  1  1 -1 -1 -1  1  1  1 -1 -1 -1  1  1 -1 -1 -1 -1  1 -1  1  1 -1  1 -1 -1  1 -1 -1  1  1 -1 -1 
-1 -1  1  1  1 -1 -1 -1  1  1  1  1  1  1  1 -1 -1  1 -1  1 -1  1 -1 -1 -1  1  1  1  1  1 -1 -1 -1 -1 -1  1  1 -1 -1  1 -1  1  1 -1 -1 -1 -1  1  1  1  1 
-1  1  1 -1 -1 -1  1  1 -1 -1  1  1 -1  1  1 -1  1  1 -1  1  1 -1  1  1 -1 -1 -1 -1 -1 -1 -1  1  1 -1  1  1 -1  1  1  1 -1  1  1  1  1  1 -1 -1  1  1 -1 
 1 -1  1 -1  1  1 -1  1 -1  1  1 -1  1 -1  1  1  1 -1 -1 -1 -1  1 -1 -1  1 -1  1 -1  1  1 -1  1  1  1 -1 -1  1  1  1  1  1  1  1 -1 -1 -1 -1  1  1  1  1 
-1 -1  1 -1  1 -1  1 -1 -1  1 -1  1  1 -1  1  1  1  1 -1 -1 -1  1  1 -1  1 -1  1  1 -1  1  1 -1  1  1  1 -1  1  1  1  1 -1 -1  1 -1  1 -1 -1 -1  1  1 -1 
-1  1 -1 -1  1 -1 -1  1  1 -1  1 -1 -1 -1  1  1 -1  1 -1  1  1  1 -1 -1  1 -1 -1  1 -1 -1 -1  1 -1  1 -1  1  1  1  1 -1  1 -1  1  1 -1 -1  1  1 -1 -1  1 
-1 -1 -1 -1  1  1 -1 -1 -1 -1 -1 -1 -1 -1 -1  1  1 -1 -1 -1 -1 -1  1  1 -1  1  1  1  1 -1  1  1 -1  1  1 -1 -1  1 -1 -1 -1  1 -1  1 -1  1 -1  1 -1 -1 -1 
 1 -1  1 -1 -1  1  1  1 -1  1 -1  1 -1  1 -1 -1  1  1  1 -1  1 -1 -1 -1 -1 -1  1 -1 -1 -1  1 -1  1 -1  1 -1  1  1 -1 -1  1 -1  1  1  1  1 -1  1  1  1  1 
-1 -1 -1  1  1 -1 -1 -1 -1 -1 -1 -1  1 -1 -1  1 -1  1 -1  1 -1  1  1 -1 -1  1  1  1 -1 -1 -1  1 -1 -1  1 -1  1  1 -1 -1 -1  1 -1 -1 -1  1  1  1 -1 -1 -1 
 1  1  1 -1 -1 -1 -1 -1 -1  1 -1 -1 -1 -1  1 -1  1 -1 -1 -1  1  1  1  1 -1  1 -1  1  1 -1 -1 -1  1 -1 -1  1  1  1 -1  1 -1 -1  1  1 -1 -1  1  1  1 -1 -1 
-1 -1  1 -1 -1  1 -1  1  1  1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1  1 -1  1 -1 -1 -1 -1 -1 -1 -1  1 -1  1  1 -1 -1  1 -1 -1 -1 -1 -1 -1 -1  1 -1  1 -1 
 1 -1 -1  1  1 -1 -1  1 -1 -1  1  1  1  1 -1  1 -1 -1  1 -1  1  1  1  1  1  1 -1  1 -1  1  1  1 -1  1 -1 -1 -1 -1 -1  1  1  1 -1  1  1  1  1 -1  1 -1  1 
-1 -1  1  1  1 -1  1 -1 -1  1  1 -1 -1  1 -1  1  1 -1 -1 -1 -1 -1  1  1 -1  1  1  1  1 -1 -1  1 -1 -1 -1 -1 -1  1 -1  1 -1 -1  1  1 -1  1  1  1  1  1 -1 
-1  1  1 -1 -1  1 -1 -1  1  1  1  1 -1  1 -1 -1  1 -1 -1 -1  1 -1 -1 -1 -1 -1 -1  1  1  1 -1  1 -1  1  1  1  1 -1 -1  1  1 -1 -1  1  1 -1  1  1 -1  1 -1 
 1  1  1  1  1  1  1  1 -1 -1  1 -1  1  1 -1  1  1 -1  1 -1  1  1 -1 -1 -1  1 -1  1 -1 -1 -1  1  1 -1 -1  1 -1  1 -1  1  1  1 -1 -1  1  1  1  1 -1 -1 -1 
 1 -1 -1  1  1 -1 -1  1 -1 -1 -1  1 -1  1  1  1  1  1  1  1 -1 -1 -1  1 -1  1 -1 -1  1 -1 -1 -1 -1 -1  1  1 -1  1  1 -1 -1 -1  1 -1  1 -1 -1  1 -1  1  1 
 1 -1  1  1  1  1 -1 -1 -1 -1 -1  1  1  1 -1  1 -1  1  1 -1 -1 -1 -1 -1 -1  1 -1 -1  1  1 -1  1 -1 -1 -1  1 -1  1  1 -1  1  1 -1  1  1  1  1  1 -1  1  1 
-1  1 -1  1  1  1  1 -1 -1  1 -1 -1 -1  1  1  1 -1 -1  1 -1 -1 -1 -1 -1  1 -1 -1  1 -1 -1 -1  1 -1 -1  1  1 -1  1  1 -1  1 -1 -1  1  1 -1 -1 -1  1 -1  1 
-1 -1 -1 -1 -1  1 -1  1  1 -1  1  1 -1 -1  1  1  1  1 -1  1  1 -1 -1 -1 -1  1  1  1 -1 -1 -1 -1  1 -1 -1 -1 -1 -1 -1  1  1  1 -1  1 -1  1 -1  1 -1  1  1 
 1 -1 -1  1  1  1 -1 -1  1  1  1  1 -1  1 -1  1  1  1 -1  1 -1 -1 -1 -1  1  1  1  1 -1  1 -1  1 -1  1  1  1  1  1 -1 -1 -1  1  1  1 -1 -1  1 -1 -1  1  1 
 1 -1 -1  1 -1 -1  1 -1 -1  1 -1  1  1  1 -1  1  1 -1 -1 -1 -1  1  1 -1 -1 -1  1 -1  1 -1  1  1 -1 -1  1 -1  1  1 -1  1 -1 -1 -1 -1 -1 -1 -1 -1  1 -1 -1 
 1  1  1 -1 -1  1  1 -1 -1 -1  1  1  1 -1 -1  1 -1  1 -1  1 -1  1 -1 -1  1  1  1  1 -1  1 -1 -1  1 -1  1  1 -1 -1  1  1  1 -1  1 -1  1 -1  1  1  1 -1  1 
-1 -1 -1  1 -1 -1  1 -1  1  1  1 -1  1  1  1 -1  1  1  1 -1 -1 -1 -1 -1  1  1 -1  1 -1 -1 -1  1  1 -1 -1  1  1 -1 -1 -1 -1  1  1  1  1 -1 -1 -1 -1 -1  1 
 1 -1  1 -1  1 -1  1 -1  1 -1 -1  1 -1  1 -1 -1  1  1 -1  1 -1 -1  1  1 -1  1  1 -1  1 -1 -1 -1 -1 -1  1 -1  1 -1 -1  1  1  1  1  1  1 -1  1  1  1  1 -1 
-1 -1 -1 -1  1  1 -1 -1  1  1  1  1 -1  1 -1  1 -1  1 -1  1 -1  1  1 -1  1  1  1  1 -1 -1 -1  1 -1 -1 -1  1 -1 -1  1 -1 -1  1  1  1  1  1 -1 -1 -1 -1 -1 
-1 -1 -1 -1  1 -1 -1 -1  1 -1  1  1 -1  1  1 -1 -1  1  1 -1 -1  1  1  1  1 -1  1  1 -1 -1  1  1 -1 -1 -1  1 -1 -1  1 -1 -1 -1 -1 -1  1 -1 -1 -1  1  1  1 
 1 -1 -1  1  1  1 -1  1  1  1  1  1  1  1 -1 -1  1 -1 -1  1  1 -1 -1 -1  1 -1 -1 -1  1  1  1 -1 -1  1  1  1  1 -1  1  1 -1  1  1 -1  1  1 -1 -1  1 -1  1 
-1 -1  1  1  1  1 -1  1  1  1 -1  1 -1 -1 -1 -1 -1 -1  1 -1 -1  1  1  1  1  1 -1 -1 -1  1 -1 -1  1 -1  1  1 -1  1 -1  1 -1  1  1  1  1  1  1 -1 -1 -1  1 
 1 -1 -1 -1 -1 -1 -1  1 -1  1  1  1 -1 -1  1  1  1  1 -1  1 -1 -1  1 -1  1 -1  1 -1 -1  1 -1  1 -1  1  1 -1 -1  1  1  1  1  1 -1  1 -1  1 -1 -1 -1  1 -1 
 1 -1 -1  1 -1  1  1 -1 -1 -1  1  1  1 -1  1  1  1  1  1 -1 -1  1 -1  1  1  1 -1  1  1  1 -1 -1  1  1 -1  1  1 -1 -1  1  1 -1  1 -1  1 -1 -1 -1  1  1  1 
 1 -1  1 -1  1 -1  1  1 -1 -1 -1 -1  1 -1 -1  1  1  1  1  1  1 -1  1 -1 -1 -1  1  1 -1 -1 -1  1 -1 -1 -1  1 -1  1 -1 -1 -1  1 -1 -1 -1 -1  1  1 -1 -1  1 
-1  1 -1 -1  1  1  1 -1  1  1  1  1 -1  1  1 -1 -1 -1  1  1  1 -1  1 -1 -1  1 -1  1  1  1  1  1  1 -1 -1  1 -1 -1 -1  1  1 -1 -1 -1  1 -1  1  1  1 -1 -1 
-1  1 -1 -1 -1  1  1  1  1 -1  1 -1  1  1 -1 -1  1 -1 -1  1 -1  1  1  1  1 -1 -1 -1  1  1  1  1 -1  1  1  1  1 -1  1  1 -1  1  1 -1 -1 -1 -1  1 -1 -1 -1 
 1  1 -1 -1  1 -1 -1 -1  1 -1  1 -1  1  1 -1 -1 -1 -1  1  1 -1  1  1 -1  1  1  1  1 -1 -1 -1  1  1  1 -1 -1 -1 -1 -1 -1  1  1 -1 -1 -1  1 -1  1  1  1  1 
-1 -1 -1 -1  1 -1 -1 -1  1  1 -1 -1 -1 -1  1  1 -1 -1  1 -1 -1 -1  1 -1  1  1 -1  1  1 -1 -1  1 -1 -1 -1 -1  1 -1  1 -1 -1  1 -1 -1  1 -1 -1  1 -1 -1  1 
 1 -1 -1 -1  1 -1  1 -1  1  1 -1 -1 -1 -1  1 -1  1 -1 -1 -1  1  1 -1 -1 -1 -1  1  1 -1  1  1  1  1  1 -1 -1 -1  1  1  1  1 -1 -1  1 -1  1 -1 -1  1 -1  1 
 1  1 -1 -1 -1 -1 -1 -1  1 -1  1  1  1 -1 -1  1 -1  1  1  1  1 -1 -1 -1  1 -1  1 -1 -1 -1  1 -1 -1  1  1 -1 -1 -1 -1 -1 -1  1 -1 -1 -1  1 -1 -1 -1 -1 -1 
 1 -1  1  1  1  1 -1  1  1  1 -1 -1 -1 -1 -1 -1  1 -1  1 -1 -1 -1  1  1 -1  1  1  1 -1 -1  1  1  1 -1  1  1 -1 -1 -1  1  1  1 -1  1 -1  1 -1 -1  1 -1  1 
 1  1  1 -1  1 -1  1  1  1  1  1  1 -1 -1 -1 -1  1 -1  1  1 -1  1 -1 -1 -1  1  1 -1  1 -1 -1  1  1  1  1  1  1  1 -1  1  1 -1  1  1 -1  1  1 -1 -1  1  1 
-1  1 -1  1 -1  1  1 -1  1 -1  1 -1  1 -1 -1 -1  1  1  1  1 -1 -1  1 -1  1 -1 -1 -1 -1  1  1  1  1 -1  1  1  1 -1 -1 -1 -1 -1 -1 -1  1  1 -1  1 -1 -1  1 
-1  1  1  1 -1 -1  1  1  1 -1 -1 -1  1  1 -1 -1 -1 -1 -1  1  1 -1  1 -1 -1 -1 -1  1  1  1  1  1  1  1 -1  1 -1 -1 -1  1 -1 -1  1 -1  1 -1 -1 -1 -1  1 -1 
 1  1 -1  1 -1  1  1 -1  1  1 -1  1 -1 -1 -1 -1  1  1 -1 -1 -1  1  1  1 -1 -1  1  1  1  1 -1 -1 -1 -1  1 -1  1 -1  1  1  1  1 -1 -1 -1  1 -1  1  1 -1 -1 
-1 -1 -1 -1 -1  1  1  1  1  1  1 -1 -1 -1 -1  1 -1  1  1 -1  1 -1  1  1  1  1  1 -1  1  1  1  1 -1  1  1 -1  1  1  1  1 -1 -1 -1  1 -1  1  1 -1  1 -1  1 
-1  1  1  1  1  1 -1 -1 -1 -1 -1 -1  1  1 -1 -1  1 -1 -1  1 -1 -1 -1  1  1  1  1  1 -1  1  1 -1  1 -1 -1  1  1  1  1 -1  1 -1  1  1 -1 -1  1  1 -1 -1  1 
-1  1  1 -1  1 -1  1  1 -1 -1 -1 -1 -1 -1 -1 -1  1 -1 -1  1  1  1  1 -1  1 -1  1 -1 -1 -1 -1 -1  1 -1 -1 -1  1 -1 -1  1  1 -1 -1 -1  1  1 -1 -1 -1 -1 -1 
-1 -1  1 -1 -1  1 -1  1  1 -1 -1  1  1 -1 -1  1 -1 -1 -1 -1  1  1 -1  1  1 -1  1 -1 -1  1 -1 -1  1  1  1  1 -1 -1 -1  1  1  1  1  1 -1 -1 -1  1  1  1 -1 
 1 -1  1 -1 -1  1  1  1 -1  1  1 -1 -1  1  1  1  1  1  1 -1  1 -1 -1 -1 -1  1 -1 -1  1 -1  1 -1 -1 -1 -1  1 -1 -1  1  1  1 -1  1  1 -1  1  1 -1  1  1 -1 
-1  1 -1  1 -1  1 -1  1 -1  1  1  1  1 -1 -1  1  1  1  1 -1  1  1 -1 -1 -1 -1  1  1 -1  1  1  1 -1 -1 -1 -1  1  1 -1  1  1 -1  1 -1  1  1  1  1 -1  1  1 
-1 -1  1  1 -1 -1 -1  1  1  1 -1  1 -1 -1 -1 -1  1 -1  1  1 -1 -1 -1 -1 -1 -1 -1 -1  1  1 -1 -1  1 -1  1 -1  1 -1 -1 -1  1  1  1 -1  1 -1 -1  1  1  1  1 
-1  1  1  1 -1  1  1 -1 -1 -1  1  1 -1 -1 -1  1  1  1 -1  1 -1  1 -1  1 -1 -1 -1 -1  1  1  1  1 -1 -1 -1  1  1 -1 -1 -1  1 -1  1 -1 -1 -1  1  1 -1 -1 -1 
 1 -1  1 -1 -1 -1 -1  1  1  1  1  1  1 -1  1  1  1 -1  1  1  1 -1  1  1  1 -1 -1  1 -1 -1  1  1 -1  1 -1 -1  1  1  1 -1 -1  1  1 -1 -1 -1  1  1 -1 -1 -1 
-1 -1  1  1 -1 -1 -1 -1  1 -1  1  1 -1 -1  1 -1  1  1 -1  1 -1  1 -1 -1 -1 -1  1  1  1 -1 -1 -1  1 -1 -1  1 -1 -1  1  1  1 -1 -1 -1  1 -1 -1  1  1  1 -1 
 1  1 -1  1  1  1 -1  1 -1 -1 -1  1 -1  1  1 -1 -1  1  1 -1 -1  1 -1  1 -1 -1 -1  1  1 -1  1  1  1  1  1 -1 -1  1  1  1  1  1 -1  1  1  1 -1 -1  1 -1  1 
-1  1 -1  1  1  1 -1  1 -1 -1 -1  1 -1 -1 -1  1  1  1 -1 -1  1 -1  1 -1  1  1 -1  1 -1  1 -1  1 -1  1 -1  1  1 -1 -1  1  1  1  1 -1  1  1  1  1  1 -1 -1 
 1 -1  1  1 -1  1  1  1 -1  1  1 -1 -1  1  1  1 -1  1 -1  1  1  1 -1  1  1 -1 -1  1  1  1 -1  1  1  1 -1  1  1  1  1  1  1 -1 -1 -1  1  1  1 -1 -1 -1  1 
-1  1  1  1  1 -1  1  1  1 -1 -1  1 -1  1  1 -1 -1  1 -1 -1  1  1  1 -1 -1 -1  1  1  1 -1  1 -1 -1 -1 -1 -1 -1  1 -1 -1  1 -1 -1  1 -1  1  1  1 -1  1 -1 
-1  1  1  1  1  1 -1 -1 -1 -1 -1 -1  1 -1  1  1  1  1  1 -1 -1  1  1  1 -1  1 -1 -1 -1 -1 -1 -1  1  1  1 -1  1  1  1  1 -1 -1  1  1 -1 -1 -1 -1  1  1  1 
-1 -1 -1  1 -1 -1  1  1  1  1 -1  1 -1  1 -1 -1 -1  1 -1 -1 -1  1 -1  1  1  1  1  1 -1 -1  1  1 -1 -1 -1 -1  1  1 -1  1  1  1 -1  1  1  1  1 -1  1  1  1 
-1 -1 -1  1 -1 -1 -1  1 -1 -1  1 -1  1  1  1 -1  1  1 -1 -1  1  1  1 -1  1  1 -1  1 -1  1  1  1  1  1 -1 -1  1  1 -1  1  1  1  1  1  1  1 -1  1  1  1  1 
-1 -1  1  1  1  1  1  1  1  1 -1 -1 -1  1  1 -1  1  1  1 -1  1  1  1  1 -1 -1  1  1 -1  1 -1  1 -1  1  1 -1 -1  1 -1 -1 -1 -1  1 -1  1 -1  1  1  1 -1 -1 
-1  1 -1  1  1  1  1 -1 -1  1 -1  1  1 -1 -1  1 -1  1 -1 -1  1 -1 -1 -1 -1 -1 -1 -1  1  1 -1 -1 -1 -1  1  1  1 -1  1  1  1 -1 -1  1  1 -1  1 -1 -1 -1  1 
-1  1  1 -1  1  1  1 -1  1  1  1  1 -1 -1 -1  1  1  1 -1 -1  1  1  1  1  1 -1  1  1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1  1 -1  1 -1  1  1  1  1  1 -1 -1  1 
-1  1 -1 -1 -1 -1 -1 -1  1 -1 -1  1  1  1 -1 -1 -1  1  1  1 -1  1 -1  1  1 -1  1  1 -1  1 -1 -1  1 -1  1  1 -1 -1  1 -1 -1  1  1  1  1 -1  1 -1  1 -1 -1 
-1  1 -1  1  1 -1  1  1  1  1  1 -1  1  1 -1  1 -1  1  1 -1  1  1  1 -1  1 -1  1 -1  1 -1 -1 -1 -1  1 -1  1  1 -1 -1  1 -1 -1 -1 -1  1  1 -1  1  1  1 -1 
-1 -1 -1  1  1 -1 -1  1  1 -1  1  1  1 -1  1 -1  1  1  1 -1  1 -1  1 -1 -1  1 -1 -1 -1  1  1  1 -1  1 -1  1  1 -1 -1  1  1  1 -1 -1 -1 -1  1 -1  1 -1 -1 
 1 -1  1 -1  1 -1  1 -1  1  1  1 -1  1 -1 -1  1  1  1 -1 -1 -1 -1 -1 -1  1  1 -1 -1 -1  1  1  1  1 -1  1  1  1 -1 -1  1  1  1 -1  1 -1  1 -1 -1 -1 -1  1 
 1 -1  1  1  1 -1  1  1  1  1  1 -1 -1  1  1 -1  1 -1 -1  1 -1 -1  1 -1 -1  1  1  1 -1  1  1 -1 -1  1 -1  1 -1 -1  1 -1 -1  1 -1  1 -1  1 -1 -1  1 -1  1 
 1  1  1 -1  1 -1  1  1 -1  1  1 -1 -1  1 -1  1 -1  1  1 -1 -1  1 -1 -1  1  1 -1  1 -1  1  1  1 -1 -1  1 -1  1  1 -1 -1  1 -1  1 -1  1  1  1 -1 -1 -1 -1 
-1 -1 -1 -1  1  1  1 -1 -1  1 -1 -1 -1 -1 -1  1  1 -1 -1  1  1 -1 -1  1  1  1  1 -1  1  1 -1 -1  1 -1  1 -1  1 -1 -1  1 -1  1  1 -1 -1  1 -1  1  1  1 -1 
 1  1  1  1  1  1  1 -1 -1 -1 -1 -1 -1  1  1  1 -1 -1  1  1 -1 -1  1  1 -1  1  1 -1  1 -1  1 -1  1  1  1 -1 -1 -1  1 -1  1  1  1 -1  1 -1 -1 -1  1 -1  1 
-1  1 -1 -1 -1  1  1 -1 -1 -1 -1 -1  1  1 -1  1 -1 -1  1  1 -1  1 -1 -1 -1  1  1  1  1  1  1  1  1  1  1 -1  1 -1 -1  1 -1  1 -1 -1 -1 -1  1 -1 -1 -1  1 
 1 -1 -1  1  1  1 -1  1  1 -1  1 -1 -1 -1 -1  1 -1  1  1  1 -1  1 -1 -1 -1  1  1  1 -1  1 -1  1  1 -1 -1  1 -1  1  1 -1 -1 -1 -1  1  1 -1  1 -1 -1 -1  1 
-1 -1 -1 -1 -1  1  1  1  1  1 -1 -1 -1 -1 -1 -1  1 -1  1 -1 -1  1  1 -1 -1 -1 -1 -1 -1  1  1  1 -1  1  1 -1 -1 -1 -1  1 -1 -1  1 -1  1  1  1 -1  1  1  1 
 1 -1  1 -1  1  1 -1 -1  1  1 -1  1  1 -1  1  1 -1 -1 -1 -1  1 -1 -1 -1  1 -1  1  1  1 -1  1  1  1  1 -1 -1 -1  1 -1 -1  1 -1 -1  1 -1  1 -1  1  1  1  1 
 1 -1 -1  1 -1  1 -1 -1 -1 -1 -1 -1  1 -1 -1 -1  1  1 -1 -1 -1  1  1  1  1 -1 -1  1  1  1 -1  1  1 -1 -1 -1 -1 -1 -1 -1  1  1 -1 -1 -1  1  1 -1 -1  1 -1 
-1  1 -1  1  1 -1 -1  1  1 -1 -1  1 -1 -1 -1 -1 -1  1  1  1  1  1 -1 -1  1  1 -1  1  1  1 -1  1 -1 -1 -1 -1  1 -1 -1  1  1 -1 -1 -1 -1  1  1 -1 -1  1 -1 
 )NN";
