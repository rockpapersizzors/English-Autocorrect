#include "Autocorrect.h"
#include "Levenshtein.h"
#include <cctype>
#include <algorithm>
#include <cstdlib>


struct Token {
    std::string text;
    bool isWord;
};

static std::string applyCapitalization(const std::string& original, const std::string& target) {
    if (original.empty() || target.empty()) return target;

    bool allUpper = true;
    for (char c : original) {
        if (!std::isupper(static_cast<unsigned char>(c))) {
            allUpper = false;
            break;
        }
    }

    std::string result = target;
    if (allUpper) {
        for (char& c : result) c = std::toupper(static_cast<unsigned char>(c));
    } else if (std::isupper(static_cast<unsigned char>(original[0]))) {
        result[0] = std::toupper(static_cast<unsigned char>(result[0]));
    } else {
        for (char& c : result) c = std::tolower(static_cast<unsigned char>(c));
    }

    return result;
}

static std::vector<Token> tokenize(const std::string& sentence) {
    std::vector<Token> tokens;
    std::string current;
    bool inWord = false;

    for (char c : sentence) {
        bool charIsAlpha = std::isalpha(static_cast<unsigned char>(c));
        if (current.empty()) {
            inWord = charIsAlpha;
            current += c;
        } else if (charIsAlpha == inWord) {
            current += c;
        } else {
            tokens.push_back({current, inWord});
            current = c;
            inWord = charIsAlpha;
        }
    }
    if (!current.empty()) {
        tokens.push_back({current, inWord});
    }

    return tokens;
}

std::string correctWord(
    const std::string& word,
    const Dictionary& dictionary,
    int maxDistance)
{
    std::string lowerWord = word;

    std::transform(
        lowerWord.begin(),
        lowerWord.end(),
        lowerWord.begin(),
        [](unsigned char c) {
            return std::tolower(c);
        }
    );

    // Word is already correct
    if (dictionary.contains(lowerWord)) {
        return word;
    }

    std::string bestMatch = word;
    int minDistance = maxDistance + 1;

    for (const auto& dictWord : dictionary.words())
    {
        // Ignore words that are too different in length
        int lengthDifference =
            std::abs(
                static_cast<int>(lowerWord.length()) -
                static_cast<int>(dictWord.length())
            );

        if (lengthDifference > 2)
            continue;

        int dist = levenshteinDistance(lowerWord, dictWord);

        if (dist < minDistance)
        {
            minDistance = dist;
            bestMatch = dictWord;
        }
    }

    if (minDistance <= maxDistance)
    {
        return applyCapitalization(word, bestMatch);
    }

    return word;
}

CorrectionResult correctSentence(const std::string& sentence, const Dictionary& dictionary) {
    CorrectionResult result;
    auto tokens = tokenize(sentence);

    for (auto& token : tokens) {
        if (token.isWord) {
            std::string corrected = correctWord(token.text, dictionary);
            if (corrected != token.text) {
                result.corrections.push_back({token.text, corrected});
                token.text = corrected;
            }
        }
        result.correctedSentence += token.text;
    }

    return result;
}