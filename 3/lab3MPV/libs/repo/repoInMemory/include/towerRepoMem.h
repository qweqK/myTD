#pragma once
#include "model/repository/towerRepo.h"

/**
 * @brief репозиторий башен
 */
class TowerRepoMem : public TowerRepository {
    public:
    void add(TowerPtr tow) override; ///<добавить
    [[nodiscard]] const std::vector<TowerPtr> &getAll() const override; ///< полуить вехх
    [[nodiscard]] std::vector<TowerPtr>& getAllMutable() override; ///< получить всех изменяемыз
    void clear() override; ///< очисть
    void removeDead() override; ///< очистьтить умержших


    private:

    std::vector<TowerPtr> data;

};
