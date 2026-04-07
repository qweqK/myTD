#include "configServiceImpl.h"

#include <iostream>

#include "dto/EnemyDto.h"
#include "yaml-cpp/yaml.h"
#include <map>

void configLoadServiceImpl::load(const std::string &path) {
 auto config = YAML::LoadFile(path);
 auto enemyNodes = config["enemy"];

 std::vector<std::unique_ptr<IEnemy>> enemies;
 enemies.reserve(enemyNodes.size());

 for (const auto & node : enemyNodes) {
     auto type = node["type"].as<std::string>();
     auto name = node["name"].as<std::string>();
     auto hp = node["health"].as<float>();
     auto speed = node["speed"].as<float>();
     auto gold = node["gold"].as<int>();
     EnemyDto dto{name, type, hp, hp, speed, -10000, -10000, gold};
     auto enemy= enemyMapper.mapFrom(dto);
     enemies.push_back(std::move(enemy));
 }
    enemyTypes.clear();
    for (auto & enemy : enemies) {
        enemyTypes.add(std::move(enemy));
    }

     auto towerNodes = config["tower"];
     std::vector<std::unique_ptr<ITower>> towers;
    towers.reserve(towerNodes.size());
    for (const auto & node : towerNodes) {
        auto type = node["type"].as<std::string>();
        auto cost = node["cost"].as<int>();
        auto range = node["range"].as<int>();
        auto levelMulty = node["levelMult"].as<float>();
        auto properties = node["properties"].as<std::map<std::string, std::string>>();
        auto attackStrategy  = node["attackStrategy"].as<std::string>();
        TowerDTO dto{type, 1, cost, 0, 0, attackStrategy,range,levelMulty, properties};
        auto tower = towerMapper.mapFrom(dto);
        towers.push_back(std::move(tower));
     }
    for (auto & tow : towers) {
        towerTypeRegistry.add(std::move(tow));
    }
}


