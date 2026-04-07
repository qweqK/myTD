#include "findTargetStrategyRegistry.h"

void FindTargetRegistryStrategyMem::add(std::unique_ptr<targetFindStrategy> f) {
    auto [it, success] =data.try_emplace(f->getType(), std::move(f));
    if (!success) throw std::logic_error("Strategy is already registered"+ f->getType());
}

std::unique_ptr<targetFindStrategy> &FindTargetRegistryStrategyMem::get(const std::string &id) {
    return data.at(id);
}

targetFindStrategy *FindTargetRegistryStrategyMem::getRaw(const std::string &id) {
    return data.at(id).get();
}

void FindTargetRegistryStrategyMem::clear() {
    data.clear();
}



