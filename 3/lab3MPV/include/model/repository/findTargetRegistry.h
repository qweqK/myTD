#pragma once

#include "registry.h"
#include "model/targetFindStrategy/targetFindStrategy.h"

/**
 * класс для хранения типов стратегий
 */
class FindTargetRegistry : public Registry<targetFindStrategy, std::string> {
public:
    using attackPtr = std::unique_ptr<targetFindStrategy>;
};


