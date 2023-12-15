#include "safeBool.hpp"

SafeBool & SafeBool::operator=(bool other) {
    std::lock_guard<std::shared_mutex> lock(mutex);

    value = other;

    return *this;
}

SafeBool::operator bool() {
    std::shared_lock<std::shared_mutex> lock(mutex);

    return value;
}
