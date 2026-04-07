#include "enemyTypeRegistryMem.h"


void EnemyTypeRegistryMem::add(std::unique_ptr<IEnemy> e) {
    auto [it, success] =data.try_emplace(e->getName(), std::move(e));
    if (!success) throw std::logic_error("Enemy is already registered:" + e->getName());
}

void EnemyTypeRegistryMem::clear() {
    data.clear();
}

std::unique_ptr<IEnemy> &EnemyTypeRegistryMem::get(const std::string &id) {
    return data.at(id);
}

IEnemy *EnemyTypeRegistryMem::getRaw(const std::string &id) {
    return data.at(id).get();
}



