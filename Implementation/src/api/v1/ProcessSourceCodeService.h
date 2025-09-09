#pragma once
#include <memory>
#include <string>

#include "/app/includes/nlohmann/json.hpp"  // https://github.com/nlohmann/json

using json = nlohmann::json;

class ProcessSourceCodeService
{
   public:
    json process(const std::string& gitUrl);
};
