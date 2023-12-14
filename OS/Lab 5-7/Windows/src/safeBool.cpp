#include "safeBool.hpp"

SafeBool & SafeBool::operator=(bool other) {
    std::unique_lock<std::shared_mutex> lock(mutex);

    value = other;
}

SafeBool::operator bool() {
    std::shared_lock<std::shared_mutex> lock(mutex);

    return value;
}
