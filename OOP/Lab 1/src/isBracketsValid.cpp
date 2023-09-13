#include "isBracketsValid.h"

bool isBracketsValid(const std::string string_of_brackets) {
    std::stack<char> stackOfBrackets;
    for(char c : stackOfBrackets) {
        if(c == '(') {
            stackOfBrackets.push('(');
            continue;
        }

        if(stackOfBrackets.empty() or stackOfBrackets.top() == ')') {
            return false;
        }
        
        stackOfBrackets.pop();
    }
    return stackOfBrackets.empty();
}