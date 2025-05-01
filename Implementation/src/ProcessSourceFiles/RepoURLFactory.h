#pragma once

#include "util/IRepoURL.h"

class RepoURLFactory
{
   public:
    static std::unique_ptr<IRepoURL> createRepoURL(const std::string& url);
};