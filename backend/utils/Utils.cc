#include "Utils.h"
#include <algorithm>
#include <cctype>
#include <unordered_map>

namespace augventure
{

namespace utils
{

bool isImageExtension(const std::string_view& extension)
{
    static std::set<std::string> imageExtensions{ { "jpg", "jpeg", "png",
                                                    "bmp" } };
    std::string lower{ extension };
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](auto c) { return std::tolower(c); });
    return imageExtensions.find(lower) != imageExtensions.end();
}

} // namespace utils
} // namespace augventure
