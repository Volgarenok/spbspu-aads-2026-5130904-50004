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

  std::string line;
  while (std::getline(file, line))
  {
    if (line.empty()) continue;
    std::istringstream iss(line);
    std::string datasetName;
    if (!(iss >> datasetName)) continue;

    SingleDataset dataset;
    int key;
    std::string value;
    while (iss >> key >> value)
    {
      dataset.push(key, value);
    }
    datasets_.push(datasetName, dataset);
  }
  file.close();
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

  if (!in.eof())
  {
    throw std::runtime_error("Bad input");
  }
}

void haliullin::Cmd::cmdPrint(std::istream& in, std::ostream& out)
{
  std::string datasetName;
  if (!(in >> datasetName))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  auto it = datasets_.find(datasetName);
  if (it == datasets_.end())
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  const auto& dataset = it->second;
  if (dataset.isEmpty())
  {
    out << "<EMPTY>\n";
    return;
  }

  out << datasetName;
  for (auto cit = dataset.cbegin(); cit != dataset.cend(); ++cit)
  {
    out << " " << cit->first << " " << cit->second;
  }
  out << "\n";
}

void haliullin::Cmd::cmdComplement(std::istream& in, std::ostream& out)
{
  std::string newName, leftName, rightName;
  if (!(in >> newName >> leftName >> rightName))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  auto leftIt = datasets_.find(leftName);
  auto rightIt = datasets_.find(rightName);
  if (leftIt == datasets_.end() || rightIt == datasets_.end())
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  const auto& left = leftIt->second;
  const auto& right = rightIt->second;
  SingleDataset result;

  for (auto cit = left.cbegin(); cit != left.cend(); ++cit)
  {
    if (right.find(cit->first) == right.cend())
    {
      result.push(cit->first, cit->second);
    }
  }

  datasets_.push(newName, result);
}

void haliullin::Cmd::cmdIntersect(std::istream& in, std::ostream& out)
{
  std::string newName, leftName, rightName;
  if (!(in >> newName >> leftName >> rightName))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  auto leftIt = datasets_.find(leftName);
  auto rightIt = datasets_.find(rightName);
  if (leftIt == datasets_.end() || rightIt == datasets_.end())
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  const auto& left = leftIt->second;
  const auto& right = rightIt->second;
  SingleDataset result;

  for (auto cit = left.cbegin(); cit != left.cend(); ++cit)
  {
    if (right.find(cit->first) != right.cend())
    {
      result.push(cit->first, cit->second);
    }
  }

  datasets_.push(newName, result);
}

void haliullin::Cmd::cmdUnion(std::istream& in, std::ostream& out)
{
  std::string newName, leftName, rightName;
  if (!(in >> newName >> leftName >> rightName))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  auto leftIt = datasets_.find(leftName);
  auto rightIt = datasets_.find(rightName);
  if (leftIt == datasets_.end() || rightIt == datasets_.end())
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  const auto& left = leftIt->second;
  const auto& right = rightIt->second;
  SingleDataset result;

  for (auto cit = left.cbegin(); cit != left.cend(); ++cit)
  {
    result.push(cit->first, cit->second);
  }
  for (auto cit = right.cbegin(); cit != right.cend(); ++cit)
  {
    if (left.find(cit->first) == left.cend())
    {
      result.push(cit->first, cit->second);
    }
  }

  datasets_.push(newName, result);
}
