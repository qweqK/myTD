#pragma once

template<typename From, typename To, typename FromWrap=From, typename ToWrap=To>
class Mapper{
    public:
    using ToType = To;
    using FromType = From;
    using FromWrapType = FromWrap;
    using ToWrapType = ToWrap;
    virtual ~Mapper() = default;
    [[nodiscard]] virtual ToWrap mapTo(const From &) const=0;
    [[nodiscard]] virtual FromWrap mapFrom(const To &)const=0;
};

