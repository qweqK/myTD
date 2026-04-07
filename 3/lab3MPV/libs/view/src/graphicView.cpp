#include "graphicView.h"

#include <iostream>

GraphicView::GraphicView(Map &map, sf::RenderWindow &mwindow,
    EnemyRepo & enRepo, TowerRepository &towRep,Controller & controller,
    Castle &cast ,LairRepository &lairRepository,float titleSize) : map(map), window(mwindow), titleSize(titleSize),
    enRepo(enRepo), towerRepo(towRep), controller(controller), castle(cast), lairRepo(lairRepository){}


void GraphicView::drawMap()  {
    for (size_t y = 0; y<map.getRows(); ++y) {
        for (size_t x = 0; x<map.getCols(); ++x) {
            auto cellType = map.at(x, y).type;
            sf::Sprite s;
            mapText.setPosition(sf::Vector2f(x * titleSize+titleSize/2.f, y * titleSize+titleSize/2.f));
            mapText.setString(std::to_string(map.at(x, y).priority));
            switch (cellType) {
                case TerraType::field : {
                    s=spriteMap["field"];
                }break;

                case TerraType::forest : {
                    s=spriteMap["forest"];
                }break;

                case TerraType::road : {
                    s=spriteMap["road"];
                }break;
            }
            s.setPosition((sf::Vector2f(x * titleSize, y * titleSize)));
            window.draw(s);
            if (cellType == TerraType::road)window.draw(mapText);
        }
    }
}

void GraphicView::processInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (gameState==GameState::PLAYING||gameState==GameState::BUILD)gameState=GameState::PAUSED;
            else gameState = GameState::PLAYING;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B) {
            if (gameState==GameState::PLAYING) gameState=GameState::BUILD;
            else gameState = GameState::PLAYING;
        }

        if (event.type == sf::Event::MouseButtonPressed && gameState==GameState::BUILD) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                buildClick(event.mouseButton.x, event.mouseButton.y);

            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                sf::Vector2f pixelPos = window.mapPixelToCoords(mousePos);
                float worldX = pixelPos.x/titleSize;
                float worldY = pixelPos.y/titleSize;
                bool f= controller.sell(worldX, worldY);
                if (f==false) {std::cout << "poshel ka ti nax"<< std::endl;}
            }
            /*if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                sf::Vector2f pixelPos = window.mapPixelToCoords(mousePos);
                float worldX = pixelPos.x/titleSize;
                float worldY = pixelPos.y/titleSize;

                bool f=  controller.build(worldX, worldY, "baseTower");
                if (f==false) {std::cout << "poshel ka ti nax"<< std::endl;}
            }
            if (event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                sf::Vector2f pixelPos = window.mapPixelToCoords(mousePos);
                float worldX = pixelPos.x/titleSize;
                float worldY = pixelPos.y/titleSize;
                bool f= controller.sell(worldX, worldY);
                if (f==false) {std::cout << "poshel ka ti nax"<< std::endl;}

            }*/

        }
        else if (event.type == sf::Event::MouseButtonPressed && gameState==GameState::PAUSED) {
                menuClick(event.mouseButton.x, event.mouseButton.y);
        }
        else if (event.type == sf::Event::MouseButtonPressed && gameState==GameState::PLAYING) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                sf::Vector2f pixelPos = window.mapPixelToCoords(mousePos);
                float worldX = pixelPos.x/titleSize;
                float worldY = pixelPos.y/titleSize;
                bool f =controller.levelUp(worldX, worldY);
                if (f==false) {std::cout << "poshel ki ti nax"<< std::endl;}
            }
        }

        }

    }


void GraphicView::menuClick(int mouseX, int mouseY) {
    sf::Vector2f mousePos = window.mapPixelToCoords({mouseX, mouseY});
    if (saveButton.getGlobalBounds().contains(mousePos)) {

        std::cout << "save"<<std::endl;

    }
    else if (loadButton.getGlobalBounds().contains(mousePos)) {
        std::cout << "load"<<std::endl;
    }
    else if (exitButton.getGlobalBounds().contains(mousePos)) {
        window.close();
    }

}

