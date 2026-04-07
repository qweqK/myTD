#pragma once
#include <map>
#include <string>

#include "registry.h"
#include "model/attackStrategy/AttackStrategy.h"

/**
 * асбтрактный класс для хранение стратегий атаки
 */
class AttackRegistry : public Registry<AttackStrategy, std::string> {
    public:
    using attackPtr = std::unique_ptr<AttackStrategy>;

};