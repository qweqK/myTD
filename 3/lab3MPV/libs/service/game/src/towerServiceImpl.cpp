#include "towerServiceImpl.h"
#include "model/repository/attackRegistry.h"

TowerServiceImpl::TowerServiceImpl(TowerRepository &towers_, Map &map_, EnemyRepo &repo_) : towers(towers_), map(map_), enemies(repo_) {}

void TowerServiceImpl::updateTower(float dt) {
    for (auto &tow : towers.getAll()) {
        tow->update(dt);
        PointF pf{static_cast<float>(tow->getPosition().x)+0.5f, static_cast<float>(tow->getPosition().y)+0.5f};
        std::vector<IEnemy*> enemiesT=enemies.getEnemiesInArea(pf,tow->getRange());
        tow->getAttackStrategy()->attack(enemiesT, tow.get());
    }
}