void GraphicView::buildClick(int mouseX, int mouseY) {
    sf::Vector2f mousePos = window.mapPixelToCoords({mouseX, mouseY});
    float xWorld = mousePos.x/titleSize;
    float yWorld = mousePos.y/titleSize;
    if (magickTowerBuildButton.getGlobalBounds().contains(mousePos)) {
        buildType=BuildType::MAG;
        magickTowerBuildButton.setFillColor(sf::Color::Magenta);
        return;
    }
    else if (baseTowerBuildButton.getGlobalBounds().contains(mousePos)) {
        buildType=BuildType::BASE;
        baseTowerBuildButton.setFillColor(sf::Color::Magenta);
        return;
    }
    else if (magickTrapBuildButton.getGlobalBounds().contains(mousePos)) {
        buildType=BuildType::TRAP;
        magickTrapBuildButton.setFillColor(sf::Color::Magenta);
        return;

    }

    switch (buildType) {
        case BuildType::MAG : controller.build(xWorld, yWorld, "magickTower"); break;
        case BuildType::BASE : controller.build(xWorld, yWorld, "baseTower"); break;
        case BuildType::TRAP : controller.build(xWorld, yWorld, "magickTrap"); break;
    }

}





void GraphicView::render() {
    window.clear(sf::Color::Black);


    drawMap();
    drawEnemy();
    drawTower();
    drawCastle();
    drawLair();
    if (gameState == GameState::PAUSED) drawPauseMenu();
    if (gameState == GameState::BUILD) drawBuildMenu();
    window.display();
}


void GraphicView::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processInput();
         if (gameState==GameState::PLAYING||gameState==GameState::BUILD) controller.updateLogic(dt);
        render();
    }
}

void GraphicView::drawEnemy()  {
    const auto& enemies = enRepo.getAll();
    auto & sprite = spriteMap.at("enemy");
    for (const auto & enemy: enemies) {
        float height = 6.0f;

        float ratio = enemy->getCurHp()/enemy->getMaxHp();
        float pixelXHp = enemy->getPosition().x * titleSize;
        float pixelYHp = enemy->getPosition().y * titleSize;

        sf::RectangleShape hp{{titleSize*ratio, height}};
        hp.setOrigin(titleSize *ratio/ 2, height / 2);
        hp.setPosition(pixelXHp, pixelYHp-titleSize * 0.6f);
        hp.setFillColor(sf::Color(0, 30, 200));


        float pixelX = enemy->getPosition().x*titleSize;
        float pixelY = enemy->getPosition().y*titleSize;

        sprite.setPosition(sf::Vector2f(pixelX, pixelY));
        window.draw(sprite);
        window.draw(hp);
    }
}

void GraphicView::drawTower()  {
    for (const auto& tow: towerRepo.getAll()) {
        level.setString("level " + std::to_string(tow->getLevel()));
        sf::Sprite sprite = spriteMap.at(tow->getType());
        float radius =titleSize*static_cast<float>(tow->getRange());
        sf::CircleShape shapeRad(radius);
        shapeRad.setFillColor(sf::Color(0, 255, 0, 40));
        shapeRad.setOrigin(radius, radius);

        float pixelX = static_cast<float>(tow->getPosition().x)*titleSize +titleSize/2.0f;
        float pixelY = static_cast<float>(tow->getPosition().y)*titleSize +titleSize/2.0f;
        sprite.setPosition(sf::Vector2f(pixelX, pixelY));
        shapeRad.setPosition(sf::Vector2f(pixelX, pixelY));
        level.setPosition(pixelX-titleSize*0.40, pixelY-titleSize*0.85);
        window.draw(level);
        window.draw(sprite);
        window.draw(shapeRad);

    }
}

