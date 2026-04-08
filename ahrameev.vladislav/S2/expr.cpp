#include "expr.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include <iostream>
#include <fstream>
#include <string>

namespace akhrameev {

void tokenize(const std::string& line, Queue<std::string>& out) {
    size_t i = 0;
    while (i < line.size()) {
        size_t j = line.find(' ', i);
        if (j == std::string::npos) j = line.size();
        if (j > i) out.push(line.substr(i, j - i));
        i = j + 1;
    }
}

int run(int argc, char* argv[]) {
    std::istream* input = &std::cin;
    std::ifstream file;

    if (argc > 1) {
        file.open(argv[1]);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл " << argv[1] << "\n";
            return 1;
        }
        input = &file;
    }

    std::string line;
    while (std::getline(*input, line)) {
        Queue<std::string> tokens;
        tokenize(line, tokens);
        
        std::cout << "Tokens: ";
        while (!tokens.empty()) {
            std::cout << tokens.drop() << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
}