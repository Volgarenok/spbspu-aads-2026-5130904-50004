#include <iostream>
#include <fstream>
#include <string>
#include "BSTree.hpp"

int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        std::cout << "No filename provided\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open())
    {
        std::cout << "Can't open file\n";
        return 1;
    }



    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;


    }
}
