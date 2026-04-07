#include "stateServiceImpl.h"
#include "nlohmann/json.hpp"
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <iostream>

//#include "../../../../../cmake-build-debug-coverage/_deps/catch2-src/src/catch2/catch_test_macros.hpp"
#include "dto/TowerDto.h"

StateServiceImpl::StateServiceImpl(TowerRepository &towers_, Map &map_, EnemyRepo &enemies_, Castle &castle_, LairRepository &lairs_, EnemyMapper & eMapper_, EnemyTypeRegistry & enemyTypes_, TowerMapper & towerMapper_) :
towers(towers_), map(map_), enemies(enemies_), castle(castle_), lairs(lairs_), enemyMapper(eMapper_), enemyTypes(enemyTypes_), towerMapper(towerMapper_) {}

void StateServiceImpl::load(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Can't open file " + path);
    nlohmann::json j;
    file >> j;
    enemies.clear();
    lairs.clear();
    towers.clear();
    std::cout << "1"<< std::endl;
    auto castleJson = j.at("castle");

    int money = castleJson.at("money").get<int>();
    float maxHp = castleJson.at("maxHp").get<float>();
    float hp = castleJson.at("Hp").get<float>();
    std::string castleName = castleJson.at("name").get<std::string>();
    int Cx = castleJson.at("x").get<int>();
    int Cy = castleJson.at("y").get<int>();
    castle.setGold(money);
    castle.setCurrHP(hp);
    castle.setMaxHP(maxHp);
    castle.setName(castleName);
    castle.setLocation({Cx, Cy});
    std::cout << "2"<< std::endl;

    auto enemiesJson = j.at("enemies");
    for (const auto & e: enemiesJson) {
        auto type = e.at("type").get<std::string>();
        auto enemyName = e.at("name").get<std::string>();
        auto enemyGold = e.at("gold").get<int>();
        auto curEnemyHp = e.at("curHp").get<float>();
        auto enemyHp = e.at("maxHp").get<float>();
        auto enemySpeed = e.at("speed").get<float>();
        auto xE = e.at("x").get<float>();
        auto yE = e.at("y").get<float>();
        auto effectsJson = e.at("effects");
        std::map<std::string, std::pair<float, float>> effects;
        for (const auto & ef: effectsJson) {
            auto effectType = ef.at("type").get<std::string>();
            auto duration = ef.at("duration").get<float>();
            auto strength = ef.at("strength").get<float>();
            effects[effectType] = std::make_pair( strength, duration);
        }
        EnemyDto enDto{enemyName, type, curEnemyHp, enemyHp, enemySpeed, xE, yE, enemyGold,effects};
        std::unique_ptr<IEnemy> enemy = enemyMapper.mapFrom(enDto);
        enemies.add(std::move(enemy));

    }

    std::cout << "3"<< std::endl;

    auto lairsJson=  j.at("lairs");
    for (const auto & lair : lairsJson) {
        auto xL = lair.at("x").get<int>();
        auto yL = lair.at("y").get<int>();
        auto lairTime = lair.at("time").get<float>();

        auto enemiesWithTimeJson = lair.at("enemies");
        std::deque<std::unique_ptr<IEnemy>> spawnEnemies;
        std::deque<float> times;

        for (const auto & enemy : enemiesWithTimeJson) {
            auto type = enemy.at("type").get<std::string>();
            auto releaseTime = enemy.at("releaseTime").get<float>();
            std::unique_ptr<IEnemy> spawnEnemy = enemyTypes.get(type)->clone();
            spawnEnemies.push_back(std::move(spawnEnemy));
            times.push_back(releaseTime);

        }
        std::unique_ptr<Lair> concreteLair = std::make_unique<Lair>(std::move(times),std::move(spawnEnemies), Point{xL, yL}, lairTime);
        lairs.add(std::move(concreteLair));
    }

    std::cout << "4"<< std::endl;

    auto towersJson = j.at("towers");
    for (const auto & tower : towersJson) {
        auto type = tower.at("type").get<std::string>();
        auto level = tower.at("level").get<int>();
        auto cost = tower.at("cost").get<int>();
        auto xT = tower.at("x").get<int>();
        auto yT = tower.at("y").get<int>();
        auto attackStrategy = tower.at("attackStrategy").get<std::string>();
        auto range = tower.at("range").get<int>();
        auto levelUpMulty = tower.at("levelUpMulti").get<float>();
        auto properties = tower.at("properties").get<std::map<std::string,std::string>>();
        TowerDTO dto{type, level, cost, xT, yT, attackStrategy, range, levelUpMulty, properties};
        std::unique_ptr<ITower> tow= towerMapper.mapFrom(dto);
        towers.add(std::move(tow));
    }
    std::cout << "5"<< std::endl;
    auto mapJson = j.at("map");

    size_t width = mapJson.at("width").get<size_t>();
    size_t height = mapJson.at("height").get<size_t>();

    std::vector<int> mapa = mapJson.at("data").get<std::vector<int>>();
    std::vector<Cell> cells;
    cells.reserve(height*width);


    for (int i = 0; i< height*width; i++) {
        int x= i%width;
        int y= i/width;
        TerraType type;
        if (mapa.at(i)==0) type = TerraType::field;
        else if (mapa.at(i)==1) type = TerraType::forest;
        else if (mapa.at(i)==2) type = TerraType::road;
        else throw std::runtime_error("invalid map index " + std::to_string(i));

        Cell curCell{{x, y}, type};
        cells.push_back(curCell);
    }
    Map mapp{width, height, cells};
    map = std::move(mapp);
    std::cout << "6"<< std::endl;
    for ( auto & cell : map.getCells()) {
        auto & tow = towers.getAll();
        auto it =std::find_if(tow.begin(), tow.end(), [&cell](const std::unique_ptr<ITower> & a) {
            return a->getPosition()==cell.pos;
        });
        if (it != tow.end()) {
            cell.build = (*it).get();
        }

        auto &lairase = lairs.getAll();
        auto ite = std::find_if(lairase.begin(), lairase.end(), [&cell](const std::unique_ptr<Lair> & a) {
            return a->getPos()==cell.pos;
        });
        if (ite != lairase.end()) {
            cell.build = (*ite).get();
        }
        std::cout << "7"<< std::endl;

    }
    map.at(castle.getLocation().x, castle.getLocation().y ).build = &castle;

    std::cout << "8"<< std::endl;

}




