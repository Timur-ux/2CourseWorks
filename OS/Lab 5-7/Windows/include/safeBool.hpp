#ifndef SAFE_BOOL_H_
#define SAFE_BOOL_H_

#include <shared_mutex>

class SafeBool {
private:
    std::shared_mutex mutex;
    bool value;
public:
    SafeBool(bool _value) : value(_value) {}

    SafeBool & operator=(bool other);
    operator bool();
};

#endif