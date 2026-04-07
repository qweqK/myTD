#pragma once
/**
 * компонент ловушки
 */
class ITrap {
    public:
    virtual ~ITrap()=default;
};


class Trap : public ITrap {
};