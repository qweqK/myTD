#pragma once
#include <string>

/**
 * сервис для загрузки конфига
 */
class configLoadService {
    public:
    virtual ~configLoadService() {};
    virtual  void load(const std::string &path)=0;///< загрузка конфига из файла по пути
};