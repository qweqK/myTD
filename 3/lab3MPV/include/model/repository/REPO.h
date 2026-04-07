#pragma once
#include <memory>
#include <vector>


template<typename T>
class REPO {
    public:
    virtual ~REPO()=default;
    virtual void add(std::unique_ptr<T> object)=0;

    [[nodiscard]]virtual const std::vector<std::unique_ptr<T>>& getAll() const=0;

    [[nodiscard]]virtual  std::vector<std::unique_ptr<T>>& getAllMutable()=0;

    virtual void clear()=0;

};
