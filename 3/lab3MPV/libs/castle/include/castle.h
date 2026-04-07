#pragma once
#include <string>
#include "model/buildings/Build.h"

/**
 * @brief класс реализующий замок
 */
class Castle: public IBuild {
    std::string name;///< имя замка
    Point Location;///< локация замкаа
    float maxHP;///< макс хп замка
    float currHP;///< текущие хп замка
    int gold;///< золото
    public:
    explicit Castle( std::string name,const Point location,const float maxHP,const float currHP,const int gold): name(std::move(name)), Location(location), maxHP(maxHP), currHP(currHP), gold(gold) {}
    [[nodiscard]]std::string getName() {return name;}
    void setName(const std::string& newname) {name = newname;}

    [[nodiscard]]Point getLocation() const {return Location;}
    void setLocation(const Point newLocation) {Location = newLocation;}

    [[nodiscard]]float getMaxHP() const {return maxHP;}
    void setMaxHP(const float newMaxHP) {maxHP = newMaxHP;}

    [[nodiscard]]float getCurrHP() const {return currHP;}
    void setCurrHP(const float newCurrHP) {currHP = newCurrHP;}

    [[nodiscard]]int getGold() const {return gold;}
    void setGold(const int newGold) {gold = newGold;}

    /**
     *
     * @param damage принять урон
     */
    void takeDamage(float damage) {
        currHP -= damage;
    }

};