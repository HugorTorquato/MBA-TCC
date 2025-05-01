#pragma once

#include <regex>
#include <string>

// Strategy pattern
class IRepoURL
{
   public:
    virtual ~IRepoURL() = default;

    virtual bool isValidUrl(const std::string& url) const = 0;

    virtual std::string getBranch() const = 0;
    virtual std::string getPath() const = 0;
    virtual std::string getRepo() const = 0;
    virtual std::string getUser() const = 0;
    virtual std::string getRegexp() const = 0;

    virtual void parseURL(const std::string& url) = 0;
};