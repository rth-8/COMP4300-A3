#include <iostream>
#include <fstream>
#include <cstdlib>

#include "scene_play.h"
#include "game_engine.h"
#include "assets.h"
#include "entity.h"
#include "entity_manager.h"

ScenePlay::ScenePlay(GameEngine* eng, const std::string & lvlP)
    : Scene(eng)
    , levelPath(lvlP)
{
    // std::cout << "SCENE PLAY: c'tor\n";
    this->view = this->engine->getWindow()->getDefaultView();
    this->windowW = this->engine->getWindow()->getSize().x;
    this->windowW2 = this->engine->getWindow()->getSize().x / 2;
    this->windowH = this->engine->getWindow()->getSize().y;
    this->windowH2 = this->engine->getWindow()->getSize().y / 2;
    init();
}

ScenePlay::~ScenePlay()
{
    // std::cout << "SCENE PLAY: d'tor\n";
}

void ScenePlay::init()
{
    // register actions
    registerAction(static_cast<int>(sf::Keyboard::Scancode::Escape), "RETURNTOMENU");
    registerAction(static_cast<int>(sf::Keyboard::Scancode::P), "PAUSE");
    
    registerAction(static_cast<int>(sf::Keyboard::Scancode::Left), "PLAYERLEFT");
    registerAction(static_cast<int>(sf::Keyboard::Scancode::Right), "PLAYERRIGHT");
    registerAction(static_cast<int>(sf::Keyboard::Scancode::Space), "PLAYERJUMP");
    registerAction(static_cast<int>(sf::Keyboard::Scancode::X), "PLAYERSHOT");
    registerAction(static_cast<int>(sf::Keyboard::Scancode::R), "PLAYERRESET");
    
    registerAction(static_cast<int>(sf::Keyboard::Scancode::C), "TOGLEBB");
    registerAction(static_cast<int>(sf::Keyboard::Scancode::T), "TOGLETEX");
    registerAction(static_cast<int>(sf::Keyboard::Scancode::G), "TOGLEGRID");

    // load level + player cfg
    load_level();

    // create player
    // std::cout << "Add player...\n";
    // std::cout << "[" << playerCfg.gx << "," << playerCfg.gy << "]\n";
    this->player = manager->addEntity("Player");
    auto& a = this->player->addComponent<CAnimation>(&this->engine->getAssets()->getAnimation("PlayerStanding"));
    auto& t = this->player->addComponent<CTransform>();
    t.pos.x = playerCfg.gx * 64;
    t.pos.y = this->engine->getWindow()->getSize().y - (playerCfg.gy * 64);
    this->player->addComponent<CInput>();
    this->player->addComponent<CBoundingBox>(a.getAnimation()->getSize());
    
    create_grid();
}

void ScenePlay::load_level()
{
    std::cout << "Loading level: \"" << levelPath << "\"\n";

    int bottom = this->engine->getWindow()->getSize().y;

    levelW = 0;
    int maxCol = 0;
    
    std::fstream input;

    input.open(this->levelPath, std::ios::in);
    if (input.is_open())
    {
        std::string line;
        while (std::getline(input, line))
        {
            // std::cout << "LINE: " << line << '\n';

            if (line[0] == '#')
                continue;

            std::stringstream ss(line);
            std::string token;

            std::string sval1;
            std::string sval2;
            int ival1;
            int ival2;

            if (std::getline(ss, token, ' '))
            {
                if (token == "Tile")
                {
                    ss >> sval1 >> ival1 >> ival2;
                    
                    if (ival1 > maxCol)
                        maxCol = ival1;
                    
                    auto e = manager->addEntity("Tile");
                    auto& a = e->addComponent<CAnimation>(&this->engine->getAssets()->getAnimation(sval1));
                    auto& t = e->addComponent<CTransform>();
                    t.pos.x = (ival1 * 64) + a.getAnimation()->getSize().x/2;
                    t.pos.y = bottom - (ival2 * 64) - a.getAnimation()->getSize().y/2;
                    e->addComponent<CBoundingBox>(a.getAnimation()->getSize());
                }
                else
                if (token == "Dec")
                {
                    ss >> sval1 >> ival1 >> ival2;
                    
                    if (ival1 > maxCol)
                        maxCol = ival1;
                    
                    auto e = manager->addEntity("Dec");
                    auto& a = e->addComponent<CAnimation>(&this->engine->getAssets()->getAnimation(sval1));
                    auto& t = e->addComponent<CTransform>();
                    t.pos.x = (ival1 * 64) + a.getAnimation()->getSize().x/2;
                    t.pos.y = bottom - (ival2 * 64) - a.getAnimation()->getSize().y/2;
                }
                else
                if (token == "Player")
                {
                    ss >> playerCfg.gx >>
                          playerCfg.gy >>
                          playerCfg.cx >>
                          playerCfg.cy >>
                          playerCfg.speed >>
                          playerCfg.jump >>
                          playerCfg.maxspeed >>
                          playerCfg.gravity >>
                          playerCfg.weapon;
                }
            }
        }

        input.close();
    }
    
    // std::cout << "maxCol = " << maxCol << "\n";
    levelW = 64 * (maxCol + 1);
    // std::cout << "levelW = " << levelW << "\n";
}

