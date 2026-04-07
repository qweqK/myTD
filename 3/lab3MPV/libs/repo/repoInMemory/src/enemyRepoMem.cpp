#include "enemyRepoMem.h"

void EnemyRepoMem::add(EnemyPtr object) {
    data.push_back(std::move(object));
}

const std::vector<EnemyRepo::EnemyPtr> &EnemyRepoMem::getAll() const {
    return data;
}

std::vector<EnemyRepo::EnemyPtr> &EnemyRepoMem::getAllMutable() {
    return data;
}

 std::vector<IEnemy *> EnemyRepoMem::getEnemiesInArea(PointF p, int radius) {
     std::vector<IEnemy *> result;
    auto r2= static_cast<float>(radius*radius);
    for (const auto &en : data) {
        if (!en->checkDead() && p.distSq(en->getPosition()) <= r2) result.push_back(en.get());
    }
    return result;
}

void EnemyRepoMem::clear() {
    data.clear();
}

void EnemyRepoMem::removeDead() {
    auto it = std::remove_if(data.begin(), data.end(), [](const std::unique_ptr<IEnemy>& enemy) {
        return enemy->checkDead();
    });
    data.erase(it, data.end());
}







