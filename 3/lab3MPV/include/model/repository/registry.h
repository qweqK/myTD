#pragma once
#include <memory>

template<typename T, typename ID>
class Registry {
    public:
    virtual ~Registry()=default;

    virtual void add(std::unique_ptr<T>)=0;
    [[nodiscard]]virtual std::unique_ptr<T>& get(const ID & id)=0;
    [[nodiscard]] virtual T* getRaw(const ID & id)=0;
    virtual  void clear()=0;


};
