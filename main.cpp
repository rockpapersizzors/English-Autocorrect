#include "Dictionary.h"
#include "Autocorrect.h"

#include <iostream>
#include <string>

int main()
{
    Dictionary dict;
    std::string dictFile = "dictionary.txt";

    // Load dictionary
    if (!dict.load(dictFile))
    {
        std::cerr << "Error: Could not load "
                  << dictFile << ".\n";
        return 1;
    }

    // Header
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "       SIMPLE ENGLISH AUTOCORRECT\n";
    std::cout << "========================================\n";
    std::cout << "\n";

    std::string input;

    while (true)
    {
        std::cout << "Enter a sentence:\n> ";

        if (!std::getline(std::cin, input))
            break;

        if (input.empty())
            continue;

        CorrectionResult res = correctSentence(input, dict);

        std::cout << "\n";

        if (res.corrections.empty())
        {
            std::cout << "Your sentence looks correct:\n";
            std::cout << "> " << res.correctedSentence << "\n";
        }
        else
        {
            std::cout << "Did you mean:\n";
            std::cout << "> " << res.correctedSentence << "\n";

            std::cout << "\nCorrections:\n";

            for (const auto& [original, corrected] : res.corrections)
            {
                std::cout << "  "
                          << original
                          << " -> "
                          << corrected
                          << "\n";
            }
        }

        std::cout << "\n";
        std::cout << "----------------------------------------\n\n";
    }

    return 0;
}