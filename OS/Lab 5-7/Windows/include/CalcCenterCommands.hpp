#ifndef CACL_CENTER_COMMANDS_H_
#define CACL_CENTER_COMMANDS_H_
#include <vector>

namespace calc_center_command {
	std::string terminate{ "terminate" };
	std::string exec{ "exec" };
}

namespace calc_center_return {
	std::string execSucceed{"execSucceed"};
	std::string notFound{"notFound"};
}

std::vector<char> strToVChar(std::string s) {
    std::vector<char> result;
    for (char c : s) {
        result.push_back(c);
    }

    return result;
}

#endif // !CACL_CENTER_COMMANDS_H_
