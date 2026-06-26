#include "DictionaryManager.h"
#include <iostream>
#include <sstream>
#include <string>

void printHelp() {
    std::cout << "Commands:" << std::endl;
    std::cout << "create <dictionary>" << std::endl;
    std::cout << "delete <dictionary>" << std::endl;
    std::cout << "load <dictionary> <file-name>" << std::endl;
    std::cout << "insert <dictionary> <word>" << std::endl;
    std::cout << "search <dictionary> <word>" << std::endl;
    std::cout << "remove <dictionary> <word>" << std::endl;
    std::cout << "show <dictionary>" << std::endl;
    std::cout << "top <dictionary>" << std::endl;
    std::cout << "clear <dictionary>" << std::endl;
    std::cout << "list" << std::endl;
    std::cout << "help" << std::endl;
    std::cout << "exit" << std::endl;
}

int main() {
    DictionaryManager manager;
    std::string line;

    std::cout << "Frequency Dictionary" << std::endl;
    std::cout << "Type 'help' to show commands." << std::endl;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "exit") {
            break;
        } else if (command == "help") {
            printHelp();
        } else if (command == "create") {
            std::string dictionary;
            ss >> dictionary;

            if (dictionary.empty()) {
                std::cout << "Usage: create <dictionary>" << std::endl;
            } else if (manager.createDictionary(dictionary)) {
                std::cout << "Dictionary created." << std::endl;
            } else {
                std::cout << "Dictionary already exists or invalid name." << std::endl;
            }
        } else if (command == "delete") {
            std::string dictionary;
            ss >> dictionary;

            if (dictionary.empty()) {
                std::cout << "Usage: delete <dictionary>" << std::endl;
            } else if (manager.deleteDictionary(dictionary)) {
                std::cout << "Dictionary deleted." << std::endl;
            } else {
                std::cout << "Dictionary not found." << std::endl;
            }
        } else if (command == "load") {
            std::string dictionary, fileName;
            ss >> dictionary >> fileName;

            if (dictionary.empty() || fileName.empty()) {
                std::cout << "Usage: load <dictionary> <file-name>" << std::endl;
            } else {
                int loadedWords = 0;
                if (manager.loadFromFile(dictionary, fileName, loadedWords)) {
                    std::cout << "File loaded. Words added: " << loadedWords << std::endl;
                } else {
                    std::cout << "Operation failed. Check dictionary name or file." << std::endl;
                }
            }
        } else if (command == "insert") {
            std::string dictionary, word;
            ss >> dictionary >> word;

            if (dictionary.empty() || word.empty()) {
                std::cout << "Usage: insert <dictionary> <word>" << std::endl;
            } else if (manager.insertWord(dictionary, word)) {
                std::cout << "Inserted." << std::endl;
            } else {
                std::cout << "Operation failed." << std::endl;
            }
        } else if (command == "search") {
            std::string dictionary, word;
            ss >> dictionary >> word;

            if (dictionary.empty() || word.empty()) {
                std::cout << "Usage: search <dictionary> <word>" << std::endl;
            } else {
                int frequency = 0;
                if (manager.searchWord(dictionary, word, frequency)) {
                    std::cout << word << " -> " << frequency << std::endl;
                } else {
                    std::cout << "Word not found." << std::endl;
                }
            }
        } else if (command == "remove") {
            std::string dictionary, word;
            ss >> dictionary >> word;

            if (dictionary.empty() || word.empty()) {
                std::cout << "Usage: remove <dictionary> <word>" << std::endl;
            } else if (manager.removeWord(dictionary, word)) {
                std::cout << "Removed." << std::endl;
            } else {
                std::cout << "Word not found." << std::endl;
            }
        } else if (command == "show") {
            std::string dictionary;
            ss >> dictionary;

            if (dictionary.empty()) std::cout << "Usage: show <dictionary>" << std::endl;
            else manager.showDictionary(dictionary);
        } else if (command == "top") {
            std::string dictionary;
            ss >> dictionary;

            if (dictionary.empty()) std::cout << "Usage: top <dictionary>" << std::endl;
            else manager.showTopWord(dictionary);
        } else if (command == "clear") {
            std::string dictionary;
            ss >> dictionary;

            if (dictionary.empty()) {
                std::cout << "Usage: clear <dictionary>" << std::endl;
            } else if (manager.exists(dictionary)) {
                manager.clearDictionary(dictionary);
                std::cout << "Dictionary cleared." << std::endl;
            } else {
                std::cout << "Dictionary not found." << std::endl;
            }
        } else if (command == "list") {
            manager.showDictionaries();
        } else {
            std::cout << "Unknown command. Type 'help'." << std::endl;
        }
    }

    std::cout << "Program finished." << std::endl;
    return 0;
}
