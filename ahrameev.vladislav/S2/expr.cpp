#include "expr.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include <iostream>
#include <fstream>
#include <string>

namespace akhrameev {
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
            // Пока просто выводим строку для проверки
            std::cout << "Read: " << line << "\n";
        }
        return 0;
    }
}