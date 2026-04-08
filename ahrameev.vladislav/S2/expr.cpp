#include "expr.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

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

void to_postfix(Queue<std::string>& tokens, Queue<std::string>& out) {
    Stack<std::string> ops;
    while (!tokens.empty()) {
        std::string t = tokens.drop();

        if (t == "(") {
            ops.push(t);
        } else if (t == ")") {
            while (!ops.empty() && ops.top() != "(") {
                out.push(ops.drop());
            }
            if (ops.empty()) throw std::runtime_error("Ошибка в скобках");
            ops.drop(); 
        } else {
            out.push(t);
        }
    }
    while (!ops.empty()) {
        if (ops.top() == "(") throw std::runtime_error("Ошибка в скобках");
        out.push(ops.drop());
    }
}

int run(int argc, char* argv[]) {
    std::istream* input = &std::cin;
    std::ifstream file;

    if (argc > 1) {
        file.open(argv[1]);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл " << argv[1] << std::endl;
            return 1;
        }
        input = &file;
    }

    std::string line;
    while (std::getline(*input, line)) {
        Queue<std::string> tokens;
        tokenize(line, tokens);

        Queue<std::string> postfix;
        to_postfix(tokens, postfix);

        
        std::cout << "Postfix: ";
        while (!postfix.empty()) std::cout << postfix.drop() << " ";
        std::cout << "\n";
    }
  }
}