
#include <iostream>
#include <fstream>

int main()
{
    std::ofstream   result("result.cpp");
    result << R"(
#include <iostream>

extern std::string network;

int main()
{
    std::cout << network;
}

)";

    // The train application creates a "nets" file.
    // This application takes the best neural net from this file (the first 150 lines).
    // Then create an application that prints this network.
    // We are doing this as the input to this problem is a program that prints the
    // network.
    // https://open.kattis.com/problems/mnist10class
    std::ifstream   networkFile("nets");
    std::string     line;

    result << R"(std::string network = R"NN()";
    for(int loop = 0;loop < 150; ++loop) {
        std::getline(networkFile, line);
        result << line << "\n";
    }
    result << R"( )NN";)" << "\n\n";
}


