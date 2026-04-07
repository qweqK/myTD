#include "towerRepoMem.h"
#include  <algorithm>

const std::vector<TowerRepository::TowerPtr>& TowerRepoMem::getAll() const {
    return data;
}
std::vector<TowerRepository::TowerPtr>& TowerRepoMem::getAllMutable() {
    return data;
}
void TowerRepoMem::add(TowerPtr tow) {
    data.push_back(std::move(tow));
}
void TowerRepoMem::clear() {
    data.clear();
}

void TowerRepoMem::removeDead() {
    auto it = std::remove_if(data.begin(), data.end(), [](const std::unique_ptr<ITower> & tower) {
        return tower->checkDead();
    });
    data.erase(it, data.end());
}




