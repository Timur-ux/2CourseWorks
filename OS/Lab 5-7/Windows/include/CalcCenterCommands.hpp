#ifndef CACL_CENTER_COMMANDS_H_
#define CACL_CENTER_COMMANDS_H_
#include <vector>

namespace calc_center_command {
    std::string terminate{ "terminate" };
    std::string exec{ "exec" };
    std::string ping{ "ping" };
};

namespace calc_center_return {
    std::string execSucceed{ "Ok" };
    std::string notFound{ "NotFound" };
};

#endif // !CACL_CENTER_COMMANDS_H_
