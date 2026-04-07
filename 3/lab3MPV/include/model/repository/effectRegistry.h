#pragma once

#include "registry.h"
#include "model/effect/effect.h"

/**
 * хранение эффнктов
 */
class EffectRegistry : public Registry<IEffectBehavior, std::string> {
    public:
    using EffectPtr = std::unique_ptr<IEffectBehavior>;

};