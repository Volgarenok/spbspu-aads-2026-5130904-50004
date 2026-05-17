#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "BSTree.hpp"
#include <sstream>
#include <fstream>
#include <string>

namespace haliullin
{
  class Cmd
  {
  public:
    using func_t = void (Cmd::*)(std::istream&in, std::ostream& out);

    Cmd();

    void loadFromFile(const std::string& file);
    void processCmd(std::istream& in, std::ostream& out);

  private:
    BSTree< std::string, BSTree< int, std::string > > datasets_;
    BSTree< std::string, func_t > commands_;

    void cmdPrint(std::istream& in, std::ostream& out);
    void cmdComplement(std::istream& in, std::ostream& out);
    void cmdIntersect(std::istream& in, std::ostream& out);
    void cmdUnion(std::istream& in, std::ostream& out);
  };
}

#endif
