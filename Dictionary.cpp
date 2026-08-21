#include "Dictionary.h"
#include <fstream>
#include <algorithm>
#include <cctype>

bool Dictionary::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    words_.clear();
    std::string word;
    while (file >> word) {
        std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {
            return std::tolower(c);
        });
        if (!word.empty()) {
            words_.insert(word);
        }
    }
    return true;
}

bool Dictionary::contains(const std::string& word) const {
    std::string lowerWord = word;
    std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return words_.find(lowerWord) != words_.end();
}

size_t Dictionary::size() const {
    return words_.size();
}

const std::unordered_set<std::string>& Dictionary::words() const {
    return words_;
}