void GraphicView::drawCastle()  {

    auto &sprite = spriteMap["castle"];
    gold.setString(std::to_string(castle.getGold())+"$");
    float height = 6.0f;

    float ratio = castle.getCurrHP()/castle.getMaxHP();

    sf::RectangleShape hp{{titleSize*ratio*window.getSize().x, height}};
    hp.setOrigin(titleSize *ratio/ 2, height / 2);
    hp.setPosition(0, window.getSize().y-height);
    hp.setFillColor(sf::Color(200, 0, 0));
    float pixelX  = static_cast<float>(castle.getLocation().x)*titleSize +titleSize/2.0f;
    float pixelY = static_cast<float>(castle.getLocation().y)*titleSize +titleSize/2.0f;
    gold.setPosition(pixelX-titleSize*0.40f, pixelY-titleSize*0.8f);
    sprite.setPosition(sf::Vector2f(pixelX, pixelY));
    window.draw(gold);
    window.draw(sprite);
    window.draw(hp);
}



void GraphicView::loadTexture(const std::string &name, const std::string &path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        throw std::runtime_error("Can't load texture " + name + "po puti" + path);
    }
    textureMap[name] = texture;
}

void GraphicView::loadSprites() {
    spriteMap["castle"].setTexture(textureMap["castle"]);
    auto & castleSprite = spriteMap["castle"];
    spriteMap["castle"].scale({titleSize/castleSprite.getGlobalBounds().width, titleSize/castleSprite.getGlobalBounds().height});
    spriteMap["castle"].setOrigin({castleSprite.getLocalBounds().width/2.f, castleSprite.getLocalBounds().height/2});

    spriteMap["lair"].setTexture(textureMap["lair"]);
    auto & lairSprite = spriteMap["lair"];
    spriteMap["lair"].scale({titleSize/lairSprite.getGlobalBounds().width, titleSize/lairSprite.getGlobalBounds().height});
    spriteMap["lair"].setOrigin({lairSprite.getLocalBounds().width/2.f, lairSprite.getLocalBounds().height/2});

    spriteMap["enemy"].setTexture(textureMap["enemy"]);
    auto & enemySprite = spriteMap["enemy"];
    spriteMap["enemy"].scale({titleSize/enemySprite.getGlobalBounds().width/1.5f, titleSize/enemySprite.getGlobalBounds().height/1.5f});
    spriteMap["enemy"].setOrigin({enemySprite.getLocalBounds().width/2.f, enemySprite.getLocalBounds().height/2});

    spriteMap["magickTower"].setTexture(textureMap["magickTower"]);
    auto & mTowerSprite = spriteMap["magickTower"];
    spriteMap["magickTower"].scale({titleSize/mTowerSprite.getGlobalBounds().width/1.1f, titleSize/mTowerSprite.getGlobalBounds().height/1.1f});
    spriteMap["magickTower"].setOrigin({mTowerSprite.getLocalBounds().width/2.f, mTowerSprite.getLocalBounds().height/2});

    spriteMap["magickTrap"].setTexture(textureMap["magickTrap"]);
    auto & mTrapSprite = spriteMap["magickTrap"];
    spriteMap["magickTrap"].scale({titleSize/mTrapSprite.getGlobalBounds().width/1.1f, titleSize/mTrapSprite.getGlobalBounds().height/1.1f});
    spriteMap["magickTrap"].setOrigin({mTrapSprite.getLocalBounds().width/2.f, mTrapSprite.getLocalBounds().height/2});

    spriteMap["baseTower"].setTexture(textureMap["baseTower"]);
    auto & baseTowerSprite = spriteMap["baseTower"];
    spriteMap["baseTower"].scale({titleSize/baseTowerSprite.getGlobalBounds().width/1.1f, titleSize/baseTowerSprite.getGlobalBounds().height/1.1f});
    spriteMap["baseTower"].setOrigin({baseTowerSprite.getLocalBounds().width/2.f, baseTowerSprite.getLocalBounds().height/2});

    spriteMap["road"].setTexture(textureMap["road"]);
    auto & roadSprite = spriteMap["road"];
    spriteMap["road"].scale(titleSize/roadSprite.getGlobalBounds().width, titleSize/roadSprite.getGlobalBounds().height);

    spriteMap["field"].setTexture(textureMap["field"]);
    auto & fieldSprite = spriteMap["field"];
    spriteMap["field"].scale(titleSize/fieldSprite.getGlobalBounds().width, titleSize/fieldSprite.getGlobalBounds().height);

    spriteMap["forest"].setTexture(textureMap["forest"]);
    auto & forestSprite = spriteMap["forest"];
    spriteMap["forest"].scale(titleSize/forestSprite.getGlobalBounds().width, titleSize/forestSprite.getGlobalBounds().height);

}



