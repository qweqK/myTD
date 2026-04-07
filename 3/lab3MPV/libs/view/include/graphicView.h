#pragma once
#include "view/TDView.h"
#include "map/include/map.h"
#ifdef I
#undef I
#endif
#include <SFML/Graphics.hpp>

#include "castle/include/castle.h"
#include "controller/Controller.h"
#include "model/repository/enemyRepo.h"
#include "model/repository/lairRepo.h"
#include "model/repository/towerRepo.h"
#include "model/service/game/enemyService.h"
#include "model/service/game/TowerService.h"
enum class GameState {
    PAUSED,
    PLAYING,
    BUILD,
};

enum class BuildType {
    MAG,
    BASE,
    TRAP,
};

class GraphicView: public TDView {
    Map & map;
    sf::RenderWindow & window;
    float titleSize;
    std::map<std::string, sf::Texture> textureMap;
    std::map<std::string, sf::Sprite> spriteMap;
    //std::map<std::string, sf::RectangleShape> hpBars;

    EnemyRepo & enRepo;
    TowerRepository & towerRepo;
    Castle & castle;
    LairRepository & lairRepo;
    Controller & controller;
    sf::Text mapText;
    sf::Font font;

    public:
    GraphicView(Map &map, sf::RenderWindow &mwindow, EnemyRepo & enRepo, TowerRepository &towRep, Controller &controller ,Castle& cast,LairRepository &lairRepository,float titleSize=64.0f);

    void run() override;
    void render();
    void loadTexture(const std::string & name, const std::string & path);
    void loadSprites();
    void loadFont(const std::string & path);

    private:
    GameState gameState=GameState::PLAYING;
    BuildType buildType=BuildType::BASE;
    sf::Text loadButton;
    sf::Text saveButton;
    sf::Text exitButton;
    sf::Text magickTowerBuildButton;
    sf::Text baseTowerBuildButton;
    sf::Text magickTrapBuildButton;
    sf::RectangleShape pauseBack;
    sf::Text level;
    sf::Text gold;

    void menuClick(int mouseX, int mouseY);
    void buildClick(int mouseX, int mouseY);

    void drawMap() ;
    void drawEnemy() ;
    void drawTower() ;
    void drawCastle() ;
    void drawLair() ;
    void processInput();
    void drawStat();
    void drawPauseMenu();
    void drawBuildMenu();
    void initPauseMenu();
    void initBuildMenu();


};
