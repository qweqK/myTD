#include "effectStrategyRegistryMem.h"


void EffectBehaviorRegistryMem::add(std::unique_ptr<IEffectBehavior> e) {
    auto [it, success] =data.try_emplace(e->getType(), std::move(e));
    if (!success) throw std::logic_error("Strategy is already registered"+ e->getType());
}

std::unique_ptr<IEffectBehavior>&EffectBehaviorRegistryMem::get(const std::string& id) {
    return  data.at(id);
}

IEffectBehavior * EffectBehaviorRegistryMem::getRaw(const std::string& id) {
    return  data.at(id).get();
}

void EffectBehaviorRegistryMem::clear() {
    data.clear();
}


