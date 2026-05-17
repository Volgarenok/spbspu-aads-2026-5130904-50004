#include "commands.hpp"
#include <fstream>
#include <stdexcept>
#include <limits>

haliullin::Cmd::Cmd()
{
  commands_.push("print", &Cmd::cmdPrint);
  commands_.push("complement", &Cmd::cmdComplement);
  commands_.push("intersect", &Cmd::cmdIntersect);
  commands_.push("union", &Cmd::cmdUnion);
}

void haliullin::Cmd::loadFromFile(const std::string& filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("Cannot open file");
  }

  std::string datasetName;
  while (file >> datasetName)
  {
    SingleDataset dataset;
    int key;
    std::string value;
    while (file >> key >> value)
    {
      dataset.push(key, value);
    }
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    datasets_.push(datasetName, dataset);
  }
}

void haliullin::Cmd::processCmd(std::istream& in, std::ostream& out)
{
  std::string command;
  while (in >> command)
  {
    auto it = commands_.find(command);
    if (it == commands_.end())
    {
      out << "<INVALID COMMAND>\n";
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }

    func_t func = it->second;
    (this->*func)(in, out);
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
