#include "Utils.h"
#include <algorithm>
#include <cctype>
#include <drogon/utils/Utilities.h>
#include <models/Users.h>
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

std::string getUniqueFileName(const std::string_view& fileName)
{
    std::string uniqueFileName{ fileName };
    auto dotIt{ uniqueFileName.find(".") };
    if (dotIt == std::string::npos)
        throw std::logic_error{ "File name without extension!" };
    uniqueFileName.insert(dotIt, "---" + drogon::utils::genRandomString(20));
    return uniqueFileName;
}

void filterUserData(Json::Value& userData)
{
    using namespace drogon_model::augventure_db;
    userData.removeMember(Users::Cols::_auth_code);
    //userData.removeMember(Users::Cols::_id);
    userData.removeMember(Users::Cols::_password);
}

} // namespace utils
} // namespace augventure
