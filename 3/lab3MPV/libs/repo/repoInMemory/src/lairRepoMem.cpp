#include "lairRepoMem.h"

void LairRepoMem::add(LairPtr object) {
    data.push_back(std::move(object));
}

const std::vector<LairRepository::LairPtr> & LairRepoMem::getAll() const {
    return data;
}
std::vector<LairRepository::LairPtr> & LairRepoMem::getAllMutable() {
    return data;
}
void LairRepoMem::clear() {
    data.clear();
}