void StateServiceImpl::save(const std::string &path) {
    nlohmann::json j;

    j["castle"] = {
        {"money", castle.getGold()},
        {"maxHp", castle.getMaxHP()},
        {"Hp", castle.getCurrHP()},
        {"name", castle.getName()},
        {"x", castle.getLocation().x},
        {"y", castle.getLocation().y}

    };

    j["map"]["width"] = map.getCols();
    j["map"]["height"] = map.getRows();

    std::vector<int> data;

    data.reserve(map.getCols() * map.getRows());

    //for (const Cell & c : map.getCells()) {
    for (int y=0;y<map.getRows();y++) {
        for (int x=0;x<map.getCols();x++) {
            Cell & c = map.at(x, y);
            int v = 0;
            switch (c.getTerra()) {
                case TerraType::field: v = 0; break;
                case TerraType::forest: v = 1; break;
                case TerraType::road: v = 2; break;
                default: throw std::invalid_argument("No terra found");


            }
            data.push_back(v);
        }
    }

    j["map"]["data"] = data;

    j["enemies"]= nlohmann::json::array();

    for (const auto & enemy : enemies.getAll()) {
        EnemyDto dto = enemyMapper.mapTo(*enemy);
        nlohmann::json je;
        je["name"] = dto.name;
        je["type"] = dto.type;
        je["curHp"]= dto.curHp;
        je["maxHp"] = dto.maxHp;
        je["x"] = dto.posX;
        je["y"] = dto.posY;
        je["gold"] = dto.gold;
        je["speed"] = dto.speed;

        nlohmann::json effects = nlohmann::json::array();
        for (auto & ef : dto.effectTable) {
            effects.push_back({
                {"type", ef.first},
                {"strength", ef.second.first},
                {"duration", ef.second.second},
            });
        }
        je["effects"] = effects;
        j["enemies"].push_back(je);

    }

    j["lairs"] = nlohmann::json::array();

    for (const auto &lair : lairs.getAll()) {
        nlohmann::json jl;

        jl["x"] = lair->getPos().x;
        jl["y"] = lair->getPos().y;
        jl["time"] = lair->getTime();

        nlohmann::json spawn = nlohmann::json::array();

        const auto& times = lair->getTimes();
        const auto& spawns = lair->getSpawnEnemies();

        for (size_t i = 0; i < spawns.size(); i++) {
            spawn.push_back({
               {"type", spawns[i]->getName()},
                {"releaseTime", times[i]}
            });
        }
        jl["enemies"] = spawn;
        j["lairs"].push_back(jl);
    }

    j["towers"]=nlohmann::json::array();
    for (const auto & tow : towers.getAll()) {
        nlohmann::json jT;

        TowerDTO towDto = towerMapper.mapTo(*tow);
        jT["type"] = towDto.type;
        jT["level"] = towDto.level;
        jT["cost"] = towDto.cost;
        jT["x"] = towDto.xPos;
        jT["y"] = towDto.yPos;
        jT["attackStrategy"] = towDto.attackStrategy;
        jT["range"] = towDto.range;
        jT["levelUpMulti"] = towDto.levelMulty;
        jT["properties"] = towDto.properties;
        j["towers"].push_back(jT);
    }

    std::ofstream file(path);
    if (!file) throw std::runtime_error("unable to write to file");
    file << j.dump(4);
}



