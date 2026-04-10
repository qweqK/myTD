#pragma once
#include <string>
#include <typeindex>
#include <map>
#include "mapper.h"

template<typename From, typename To, typename FromWrap=From, typename ToWrap=To, typename Key=std::string>
class SubtypeMapper: public Mapper<From, To, FromWrap, ToWrap> {
    public:
    using KeyType=Key;
    [[nodiscard]] virtual Key getKey() const=0;
    [[nodiscard]] virtual std::type_index getType() const=0;

};

template<typename From, typename To, typename FromWrap=From, typename ToWrap=To, typename Key=std::string>
class PolymorphicMapper: public Mapper<From, To, FromWrap, ToWrap> {
    public:
    using Supertype = Mapper<From, To, FromWrap, ToWrap>;
    using Subtype = SubtypeMapper<From, To, FromWrap, ToWrap, Key>;

    void addSubMapper(const Subtype& subMapper) {
        concreteMappersByKey_.emplace(subMapper.getKey(), std::ref(subMapper));
        concreteMappersByType_.emplace(subMapper.getType(), std::ref(subMapper));

    }
    [[nodiscard]] virtual Key getKey(const To&) const=0;

    [[nodiscard]] ToWrap mapTo(const From& from) const override {
        std::type_index type= typeid(from);
        return concreteMappersByType_.at(type).get().mapTo(from);

    }
    [[nodiscard]] FromWrap mapFrom(const To& to) const override {
        auto key= getKey(to);
        return concreteMappersByKey_.at(key).get().mapFrom(to);
    }


    private:
    std::map<Key, std::reference_wrapper<const Subtype>> concreteMappersByKey_;
    std::map<std::type_index, std::reference_wrapper<const Subtype>> concreteMappersByType_;

};

template<typename M>
concept IsSubmaper = requires(M v)
{
    requires std::derived_from<M, SubtypeMapper<typename M::FromType, typename M::ToType, typename M::FromWrapType, typename M::ToWrapType>>;
};

template<typename SuperFrom, typename SuperFromWrap, IsSubmaper SubMapper>
class SubtypeMapperAdapter final: public SubtypeMapper<SuperFrom, typename SubMapper::ToType, SuperFromWrap, typename SubMapper::ToWrapType, typename SubMapper::KeyType> {
    SubMapper sub_;
    using Super = SubtypeMapper<SuperFrom, typename SubMapper::ToType, SuperFromWrap, typename SubMapper::ToWrapType, typename SubMapper::KeyType>;

public:

template<typename...Args>
    explicit SubtypeMapperAdapter(Args&&... args)
    requires std::constructible_from<SubMapper, Args&&...>:
    sub_(std::forward<Args>(args)...) {}

    [[nodiscard]] Super::ToWrapType mapTo(const Super::FromType & from) const override {
        return sub_.mapTo(dynamic_cast<const SubMapper::FromType&>(from));
}
    [[nodiscard]] Super::FromWrapType mapFrom(const Super::ToType & to) const override {
    return sub_.mapFrom(to);
}

    [[nodiscard]] Super::KeyType getKey() const override {
    return sub_.getKey();
}
    [[nodiscard]] std::type_index getType() const override {
    return sub_.getType();
}


};





