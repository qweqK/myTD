#pragma once
#include <string>

/**
 * @brief класс загрузки состояния программы из файла
 */
class StateService {
    public:
    virtual ~StateService()=default;
    virtual void load(const std::string &path)=0;///<загрузка состояния по пути
    virtual void save(const std::string &path)=0;///<выгрузка состояния программы попути
    virtual void loadMap(const std::string &path)=0;
    virtual void loadEnemy(const std::string &path)=0;
    virtual void loadTower(const std::string &path)=0;
    virtual void loadCastle (const std::string &path)=0;
    virtual void loadLairs(const std::string &path) =0;


};