void StateServiceImpl::loadMap(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Can't open file " + path);
    nlohmann::json j;
    file >> j;
    auto mapJson = j.at("map");

    size_t width = mapJson.at("width").get<size_t>();
    size_t height = mapJson.at("height").get<size_t>();

    std::vector<int> mapa = mapJson.at("data").get<std::vector<int>>();
    std::vector<Cell> cells;
    cells.reserve(height*width);


    for (int i = 0; i< height*width; i++) {
        int x= i%width;
        int y= i/width;
        TerraType type;
        if (mapa.at(i)==0) type = TerraType::field;
        else if (mapa.at(i)==1) type = TerraType::forest;
        else if (mapa.at(i)==2) type = TerraType::road;
        else throw std::runtime_error("invalid map index " + std::to_string(i));

        Cell curCell{{x, y}, type};
        cells.push_back(curCell);
    }
    Map mapp{width, height, cells};
    map = std::move(mapp);
     for ( auto & cell : map.getCells()) {
         auto & tow = towers.getAll();
         auto it =std::find_if(tow.begin(), tow.end(), [&cell](const std::unique_ptr<ITower> & a) {
             return a->getPosition()==cell.pos;
         });
         if (it != tow.end()) {
             cell.build = (*it).get();
         }

         auto &lairase = lairs.getAll();
         auto ite = std::find_if(lairase.begin(), lairase.end(), [&cell](const std::unique_ptr<Lair> & a) {
             return a->getPos()==cell.pos;
         });
         if (ite != lairase.end()) {
             cell.build = (*ite).get();
         }


     }
        map.at(castle.getLocation().x, castle.getLocation().y ).build = &castle;

}


