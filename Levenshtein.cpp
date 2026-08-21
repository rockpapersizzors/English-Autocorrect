#include "Levenshtein.h"
#include <vector>
#include <algorithm>

int levenshteinDistance(const std::string& a, const std::string& b) {
    size_t m = a.length();
    size_t n = b.length();

    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (size_t i = 0; i <= m; ++i) dp[i][0] = static_cast<int>(i);
    for (size_t j = 0; j <= n; ++j) dp[0][j] = static_cast<int>(j);

   for (size_t i = 1; i <= m; ++i) {
    for (size_t j = 1; j <= n; ++j) {

        if (a[i - 1] == b[j - 1]) {
            dp[i][j] = dp[i - 1][j - 1];
        }
        else {
            dp[i][j] = 1 + std::min({
                dp[i - 1][j],     // deletion
                dp[i][j - 1],     // insertion
                dp[i - 1][j - 1]  // substitution
            });
        }

        // Transposition
        if (i > 1 && j > 1 &&
            a[i - 1] == b[j - 2] &&
            a[i - 2] == b[j - 1])
        {
            dp[i][j] = std::min(
                dp[i][j],
                dp[i - 2][j - 2] + 1
            );
        }
    }
}

    return dp[m][n];
}