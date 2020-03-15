#pragma once
#include <string>

namespace sssearch {
    int bmSearch(const std::string& text, const std::string& pattern);
    int kmpSearch(const std::string& text, const std::string& pattern);
}
