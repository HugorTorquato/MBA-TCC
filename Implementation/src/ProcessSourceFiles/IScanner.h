#pragma once

#include <string>

#include "/app/includes/nlohmann/json.hpp"  // https://github.com/nlohmann/json
#include "util/ISourceReader.h"

using json = nlohmann::json;

class IScanner
{
   public:
    virtual ~IScanner() = default;

    virtual json downloadAndRetrieveSourceFileContent(const std::string& url) const = 0;
    virtual void evaluateJsonContent(const json& content) = 0;
};