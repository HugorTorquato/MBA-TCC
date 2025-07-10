#pragma once

#include <string>

#include "/app/includes/nlohmann/json.hpp"  // https://github.com/nlohmann/json
#include "util/ISourceReader.h"

using json = nlohmann::json;

class IScannerCoordinator
{
   public:
    virtual ~IScannerCoordinator() = default;

    virtual json downloadAndRetrieveSourceFileContent(const std::string& url) const = 0;
    virtual std::vector<std::pair<std::string, std::string>> evaluateJsonContent(
        const json& content) = 0;
};