void ScenePlay::create_grid()
{
    std::cout << "Create grid texture.\n";
    
    if (this->gridTex.resize(sf::Vector2u(levelW,  this->engine->getWindow()->getSize().y)))
    {
        std::cout << "size: " << this->gridTex.getSize().x << " x " << this->gridTex.getSize().y << "\n";
        
        this->gridTex.clear(sf::Color::Transparent);
        
        int gw = levelW / 64;
        int gh = this->engine->getWindow()->getSize().y / 64;
        
        std::cout << "grid: " << gw << " x " << gh << "\n";
        
        sf::Text coords(this->engine->getAssets()->getFont("MenuFont"));
        coords.setCharacterSize(14);
        coords.setFillColor(sf::Color::White);
        
        for (int r = 0; r < gh; ++r)
        {
            for (int c = 0; c < gw; ++c)
            {
                sf::RectangleShape rectangle({64.0f, 64.0f});
                rectangle.setPosition(sf::Vector2f(c*64, r*64));
                rectangle.setFillColor(sf::Color(0, 0, 0, 0));
                rectangle.setOutlineThickness(-1);
                rectangle.setOutlineColor(sf::Color(255, 255, 255, 255));
                this->gridTex.draw(rectangle);
                
                std::ostringstream ss;
                ss << "(" << c << "," << (gh-r-1) << ")";
                coords.setString(ss.str());
                coords.setPosition(sf::Vector2f(c*64 + 2, r*64 + 62 - 14));
                this->gridTex.draw(coords);
            }
        }
        
        this->gridTex.display();
        
        this->gridSprite = std::make_shared<sf::Sprite>(this->gridTex.getTexture());
    }
    else
        std::cout << "Failed to resize grid texture!\n";
}

void ScenePlay::update()
{
    if (this->isPaused == false) 
    {
        this->manager->update();
        sAnimation();
        sMovement();
        sEnemySpawner();
        sCollision();
    }
    sRender();

    if (this->isPaused == false)
    {
        currentFrame++;
        this->engine->getWindow()->setTitle(std::format("{}, {}", 
            this->manager->getEntities("Shot").size(),
            currentFrame)
            );
    }
}

void ScenePlay::sAnimation()
{
    auto& playerTrans = this->player->getComponent<CTransform>();
    if (playerTrans.pos.y != playerTrans.prevPos.y)
    {
        // in the air
        if (this->player->getComponent<CAnimation>().getAnimation()->getName() != "PlayerJumping")
        {
            // std::cout << ">>> A: jumping\n";
            this->player->addComponent<CAnimation>(&this->engine->getAssets()->getAnimation("PlayerJumping"));
        }
    }
    else
    {
        if (playerInAir == false)
        {
            if (this->player->getComponent<CInput>().left == false &&
                this->player->getComponent<CInput>().right == false)
            {
                // not moving
                if (this->player->getComponent<CAnimation>().getAnimation()->getName() != "PlayerStanding")
                {
                    // std::cout << ">>> A: standing\n";
                    this->player->addComponent<CAnimation>(&this->engine->getAssets()->getAnimation("PlayerStanding"));
                }
            }
            else
            {
                // moving
                if (this->player->getComponent<CAnimation>().getAnimation()->getName() != "PlayerRunning")
                {
                    // std::cout << ">>> A: running\n";
                    this->player->addComponent<CAnimation>(&this->engine->getAssets()->getAnimation("PlayerRunning"));
                }
            }
        }
    }

    // update Animation(s)
    for (auto e : this->manager->getEntities())
    {
        auto& ac = e->getComponent<CAnimation>();
        auto* anim = ac.getAnimation();
        
        if (anim->getName() == "Explosion" || anim->getName() == "Coin")
        {
            anim->update(ac.frame++);
            if (anim->hasEnded())
            {
                e->kill();
                anim->reset();
            }            
        }
        else
            anim->update(currentFrame);
    }
}

