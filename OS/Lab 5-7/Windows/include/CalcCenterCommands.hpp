#ifndef CACL_CENTER_COMMANDS_H_
#define CACL_CENTER_COMMANDS_H_
#include <string>

namespace calc_center_command {
    inline std::string terminate{ "terminate" };
    inline std::string exec{ "exec" };
    inline std::string ping{ "ping" };
};

namespace calc_center_return {
    inline std::string execSucceed{ "Ok" };
    inline std::string notFound{ "NotFound" };
};

#endif // !CACL_CENTER_COMMANDS_H_