void StateServiceImpl::loadEnemy(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Can't open file " + path);
    nlohmann::json j;
    file >> j;

    auto enemiesJson = j.at("enemies");
    for (const auto & e: enemiesJson) {
        auto type = e.at("type").get<std::string>();
        auto enemyName = e.at("name").get<std::string>();
        auto enemyGold = e.at("gold").get<int>();
        auto curEnemyHp = e.at("curHp").get<float>();
        auto enemyHp = e.at("maxHp").get<float>();
        auto enemySpeed = e.at("speed").get<float>();
        auto xE = e.at("x").get<float>();
        auto yE = e.at("y").get<float>();
        auto effectsJson = e.at("effects");
        std::map<std::string, std::pair<float, float>> effects;
        for (const auto & ef: effectsJson) {
            auto effectType = ef.at("type").get<std::string>();
            auto duration = ef.at("duration").get<float>();
            auto strength = ef.at("strength").get<float>();
            effects[effectType] = std::make_pair( strength, duration);
        }
        EnemyDto enDto{enemyName, type, curEnemyHp, enemyHp, enemySpeed, xE, yE, enemyGold,effects};
        std::unique_ptr<IEnemy> enemy = enemyMapper.mapFrom(enDto);
        enemies.add(std::move(enemy));

    }

}

void StateServiceImpl::loadTower(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Can't open file " + path);
    nlohmann::json j;
    file >> j;

    auto towersJson = j.at("towers");
    for (const auto & tower : towersJson) {
        auto type = tower.at("type").get<std::string>();
        auto level = tower.at("level").get<int>();
        auto cost = tower.at("cost").get<int>();
        auto xT = tower.at("x").get<int>();
        auto yT = tower.at("y").get<int>();
        auto attackStrategy = tower.at("attackStrategy").get<std::string>();
        auto range = tower.at("range").get<int>();
        auto levelUpMulty = tower.at("levelUpMulti").get<float>();
        auto properties = tower.at("properties").get<std::map<std::string,std::string>>();
        TowerDTO dto{type, level, cost, xT, yT, attackStrategy, range, levelUpMulty, properties};
        std::unique_ptr<ITower> tow= towerMapper.mapFrom(dto);
        towers.add(std::move(tow));
    }
}


void StateServiceImpl::loadCastle(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Can't open file " + path);
    nlohmann::json j;
    file >> j;

    auto castleJson = j.at("castle");

    int money = castleJson.at("money").get<int>();
    float maxHp = castleJson.at("maxHp").get<float>();
    float hp = castleJson.at("Hp").get<float>();
    std::string castleName = castleJson.at("name").get<std::string>();
    int Cx = castleJson.at("x").get<int>();
    int Cy = castleJson.at("y").get<int>();
    castle.setGold(money);
    castle.setCurrHP(hp);
    castle.setMaxHP(maxHp);
    castle.setName(castleName);
    castle.setLocation({Cx, Cy});
}

void StateServiceImpl::loadLairs(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Can't open file " + path);
    nlohmann::json j;
    file >> j;

    auto lairsJson=  j.at("lairs");
    for (const auto & lair : lairsJson) {
        auto xL = lair.at("x").get<int>();
        auto yL = lair.at("y").get<int>();
        auto lairTime = lair.at("time").get<float>();

        auto enemiesWithTimeJson = lair.at("enemies");
        std::deque<std::unique_ptr<IEnemy>> spawnEnemies;
        std::deque<float> times;

        for (const auto & enemy : enemiesWithTimeJson) {
            auto type = enemy.at("type").get<std::string>();
            auto releaseTime = enemy.at("releaseTime").get<float>();
            std::unique_ptr<IEnemy> spawnEnemy = enemyTypes.get(type)->clone();
            spawnEnemies.push_back(std::move(spawnEnemy));
            times.push_back(releaseTime);

        }
        std::unique_ptr<Lair> concreteLair = std::make_unique<Lair>(std::move(times),std::move(spawnEnemies), Point{xL, yL}, lairTime);
        lairs.add(std::move(concreteLair));
    }
}
