#include "DictionaryManager.h"
#include "TextProcessor.h"
#include <iostream>

DictionaryManager::DictionaryManager() {}

int DictionaryManager::findDictionaryIndex(const std::string& name) const {
    for (int i = 0; i < static_cast<int>(dictionaries.size()); i++) {
        if (dictionaries[i].name == name) return i;
    }
    return -1;
}

bool DictionaryManager::createDictionary(const std::string& name) {
    if (name.empty() || exists(name)) return false;
    dictionaries.push_back(Dictionary(name));
    return true;
}

bool DictionaryManager::deleteDictionary(const std::string& name) {
    int index = findDictionaryIndex(name);
    if (index == -1) return false;

    dictionaries.erase(dictionaries.begin() + index);
    return true;
}

bool DictionaryManager::exists(const std::string& name) const {
    return findDictionaryIndex(name) != -1;
}

bool DictionaryManager::insertWord(const std::string& dictionaryName, const std::string& word) {
    int index = findDictionaryIndex(dictionaryName);
    if (index == -1) return false;

    std::string cleaned = TextProcessor::cleanWord(word);
    return dictionaries[index].table.insert(cleaned);
}

bool DictionaryManager::removeWord(const std::string& dictionaryName, const std::string& word) {
    int index = findDictionaryIndex(dictionaryName);
    if (index == -1) return false;

    std::string cleaned = TextProcessor::cleanWord(word);
    return dictionaries[index].table.remove(cleaned);
}

bool DictionaryManager::searchWord(const std::string& dictionaryName, const std::string& word, int& frequency) const {
    int index = findDictionaryIndex(dictionaryName);
    if (index == -1) return false;

    std::string cleaned = TextProcessor::cleanWord(word);
    return dictionaries[index].table.search(cleaned, frequency);
}

bool DictionaryManager::loadFromFile(const std::string& dictionaryName, const std::string& fileName, int& loadedWords) {
    int index = findDictionaryIndex(dictionaryName);
    loadedWords = 0;

    if (index == -1) return false;

    std::vector<std::string> words = TextProcessor::loadWords(fileName);
    if (words.empty()) return false;

    for (const std::string& word : words) {
        if (dictionaries[index].table.insert(word)) loadedWords++;
    }

    return true;
}

void DictionaryManager::showDictionary(const std::string& dictionaryName) const {
    int index = findDictionaryIndex(dictionaryName);

    if (index == -1) {
        std::cout << "Dictionary not found." << '\n';
        return;
    }

    std::cout << "Dictionary: " << dictionaries[index].name << '\n';
    dictionaries[index].table.show();
}

void DictionaryManager::showTopWord(const std::string& dictionaryName) const {
    int index = findDictionaryIndex(dictionaryName);

    if (index == -1) {
        std::cout << "Dictionary not found." << '\n';
        return;
    }

    std::pair<std::string, int> top = dictionaries[index].table.topWord();

    if (top.second == 0) {
        std::cout << "Dictionary is empty." << '\n';
    } else {
        std::cout << top.first << " -> " << top.second << '\n';
    }
}

void DictionaryManager::clearDictionary(const std::string& dictionaryName) {
    int index = findDictionaryIndex(dictionaryName);
    if (index != -1) dictionaries[index].table.clear();
}

void DictionaryManager::showDictionaries() const {
    if (dictionaries.empty()) {
        std::cout << "No dictionaries." << '\n';
        return;
    }

    std::cout << "Dictionaries:" << '\n';
    for (const Dictionary& dictionary : dictionaries) {
        std::cout << dictionary.name << " (" << dictionary.table.size() << " unique words)" << '\n';
    }
}

int DictionaryManager::count() const {
    return static_cast<int>(dictionaries.size());
}
