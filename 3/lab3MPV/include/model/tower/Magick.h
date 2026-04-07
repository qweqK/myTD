#pragma once
#include "model/effect/effect.h"
struct EffectConf {
    float duration;
    float strength;

    IEffectBehavior *behavior;
};

/**
 * компонент магии
 */
class IMagickEffect {
    public:
    virtual void setConf(EffectConf newConf)=0;
    [[nodiscard]]virtual const EffectConf & getConf() const =0;
    virtual ~IMagickEffect()=default;
};

class MagickEffect : public IMagickEffect {
protected:
    EffectConf conf;
public:
    explicit MagickEffect(EffectConf newConf): conf(newConf){}

    void setConf(EffectConf newConf) override{
        conf = newConf;
    }

    [[nodiscard]] const EffectConf & getConf() const override{
        return conf;
    }

};

