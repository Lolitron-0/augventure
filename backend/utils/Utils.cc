#include "Utils.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <unordered_map>

namespace augventure
{

namespace utils
{

std::string getMediaTypeString(const std::string_view& extension)
{
    static std::unordered_map<std::string, std::string> fileTypes{
        { { "jpg", "image" },
          { "jpeg", "image" },
          { "png", "image" },
          { "bmp", "image" },
          { "mp4", "video" },
          { "mov", "video" },
          { "mkv", "video" },
          { "webm", "video" },
          { "avi", "video" } }
    };
    std::string lower{ extension };
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](auto c) { return std::tolower(c); });
    try
    {
        return fileTypes.at(lower);
    }
    catch (std::out_of_range)
    {
        return "other";
    }
}

std::string getTimestampedFileName(const std::string_view& fileName)
{
    std::string timestampedFileName{ fileName };
    auto dotIt{ timestampedFileName.find(".") };
    if (dotIt == std::string::npos)
        throw std::logic_error{ "File name without extension!" };
    auto now{ trantor::Date::now() };
    timestampedFileName.insert(
        dotIt, "---" + std::to_string(now.microSecondsSinceEpoch()));
    return timestampedFileName;
}

} // namespace utils
} // namespace augventure