void GraphicView::drawLair()  {
    sf::Sprite &sprite = spriteMap.at("lair");
    for (const auto & lair : lairRepo.getAll()) {

        float pixelX = static_cast<float>(lair->getPos().x)*titleSize+titleSize/2.0f;
        float pixelY = static_cast<float>(lair->getPos().y)*titleSize +titleSize/2.0f;

        sprite.setPosition(sf::Vector2f(pixelX, pixelY));
        window.draw(sprite);
    }
}


void GraphicView::loadFont(const std::string & path) {
    if (!font.loadFromFile(path)) {
        throw std::runtime_error("Can't load font");
    }
    mapText.setFont(font);
    mapText.setCharacterSize(24);
    mapText.setFillColor(sf::Color::White);
    gold.setFont(font);
    gold.setFillColor(sf::Color::Yellow);
    gold.setCharacterSize(24);
    level.setFont(font);
    level.setCharacterSize(15);
    level.setFillColor(sf::Color::Black);
    initBuildMenu();
    initPauseMenu();
}


void GraphicView::initPauseMenu() {
    sf::Vector2u windowSize = window.getSize();
    pauseBack.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    pauseBack.setFillColor(sf::Color(0, 0, 0, 150));
    auto setupButton = [&](sf::Text& btn, std::string str, float y) {
        btn.setFont(font);
        btn.setString(str);
        btn.setCharacterSize(40);
        btn.setFillColor(sf::Color::White);

        sf::FloatRect bounds = btn.getLocalBounds();
        btn.setOrigin(bounds.width/2.f, bounds.height/2.f);
        btn.setPosition(windowSize.x /2.f, y);
    };
    setupButton(saveButton, "SAVE", windowSize.y *0.3f);
    setupButton(loadButton, "LOAD", windowSize.y *0.5f);
    setupButton(exitButton, "EXIT", windowSize.y *0.7f);

}

void GraphicView::drawPauseMenu() {
    window.draw(pauseBack);
    window.draw(saveButton);
    window.draw(exitButton);
    window.draw(loadButton);
}

void GraphicView::drawBuildMenu() {
    window.draw(magickTowerBuildButton);
    window.draw(magickTrapBuildButton);
    window.draw(baseTowerBuildButton);
    magickTowerBuildButton.setFillColor(sf::Color(130, 130, 130));
    magickTrapBuildButton.setFillColor(sf::Color(130, 130, 130));
    baseTowerBuildButton.setFillColor(sf::Color(130, 130, 130));
    if (buildType==BuildType::TRAP) magickTrapBuildButton.setFillColor(sf::Color::Magenta);
    else if (buildType== BuildType::BASE) baseTowerBuildButton.setFillColor(sf::Color::Magenta);
    else if (buildType== BuildType::MAG) magickTowerBuildButton.setFillColor(sf::Color::Magenta);
}


void GraphicView::initBuildMenu() {
    sf::Vector2u windowSize = window.getSize();
    auto setupButton = [&](sf::Text& btn, std::string str, float x) {
        btn.setFont(font);
        btn.setString(str);
        btn.setCharacterSize(30);
        btn.setFillColor(sf::Color(130, 130, 130));

        sf::FloatRect bounds = btn.getLocalBounds();
        btn.setOrigin(bounds.width/2.f, bounds.height/2.f);
        btn.setPosition(x, windowSize.y* 0.2f );
    };
    setupButton(magickTowerBuildButton, "MAGICK TOWER", windowSize.x *0.2f);
    setupButton(baseTowerBuildButton, "DEFAULT TOWER", windowSize.x *0.5f);
    setupButton(magickTrapBuildButton, "TRAP TOWER", windowSize.x *0.8f);

}