void ScenePlay::sMovement()
{
    sf::Vector2f vc = this->view.getCenter();
    
    auto& trans = this->player->getComponent<CTransform>();
    auto& bb = this->player->getComponent<CBoundingBox>();

    // store previous position
    trans.prevPos = trans.pos;

    if (trans.speed.y < playerCfg.maxspeed)
        trans.speed.y += playerCfg.gravity;
    
    trans.pos += trans.speed;
    
    // prevent moving outside of level on left
    if (trans.pos.x - bb.halfSize.x < 0)
        trans.pos.x = bb.halfSize.x;
    
    if (trans.prevPos.y != trans.pos.y)
        playerInAir = true;
    
    
    for (auto& shot : this->manager->getEntities("Shot"))
    {
        auto& shotTrans = shot->getComponent<CTransform>();
        shotTrans.pos += shotTrans.speed;
        
        if (shotTrans.pos.x < vc.x - windowW2 || shotTrans.pos.x > vc.x + windowW2)
            shot->kill();
    }
    
    // player goes out of bottom bound
    if (trans.pos.y > vc.y + windowH2 + bb.halfSize.y)
    {
        // resest players position to default
        trans.pos.x = playerCfg.gx * 64;
        trans.pos.y = windowH - (playerCfg.gy * 64);
        
        // reset view
        this->view.setCenter(sf::Vector2f(windowW2, windowH2));
    }
}

void ScenePlay::sEnemySpawner()
{
}

void ScenePlay::sCollision()
{
    auto& playerTrans = this->player->getComponent<CTransform>();
    auto& playerBB = this->player->getComponent<CBoundingBox>();

    for (auto e : this->manager->getEntities("Tile"))
    {
        // 1: check & resolve collisions with player
        
        auto& eTrans = e->getComponent<CTransform>();
        auto& eBB = e->getComponent<CBoundingBox>();

        float pox = playerBB.halfSize.x + eBB.halfSize.x - abs(playerTrans.prevPos.x - eTrans.pos.x);
        float poy = playerBB.halfSize.y + eBB.halfSize.y - abs(playerTrans.prevPos.y - eTrans.pos.y);

        float ox = playerBB.halfSize.x + eBB.halfSize.x - abs(playerTrans.pos.x - eTrans.pos.x);
        float oy = playerBB.halfSize.y + eBB.halfSize.y - abs(playerTrans.pos.y - eTrans.pos.y);

        short state = 0;
        if (pox > 0 && poy <= 0) state = 1;
        else
        if (pox <= 0 && poy > 0) state = 2;
        else
        if (pox > 0 && poy > 0) state = 3;

        if (ox > 0 && oy > 0)
        {
            // pick collection coin
            if (e->getComponent<CAnimation>().getAnimation()->getName() == "CollectibleCoin")
            {
                e->kill();
                continue;
            }
            
            if (state == 1)
            {
                // vertical
                if (playerTrans.pos.y < eTrans.pos.y)
                {
                    // moving down
                    playerTrans.pos.y -= oy;
                    this->player->getComponent<CTransform>().speed.y = 0;
                    playerInAir = false;
                }
                
                if (playerTrans.pos.y > eTrans.pos.y)
                {
                    // moving up
                    playerTrans.pos.y += oy;
                    this->player->getComponent<CInput>().up = false;
                    this->player->getComponent<CTransform>().speed.y = 0;
                    
                    if (e->getComponent<CAnimation>().getAnimation()->getName() == "Brick")
                    {
                        // destroy brick
                        e->kill();
                        
                        // spawn explosion at same position
                        auto e = manager->addEntity("Dec");
                        e->addComponent<CAnimation>(&this->engine->getAssets()->getAnimation("Explosion"));
                        auto& t = e->addComponent<CTransform>();
                        t.pos.x = eTrans.pos.x;
                        t.pos.y = eTrans.pos.y;
                    }
                    
                    if (e->getComponent<CAnimation>().getAnimation()->getName() == "Question")
                    {
                        // question becomes block
                        e->addComponent<CAnimation>(&this->engine->getAssets()->getAnimation("Block"));
                        
                        // spawn coin above
                        auto e = manager->addEntity("Dec");
                        e->addComponent<CAnimation>(&this->engine->getAssets()->getAnimation("Coin"));
                        auto& t = e->addComponent<CTransform>();
                        t.pos.x = eTrans.pos.x;
                        t.pos.y = eTrans.pos.y - 64 - 4;
                    }
                }
            }
            else
            if (state == 2 || state == 3)
            {
                // horizontal
                if (playerTrans.pos.x < eTrans.pos.x) playerTrans.pos.x -= ox;
                if (playerTrans.pos.x > eTrans.pos.x) playerTrans.pos.x += ox;
            }
        }
        
        // 2: check & resolve collisions with shots
        for (auto& shot : this->manager->getEntities("Shot"))
        {
            auto& shotTrans = shot->getComponent<CTransform>();

            if (shotTrans.pos.x > eTrans.pos.x - eBB.halfSize.x && shotTrans.pos.x < eTrans.pos.x + eBB.halfSize.x &&
                shotTrans.pos.y > eTrans.pos.y - eBB.halfSize.y && shotTrans.pos.y < eTrans.pos.y + eBB.halfSize.y)
            {
                shot->kill();
                
                if (e->getComponent<CAnimation>().getAnimation()->getName() == "Brick")
                {
                    // destroy brick
                    e->kill();
                    
                    // spawn explosion at same position
                    auto e = manager->addEntity("Dec");
                    e->addComponent<CAnimation>(&this->engine->getAssets()->getAnimation("Explosion"));
                    auto& t = e->addComponent<CTransform>();
                    t.pos.x = eTrans.pos.x;
                    t.pos.y = eTrans.pos.y;
                }
            }
        }
    }
}

