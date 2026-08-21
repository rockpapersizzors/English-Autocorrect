#ifndef AUTOCORRECT_H
#define AUTOCORRECT_H

#include "Dictionary.h"
#include <string>
#include <vector>
#include <utility>

struct CorrectionResult {
    std::string correctedSentence;
    std::vector<std::pair<std::string, std::string>> corrections;
};

std::string correctWord(
    const std::string& word,
    const Dictionary& dictionary,
    int maxDistance = 2
);

CorrectionResult correctSentence(
    const std::string& sentence,
    const Dictionary& dictionary
);

#endif