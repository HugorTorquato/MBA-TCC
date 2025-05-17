#pragma once

#include <string>

#include "util/ISourceReader.h"

class IScanner
{
   public:
    virtual ~IScanner() = default;

    virtual std::string retrieveSourceFileContent(const ISourceReader& reader) const = 0;
};