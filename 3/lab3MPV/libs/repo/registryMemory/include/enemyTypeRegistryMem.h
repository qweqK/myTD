#pragma once
#include "model/repository/enemyTypeRegistry.h"
#include "model/enemy/Enemy.h"

/**
 * реестр типов арвгов
 */
class EnemyTypeRegistryMem : public  EnemyTypeRegistry {
    public:/**
     * @brief получить по ключу
     * @param id ключ
     * @return вернуть умный указатель
     */
    std::unique_ptr<IEnemy> &get(const std::string &id) override;
    /**
   * @brief получить по ключу
   * @param id ключ
   * @return вернуть сырой указатель
   */
    IEnemy *getRaw(const std::string &id) override;

    /**
     * добавить врага
     */
    void add(std::unique_ptr<IEnemy>) override;

    /**
     * очистить
     */
    void clear() override;
    private:

    std::map<std::string, std::unique_ptr<IEnemy>> data;///<мапа типов врагов
};