static void drawPoint(sf::RenderWindow & window, float x, float y, int size)
{
    std::array line1 =
    {
        sf::Vertex{sf::Vector2f(x-size, y)},
        sf::Vertex{sf::Vector2f(x+size, y)}
    };

    std::array line2 =
    {
        sf::Vertex{sf::Vector2f(x, y-size)},
        sf::Vertex{sf::Vector2f(x, y+size)}
    };

    window.draw(line1.data(), line1.size(), sf::PrimitiveType::Lines);
    window.draw(line2.data(), line2.size(), sf::PrimitiveType::Lines);
}

static void drawBB(sf::RenderWindow & window, const CTransform& trans, const CBoundingBox& bb)
{
    sf::RectangleShape rectangle({bb.size.x, bb.size.y});
    rectangle.setPosition(sf::Vector2f(trans.pos.x - bb.halfSize.x, trans.pos.y - bb.halfSize.y));
    rectangle.setFillColor(sf::Color(0, 0, 0, 0));
    rectangle.setOutlineThickness(-1);
    rectangle.setOutlineColor(sf::Color(255, 255, 255, 255));
    window.draw(rectangle);
}

void ScenePlay::sRender()
{
    auto w = this->engine->getWindow();
    w->clear(sf::Color(92,148,252));

    auto& trans = this->player->getComponent<CTransform>();
    if (levelW > windowW && trans.pos.x > windowW2 && trans.pos.x < (levelW-windowW2))
    {
        this->view.setCenter(sf::Vector2f(trans.pos.x, this->view.getCenter().y));
    }
    
    w->setView(this->view);

    for (auto e : this->manager->getEntities())
    {
        auto& spr = e->getComponent<CAnimation>().getAnimation()->getSprite();
        auto& t = e->getComponent<CTransform>();

        spr.setPosition({t.pos.x, t.pos.y});
        spr.setScale({t.scale.x, t.scale.y});
        if (this->isDrawingTex == true)
        {
            w->draw(spr);
        }

        if (this->isDrawingBB)
        {
            drawPoint(*w, t.pos.x, t.pos.y, 10);
            drawBB(*w, t, e->getComponent<CBoundingBox>());
        }
    }
    
    if (this->isDrawingGrid)
    {
        w->draw(*this->gridSprite);
    }
}

