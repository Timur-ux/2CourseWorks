#include "brackets_check.h"

bool brackets_check(const std::string s)
{
    std::stack<char> st;
    for(char c : s) {
        switch(c) {
            case '(':
                st.push(c);
                break;
            case ')':
                if(st.empty() || st.top() == ')')
                    return false;
                st.pop();
                break;
            default:
                std::cerr << "brackets_check error: Unknown char in input string" << std::endl;
                return false;
        }
    }
    if(!st.empty())
        return false;
    return true;
}