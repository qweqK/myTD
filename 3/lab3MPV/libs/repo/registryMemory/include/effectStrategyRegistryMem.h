#pragma once
#include "model/repository/effectRegistry.h"
#include <map>

/**
 * реестр поведений эфектов
 */
class EffectBehaviorRegistryMem : public EffectRegistry {
    public:
    /**
     * добавить новую стратегию
     */
    void add(std::unique_ptr<IEffectBehavior>) override;
    /**
   * @brief получить по ключу
   * @param id ключ
   * @return вернуть сырой указатель
   */
   [[nodiscard]] std::unique_ptr<IEffectBehavior> &get(const std::string &id) override;
    /**
   * @brief получить по ключу
   * @param id ключ
   * @return вернуть умный указатель
   */
    [[nodiscard]]IEffectBehavior * getRaw(const std::string &id) override;
    void clear() override; ///< очистить реесктр
    private:
    std::map<std::string, std::unique_ptr<IEffectBehavior>> data;///< мапа эффектов

};