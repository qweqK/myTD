
#include "towerTypeRegistryImpl.h"

#include <iostream>

void TowerTypeRegistryImpl::add(std::unique_ptr<ITower> t) {
    auto [it, success] =data.try_emplace(t->getType(), std::move(t));
    if (!success) throw std::logic_error("Strategy is already registered"+ t->getType());
}

std::unique_ptr<ITower> &TowerTypeRegistryImpl::get(const std::string &id) {
    return data.at(id);
}

ITower *TowerTypeRegistryImpl::getRaw(const std::string &id) {
    return data.at(id).get();
}

void TowerTypeRegistryImpl::clear() {
    data.clear();
}





