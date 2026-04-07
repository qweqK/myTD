
#include "gameServiceImpl.h"
GameServiceImpl::GameServiceImpl(EnemyService &enemyService_, TowerService &towerService_, Castle &castle_, TowerRepository &towers_, EnemyRepo &enemies_)
: enemyService(enemyService_), towerService(towerService_), castle(castle_), towers(towers_), enemies(enemies_) {}

void GameServiceImpl::updateGame(float dt) {
   enemyService.CreateAndSpawn(dt);
   enemyService.update(dt);
   enemyService.Move(dt);
   towerService.updateTower(dt);
}

void GameServiceImpl::removeTrash() {
   enemies.removeDead();
   towers.removeDead();
}


Game GameServiceImpl::checkGameState() {
  if (castle.getCurrHP()<=0) return  Game::LOSE;
   return  Game::PROCESS;
}

