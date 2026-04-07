#pragma once

#include "model/repository/findTargetRegistry.h"

/**
 * реестр поиска стратегий
 */
class FindTargetRegistryStrategyMem : public FindTargetRegistry {
    public:
    /**
     * добавить стратегию
     */
    void add(std::unique_ptr<targetFindStrategy>) override;

    /**
    * @brief получить по ключу
    * @param id ключ
    * @return вернуть умный указатель
    */
    std::unique_ptr<targetFindStrategy>& get(const std::string &id) override;
    /**
   * @brief получить по ключу
   * @param id ключ
   * @return вернуть сырой указатель
   */
    targetFindStrategy * getRaw(const std::string &id) override;
    void clear() override;///<очисттть реестр

    private:
    std::map<std::string, std::unique_ptr<targetFindStrategy>> data;

};