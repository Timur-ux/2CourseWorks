#include "brackets_check.h"

bool brackets_check(const std::string string_of_brackets)
{
    std::stack<char> stack_of_brackets;
    for(char c : string_of_brackets) {
        if(c == '(') {
            stack_of_brackets.push('(');
            continue;
        }

        if(stack_of_brackets.empty() or stack_of_brackets.top() == ')')
            return false;
        
        stack_of_brackets.pop();
    }
    return stack_of_brackets.empty() ? true : false;
}