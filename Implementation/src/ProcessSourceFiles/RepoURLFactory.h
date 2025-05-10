#pragma once

#include "util/IRepoURL.h"

class RepoURLFactory
{
   public:
    static std::unique_ptr<IRepoURL> createRepoURL(const std::string& url);
    static bool isFromGtHub(const std::string& url);
};