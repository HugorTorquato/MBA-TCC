#include "ScannerForConditionMatch.h"

std::string ScannerForConditionMatch::retrieveSourceFileContent(const ISourceReader& reader) const
{
    return reader.readFile();
}