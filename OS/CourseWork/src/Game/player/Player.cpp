#include "Game/player/Player.hpp"
#include <algorithm>

#define min(a, b) (a < b ? a : b)
#define in(container, item) (std::find(std::begin(container), std::end(container), item) != std::end(container))

std::pair<int, int> game::Player::calcCowsAndBulls(std::string otherWord)
{
    if (!word.has_value()) {
        return { 0, 0 };
    }
    std::string word = this->word.value();
    int cows = 0;
    int bulls = 0;

    for (int i = 0; i < min(word.size(), otherWord.size()); ++i) {
        if (word[i] == otherWord[i]) {
            ++bulls;
        }
    }

    std::list<char> wordList;
    for (char c : word) {
        wordList.push_back(c);
    }

    for (char c : otherWord) {
        auto charIt = std::find(std::begin(wordList), std::end(wordList), c);
        if (charIt == std::end(wordList)) {
            continue;
        }

        ++cows;
        wordList.erase(charIt);
    }

    return { cows, bulls };
}