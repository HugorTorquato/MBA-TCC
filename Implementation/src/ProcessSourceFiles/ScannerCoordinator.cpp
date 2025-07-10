#include "ScannerCoordinator.h"

#include "../Logger/Log.h"
#include "util/ISourceReader.h"

namespace
{
/**
 * @brief Logs a JSON object in a formatted manner.
 *
 * This function takes a JSON object and logs its contents as a formatted string
 * with an indentation level of 4 spaces. The log entry is prefixed with the
 * context "[ScannerCoordinator][printJson]" for easier identification.
 *
 * @param j The JSON object to be logged.
 */
void printJson(const json& j)
{
    Logger::getInstance().log("[ScannerCoordinator][printJson] " + j.dump(4));
}
}  // namespace

ScannerCoordinator::ScannerCoordinator(
    json downloadResult,
    std::function<std::unique_ptr<ISourceReader>(const std::string& filePath)> sourceReaderFactory)
    : m_downloadResult(downloadResult), m_sourceReaderFactory(sourceReaderFactory)
{
    Logger::getInstance().log("[ScannerCoordinator::ScannerCoordinator]");
}

json ScannerCoordinator::downloadAndRetrieveSourceFileContent(const std::string& url) const
{
    Logger::getInstance().log("[ScannerCoordinator][downloadFilesInUrl] url: " + url +
                              " response: " + m_downloadResult.dump());

    json responseResult = json::object();

    for (auto& [key, path] : m_downloadResult.items())
    {
        if (key.rfind("root", 0) == 0) continue;

        auto reader = m_sourceReaderFactory(path);
        std::string readDocument = reader->readFile();

        Logger::getInstance().log(
            "[ScannerCoordinator][downloadAndRetrieveSourceFileContent] readDocument: " +
            readDocument);

        responseResult[key] = readDocument;
    }

    printJson(responseResult);

    return responseResult;
}

// OK I NEED TO LOOP THE JSON FILE TO SEE THE CONTENT.... I MAY NEED TO PROCESS ALL FILES, SO I NEED
// TO SEE IT

// void

// create a test exemple with more than one file to read.
// iMPLEMENT A METHOD TO LOOP THESE JSON RESPONSES
/// ...

// Example to create unit tests
// [ScannerCoordinator][printJson] {
//     "classDef.h:Implementation/observability/source_code_for_testing/ProcessSourceFiles/TwoFileSourceCode/classDef.h":
//     "#pragma once\n\nclass hugo {\n\n};",
//     "main.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/TwoFileSourceCode/main.cpp":
//     "#include \"classDef.h\""
// }
// [ProcessSourceFiles][downloadFilesInUrl] response:
// {"classDef.h:Implementation/observability/source_code_for_testing/ProcessSourceFiles/TwoFileSourceCode/classDef.h":"#pragma
// once\n\nclass hugo
// {\n\n};","main.cpp:Implementation/observability/source_code_for_testing/ProcessSourceFiles/TwoFileSourceCode/main.cpp":"#include
// \"classDef.h\""}

// loop jason content per file
// i also need to collect metadata... linefiles ( line col form beggining and end of each token )

std::string handleValueTypeToString(const json& value)
{
    // Convert the value to a string representation
    if (value.is_string())
    {
        return value.get<std::string>();
    }
    else if (value.is_number())
    {
        // TODO: Handle different number types if necessary ( INT DOUBLE FLOAT )
        return std::to_string(value.get<double>());
    }
    else if (value.is_boolean())
    {
        return value.get<bool>() ? "true" : "false";
    }
    else
    {
        // For other types, use dump to get a JSON string representation
        return value.dump();
    }
}

std::vector<std::pair<std::string, std::string>> ScannerCoordinator::evaluateJsonContent(
    const json& content)
{
    Logger::getInstance().log("[ScannerCoordinator][evaluateJsonContent]");

    if (content.empty())
    {
        Logger::getInstance().log("[ScannerCoordinator][evaluateJsonContent] content is empty");
        return {};
    }

    printJson(content);

    std::vector<std::pair<std::string, std::string>> file_contents;

    Logger::getInstance().log("[ScannerCoordinator][evaluateJsonContent] Type: " +
                              std::string(content.type_name()));

    for (const auto& [key, value] : content.items())
    {
        Logger::getInstance().log("[ScannerCoordinator][evaluateJsonContent] Key: " + key +
                                  " value: " + value.dump());
        std::string adjustedValue = handleValueTypeToString(value);
        file_contents.emplace_back(key, adjustedValue);
    }

    return file_contents;
}

// Here i have
// -> a vector with the name of the file and the raw string content
// -> Return
// -> a list of pairs with the file name and list of tokens for that file

// Call the class scanner for diferen files.

void ScannerCoordinator::groupTokensByFile(
    const std::vector<std::pair<std::string, std::string>> files_with_content)
{
    Logger::getInstance().log("[ScannerCoordinator][groupTokensByFile]");

    for (auto file : files_with_content)
    {
        Logger::getInstance().log("[ScannerCoordinator][groupTokensByFile] file name " +
                                  file.first + " content: " + file.second);
    }

    // TODO: Call scanner in separate threads

    // Create Scanner and Tokens class
}