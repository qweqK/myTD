#include <iostream>
#include "static_loader.h"
#include "map/include/map.h"
#include "model/service/load/StateService.h"
#include "service/load/include/stateServiceImpl.h"
#ifdef I
#undef I
#endif
#include  "view/include/graphicView.h"
#include <SFML/Graphics.hpp>


int main() {
    std::unique_ptr<StaticLoader> loader= std::make_unique<StaticLoader>();

    auto & state =loader->getStateService();
    auto & config = loader->getConfigLoadService();
    config.load("config/config.yaml");
    state.load("save/save2.json");
     //  state.loadCastle("state/castle.json");
     //  state.loadTower(std::string("state/towers.json"));
     //  state.loadMap(std::string("state/map.json"));
     // state.loadEnemy(std::string("state/enemies3.json"));
     // state.loadLairs(std::string("state/lairs.json"));

    auto & map = loader->getMap();
    const float TITLE_SIZE = 64.0f;
    sf::RenderWindow window(sf::VideoMode(960, 640), "TD");
    window.setPosition({0,0});
    //sf::RenderWindow window(sf::VideoMode(map.getCols()*TITLE_SIZE, map.getRows()*TITLE_SIZE), "TD");
    window.setFramerateLimit(60);
    std::unique_ptr<GraphicView> view= std::make_unique<GraphicView>(map, window, loader->getEnemyRepo(),loader->getTowerRepo(), loader->getController(),loader->getCastle(),loader->getLairRepository(),TITLE_SIZE);
    view->loadTexture("baseTower", "graphic/tea.png");
    view->loadTexture("magickTower", "graphic/vitaminC.png");
    view->loadTexture("magickTrap", "graphic/tabletka.png");
    view->loadTexture("enemy","graphic/microbi.png");
    view->loadTexture("castle", "graphic/ovcharenko.png");
    view->loadTexture("lair", "graphic/sopli.png");
    view->loadTexture("road", "graphic/grunt.png");
    view->loadTexture("field", "graphic/field.png");
    view->loadTexture("forest", "graphic/forest.png");
    view->loadSprites();
    view->loadFont("graphic/roboto.ttf");

    loader->getPathService().calcDistanceForMap();
    loader->getPathService().calcFlowForMap();
    view->run();
    state.save("save/save.json");
}
