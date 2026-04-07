#pragma once
#include "REPO.h"
#include "lair/include/lair.h"

/**
 * репозиторий логов
 */
class LairRepository : public REPO<Lair> {
    public:
    using LairPtr = std::unique_ptr<Lair>;

};
