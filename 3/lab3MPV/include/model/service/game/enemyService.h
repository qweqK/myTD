#pragma once
#include "model/enemy/Enemy.h"
#include "dto/EnemyDto.h"

/**
 * сервис для обработки врагов
 */
class EnemyService {
public:
    virtual void CreateAndSpawn(float dt)=0;///<создание и расположениеврага
    virtual void Move(float dt)=0;///< паередвидение врага
    virtual ~EnemyService()=default;
    virtual void update(float dt)=0;///< обновление логики врага

};