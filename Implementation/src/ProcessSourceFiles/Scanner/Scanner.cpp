#include "Scanner.h"

#include "../../Logger/Log.h"

std::vector<std::string> Scanner::scanTokens(const std::string& rawSourceCode) const
{
    Logger::getInstance().log("[Scanner][scanTokens] rawSourceCode: " + rawSourceCode);

    if (rawSourceCode.empty())
    {
        Logger::getInstance().log("[Scanner][scanTokens] rawSourceCode is empty");
        return {};
    }

    // TODO: Implement token scanning logic
    return {};
}
