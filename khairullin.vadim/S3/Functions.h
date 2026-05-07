#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <string>
namespace khairullin {
    std::string getToken(std::string & line) {
        std::string token = "";
        std::string result = "";
        size_t new_start = 0;
        for (size_t i = 0; i < line.length() && (line[i] != ' ' || line[i] != '\0'); i++) {
            token += line[i];
            new_start = i;
        }
        new_start++;
        for (size_t i = 0; i < new_start && line[i] != '\0'; i++) {
            result += line[i];
        }
        line = result;
        return token;
    }

    template<class T, class U>
    void sortPair(khairullin::Vector< std::pair< T, U > > & vector) {
        for (size_t i = 0; i < vector.getSize() - 1; i++) {
            for (size_t j = 0; j < vector.getSize() - i - 1; j++) {
                if (vector[j].second > vector[j + 1].second) {
                    std::swap(vector[j], vector[j + 1]);
                }
            }
        }
    }
}
#endif