#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <unordered_set>

class Dictionary {
private:
    std::unordered_set<std::string> words_;

public:
    bool load(const std::string& filename);
    bool contains(const std::string& word) const;
    size_t size() const;
    const std::unordered_set<std::string>& words() const;
};

#endif
