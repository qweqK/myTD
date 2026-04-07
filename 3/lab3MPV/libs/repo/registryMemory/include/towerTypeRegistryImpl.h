#pragma once

#include <map>
#include "model/repository/towerTypeRegistry.h"

/**
 * @brief реестр типов башен
 */
class TowerTypeRegistryImpl: public  TowerTypeRegistry{
    std::map<std::string, std::unique_ptr<ITower>> data;
    public:
    /**
     * добавить башню
     */
    void add(std::unique_ptr<ITower>) override;

    /**
     * очистить реестр
     */
    void clear() override;
    /**
   * @brief получить по ключу
   * @param id ключ
   * @return вернуть умный указатель
   */
    std::unique_ptr<ITower> &get(const std::string &id) override;
    /**
   * @brief получить по ключу
   * @param id ключ
   * @return вернуть сырой указатель
   */
    ITower *getRaw(const std::string &id) override;
};