#include "attackStrategyRegistryMem.h"

void AttackStrategyRegistryMem::add(std::unique_ptr<AttackStrategy> a) {
    auto [it, success] =data.try_emplace(a->getType(), std::move(a));
    if (!success) throw std::logic_error("Strategy is already registered"+ a->getType());
}

std::unique_ptr<AttackStrategy> &AttackStrategyRegistryMem::get(const std::string &id) {
    return data.at(id);
}

AttackStrategy *AttackStrategyRegistryMem::getRaw(const std::string &id) {
    return data.at(id).get();
}

void AttackStrategyRegistryMem::clear() {
    data.clear();
}

