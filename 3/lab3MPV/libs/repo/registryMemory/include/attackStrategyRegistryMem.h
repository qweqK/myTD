
#pragma once
#include "model/repository/attackRegistry.h"

/**
 * реестр стратегий атаки
 */
class AttackStrategyRegistryMem: public AttackRegistry{
    public:
    /**
     * добавить новую стратегию
     */
    void add(std::unique_ptr<AttackStrategy>) override;

    /**
     * @brief получить по ключу
     * @param id ключ
     * @return вернуть сырой указатель
     */
    [[nodiscard]] AttackStrategy* getRaw(const std::string &id) override;
    /**
  * @brief получить по ключу
  * @param id ключ
  * @return вернуть умный указатель
  */
    [[nodiscard]] std::unique_ptr<AttackStrategy> &get(const std::string &id) override;

    /**
     * очмстить реестр
     */
    void clear() override;

    private:
    std::map<std::string, std::unique_ptr<AttackStrategy>> data; ///< мапа стратегий

};