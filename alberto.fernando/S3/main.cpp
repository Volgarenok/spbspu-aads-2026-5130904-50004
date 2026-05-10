#include "commands.hpp"
#include "graph.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cerr << "Error: filename argument required\n"
              << "Usage: " << argv[0] << " filename\n";
    return 1;
  }