void ScenePlay::sDoAction(const Action& action)
{
    // std::cout << "SCENE PLAY: do action: " << action.name() << " (" << action.type() << ")\n";
    // std::cout << "waiting: " << waiting << "\n";

    if (action.name().starts_with("PLAYER") && this->isPaused == true)
        return;
    
    if (action.type() == "START")
    {
        if (action.name() == "RETURNTOMENU")
        {
            this->engine->changeScene("Menu");
        }
        else
        if (action.name() == "PLAYERLEFT")
        {
            if (this->player->getComponent<CInput>().right == true)
            {
                waiting = "PLAYERLEFT";
            }
            else
            {
                this->player->getComponent<CInput>().left = true;
                this->player->getComponent<CTransform>().speed.x = -playerCfg.speed;
                this->player->getComponent<CTransform>().scale.x = -1;
            }
        }
        else
        if (action.name() == "PLAYERRIGHT")
        {
            if (this->player->getComponent<CInput>().left == true)
            {
                waiting = "PLAYERRIGHT";
            }
            else
            {
                this->player->getComponent<CInput>().right = true;
                this->player->getComponent<CTransform>().speed.x = playerCfg.speed;
                this->player->getComponent<CTransform>().scale.x = 1;
            }
        }
        else
        if (action.name() == "PLAYERJUMP")
        {
            if (playerInAir == false)
            {
                this->player->getComponent<CInput>().up = true;
                this->player->getComponent<CTransform>().speed.y = playerCfg.jump;
                playerInAir = true;
            }
        }
        else
        if (action.name() == "PAUSE")
        {
            this->isPaused = !this->isPaused;
        }
        else
        if (action.name() == "PLAYERRESET")
        {
            this->player->getComponent<CTransform>().pos.x = playerCfg.gx * 64;
            this->player->getComponent<CTransform>().pos.y = this->engine->getWindow()->getSize().y - (playerCfg.gy * 64);
        }
        else
        if (action.name() == "TOGLETEX")
        {
            this->isDrawingTex = !this->isDrawingTex;
        }
        else
        if (action.name() == "TOGLEBB")
        {
            this->isDrawingBB = !this->isDrawingBB;
        }
        else
        if (action.name() == "TOGLEGRID")
        {
            this->isDrawingGrid = !this->isDrawingGrid;
        }
        else
        if (action.name() == "PLAYERSHOT")
        {
            auto& playerTrans = this->player->getComponent<CTransform>();
            
            auto e = manager->addEntity("Shot");
            e->addComponent<CAnimation>(&this->engine->getAssets()->getAnimation(playerCfg.weapon));
            auto& t = e->addComponent<CTransform>();
            if (playerTrans.scale.x < 0)
            {
                t.pos.x = playerTrans.pos.x - 32;
                t.speed.x = playerCfg.speed * -3;
            }
            else
            {
                t.pos.x = playerTrans.pos.x + 32;
                t.speed.x = playerCfg.speed * 3;
            }
            t.pos.y = playerTrans.pos.y;
            
        }
    }
    else
    if (action.type() == "END")
    {
        if (action.name() == "PLAYERLEFT")
        {
            if (waiting == "PLAYERLEFT")
                waiting.clear();
            
            this->player->getComponent<CInput>().left = false;
            this->player->getComponent<CTransform>().speed.x = 0;
                
            if (waiting == "PLAYERRIGHT")
            {
                this->player->getComponent<CInput>().right = true;
                this->player->getComponent<CTransform>().speed.x = playerCfg.speed;
                this->player->getComponent<CTransform>().scale.x = 1;
                waiting.clear();
            }
        }
        else
        if (action.name() == "PLAYERRIGHT")
        {
            if (waiting == "PLAYERRIGHT")
                waiting.clear();
            
            this->player->getComponent<CInput>().right = false;
            this->player->getComponent<CTransform>().speed.x = 0;
                
            if (waiting == "PLAYERLEFT")
            {
                this->player->getComponent<CInput>().left = true;
                this->player->getComponent<CTransform>().speed.x = -playerCfg.speed;
                this->player->getComponent<CTransform>().scale.x = -1;
                waiting.clear();
            }
        }
        else
        if (action.name() == "PLAYERJUMP")
        {
            if (this->player->getComponent<CInput>().up == true)
            {
                this->player->getComponent<CInput>().up = false;
                if (this->player->getComponent<CTransform>().speed.y < 0)
                    this->player->getComponent<CTransform>().speed.y = 0;
            }
        }
    }
}

void ScenePlay::sDebug()
{
}
