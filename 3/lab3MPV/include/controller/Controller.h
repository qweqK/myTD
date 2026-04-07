#pragma once
#include "cell/include/cell.h"
#include <string>

/**
 * абстрактный класс - контроллер
 */
class Controller {
    public:
    virtual ~Controller() = default;///< дефолный виртуальный дестрвутор
    virtual void updateLogic(float dt)=0; ///< обновить состояние игры
    virtual bool build(int x, int y,const std::string &type)=0; ///< построитьь башню
    virtual bool sell(int x, int y)=0; ///< продать башню
    virtual TerraType getType(int x, int y) =0; ///< получить тип клетки
    virtual void save(const std::string &path) =0; ///< сохранить состояние играы в файл
    virtual void load(const std::string &path) =0; ///< загрузить из файла состояние играы
    virtual bool levelUp(int x, int y)=0; ///< левел уп бащни
};
