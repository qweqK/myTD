#pragma once
#include "model/repository/lairRepo.h"

/**
 * @brief репозиторий логов
 */
class LairRepoMem : public LairRepository {
public:
    void add(LairPtr object) override;///<добавть
    void clear() override;///< очистить репо
    [[nodiscard]]const std::vector<LairPtr> & getAll() const override;///< вщятьвсех
    [[nodiscard]]std::vector<LairPtr> & getAllMutable() override; ///< дать всех


private:
    std::vector<LairPtr> data;

};
