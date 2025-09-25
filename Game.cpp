#include "Game.h"
#include "Components.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <math.h>

Game::Game(const std::string &config)
    : m_text(m_font)
{
    if (!m_font.openFromFile("fonts/font.ttf"))
    {
        throw std::runtime_error("Failed to load font!");
    }

    init(config);
}

void Game::init(const std::string &path)
{
    // TODO : read in config file here
    //  use the premade PlayreConfig EnemyConfig, BulletConfig
    std::ifstream file("config.txt");
    std::string type;
    while (file >> type)
    {
        if (type == "Window")
        {
            file >> m_windowConfig.wWidth >> m_windowConfig.wHeight >> m_windowConfig.wFrameLimit >> m_windowConfig.wMode;
        }
        if (type == "Font")
        {
            file >> m_fontConfig.fontUrl >> m_fontConfig.fSize >> m_fontConfig.fR >> m_fontConfig.fG >> m_fontConfig.fB;
        }
        if (type == "Player")
        {
            file >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB >> m_playerConfig.OT >> m_playerConfig.V;
        }
        if (type == "Enemy")
        {
            file >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX >> m_enemyConfig.OR >> m_enemyConfig.OG >> m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX >> m_enemyConfig.L >> m_enemyConfig.SI;
        }
        if (type == "Bullet")
        {
            file >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB >> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L;
        }
    }

    // ser up default window parameters

    m_window.create(sf::VideoMode({m_windowConfig.wWidth, m_windowConfig.wHeight}), "Geomatry Dash");
    m_window.setFramerateLimit(m_windowConfig.wFrameLimit);

    ImGui::SFML::Init(m_window);

    spawnPlayer();
}

std::shared_ptr<Entity> Game::player()
{
    auto &player = m_entities.getEntities("player");

    return player.front();
}

void Game::run()
{
    // TODO:: add pause functionality in herer
    //  some system should function while paused (rendering)
    //  some system shouldn't (movement / input)

    while (m_running)
    {
        // update the entity manager;
        m_entities.update();

        // required update call to imgui
        // ImGui::SFML::Update(m_window, m_deltaClock.restart());

        sEnemySpawner();
        sCollision();
        sUserInput();
        sMovement();
        // sGUI();
        sRender();

        // increment the current frame
        // may need to be moved when pause implemented
        m_currentFrame++;
    }
}

void Game::spawnPlayer()
{
    // todo: finsish adding all the propertien of the player with the current values from the config

    // we create every entity by calling entityManager.addEnity(tag)
    // This returns a std::shard_ptr<Entity>, so we use auto to save typing
    auto entity = m_entities.addEntity("player");

    // give the enity a transform so it spwns at (200,200) with velcity(1,1) and angle
    Vec2f wMiddle = {m_windowConfig.wWidth / 2, m_windowConfig.wHeight / 2};
    entity->add<CTransform>(wMiddle, Vec2f(2.0f, 2.0f), 1.0f);
    // the entity shape will have radius 32, 8 sides , drak gray dill and red outline
    entity->add<CShape>((float)m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);
    // add a input component to the player do that we can use inputs
    entity->add<CInput>();
}

// spawn an enemy at randome position
void Game::spawnEnemy()
{
    srand(time(0));
    Vec2f speed = {
        m_enemyConfig.SMIN + rand() % (int)(m_enemyConfig.SMAX - m_enemyConfig.SMIN + 1),
        m_enemyConfig.SMIN + rand() % (int)(m_enemyConfig.SMAX - m_enemyConfig.SMIN + 1)};

    auto vertices = m_enemyConfig.VMIN + rand() % (m_enemyConfig.VMAX - m_enemyConfig.VMIN + 1);
    auto radius = m_enemyConfig.SR;
    Vec2f postion = {
        m_enemyConfig.SR + rand() % (m_windowConfig.wWidth - 2 * m_enemyConfig.SR + 1),
        m_enemyConfig.SR + rand() % (m_windowConfig.wHeight - 2 * m_enemyConfig.SR + 1),
    };
    // Todo ; make suer the enemy is spawdne properly with the m_enemyCOngi variables
    //  the emey must be spawned within the bounds of the window;
    auto outlineColor = sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB);
    auto fillColor = sf::Color(rand() % 255, rand() % 255, rand() % 255);
    auto enemy = m_entities.addEntity("enemy");
    enemy->add<CTransform>(postion, speed, 1.0f);
    enemy->add<CShape>((float)radius, vertices, fillColor, outlineColor, 1);
    enemy->add<CCollision>((float)radius);
    // record when the most recent enemy was spawned;
    m_lastEnemySpawnTime = m_currentFrame;
}
void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
    // Todo:spawn small enemies at the location of the input enemy e
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2f &target)
{
}

void Game::sMovement()
{
    // todl implement all enity movement in this function
    //  you shoud read the m_player->cinput component to determine if player is moved

    // sampel movement speed update

    auto &transform = player()->get<CTransform>();
    auto &key = player()->get<CInput>();
    if (key.down)
    {
        transform.position.y += transform.velocity.y;
    }
    if (key.up)
    {
        transform.position.y -= transform.velocity.y;
    }
    if (key.right)
    {
        transform.position.x += transform.velocity.x;
    }
    if (key.left)
    {
        transform.position.x -= transform.velocity.x;
    }

    // enemy movement

    // auto &enemy = m_entities.getEntities("enemy");
    // for (auto e : enemy)
    // {
    //     e->get<CTransform>().position += e->get<CTransform>().velocity;
    // }
}

void Game::sLifespan()
{
    // todo implement all lifespan fuctionality

    // for all entities
    //  if entity has no lifespan component, skipit
    //  if entity has > 0 remainig lifespan , subtact 1
    //  if it has lfespan and is alive
    //      scale its alpha channel properly
    // if it has lifespan and its time is up
    //      destory the entity
}

void Game::sCollision()
{
    auto enemy = m_entities.getEntities("enemy");

    // black hold
    // for (auto e1 : enemy)
    // {
    //     for (auto e2 : enemy)
    //     {
    //         if (e1 == e2)
    //             continue; // skip self

    //         auto &pos1 = e1->get<CTransform>().position;
    //         auto &vel1 = e1->get<CTransform>().velocity;
    //         float radius1 = e1->get<CCollision>().radius;

    //         auto &pos2 = e2->get<CTransform>().position;
    //         auto &vel2 = e2->get<CTransform>().velocity;
    //         float radius2 = e2->get<CCollision>().radius;

    //         float dx = pos2.x - pos1.x;
    //         float dy = pos2.y - pos1.y;
    //         float distance = sqrt(dx * dx + dy * dy);

    //         if (distance < radius1 + radius2)
    //         {
    //             float overlap = 0.5f * (distance - radius1 - radius2);

    //             // push apart
    //             pos1.x -= overlap * (dx / distance);
    //             pos1.y -= overlap * (dy / distance);
    //             pos2.x += overlap * (dx / distance);
    //             pos2.y += overlap * (dy / distance);

    //             // swap velocities for simple bounce
    //             std::swap(vel1.x, vel2.x);
    //             std::swap(vel1.y, vel2.y);
    //         }
    //     }
    //

    // todo : implement all proper collision between entities
    //  be suer to use the collision radius, Not the shape radius
    //  for (auto b : m_entities.getEntities("bullet"))
    //  {
    //      for (auto e : m_entities.getEntities("enemy"))
    //      {

    // wall collision

    for (auto e : enemy)
    {

        if ((e->get<CTransform>().position.x - e->get<CCollision>().radius) < 0 || (e->get<CTransform>().position.x + e->get<CCollision>().radius) > m_windowConfig.wWidth)
        {
            e->get<CTransform>().velocity.x *= -1;
        }
        if ((e->get<CTransform>().position.y - e->get<CCollision>().radius) < 0 || (e->get<CTransform>().position.y + e->get<CCollision>().radius) > m_windowConfig.wHeight)
        {
            e->get<CTransform>().velocity.y *= -1;
        }
        e->get<CTransform>().position += e->get<CTransform>().velocity;
    }
}

void Game::sEnemySpawner()
{
    if (m_currentFrame > 90)
    {
        m_currentFrame = 0;
        spawnEnemy();
    }

    // todo:: code which implements eney spanwing should go here
}

void Game::sGUI()
{
    ImGui::Begin("Geometry Wars");
    ImGui::Text("Hello");
    ImGui::End();
}

void Game::sRender()
{
    // TODO: change the code below to draw all the entities
    ImGui::SFML::Update(m_window, m_deltaClock.restart());
    m_window.clear();
    auto &enemy = m_entities.getEntities("enemy");
    player()->get<CTransform>().angle += 1.0f;

    // player()->get<CTransform>().velocity += {1, 1};

    // set the position o the shape based ont eh entits transform->pos
    player()->get<CShape>().circle.setPosition(player()->get<CTransform>().position);
    auto angle = player()->get<CTransform>().angle;
    player()->get<CShape>().circle.setRotation(sf::degrees(angle));

    for (auto &e : enemy)
    {
        e->get<CShape>().circle.setPosition(e->get<CTransform>().position);
        e->get<CShape>().circle.setRotation(sf::degrees(angle));
    }
    // draw the entity's sf::circleshape
    m_window.draw(player()->get<CShape>().circle);

    for (auto &e : enemy)
    {
        m_window.draw(e->get<CShape>().circle);
    }

    // draw the ui last
    ImGui::SFML::Render(m_window);
    m_window.display();
}

void Game::sUserInput()
{
    // todo : handle user input here

    while (const auto event = m_window.pollEvent())
    {
        // ImGui::SFML::ProcessEvent(m_window, *event);
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }
        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            switch (keyPressed->scancode)
            {
            case sf::Keyboard::Scan::Escape:
                m_window.close();
                break;

            case sf::Keyboard::Scan::W:
                player()->get<CInput>().up = true;
                break;

            case sf::Keyboard::Scan::S:
                player()->get<CInput>().down = true;
                break;

            case sf::Keyboard::Scan::A:
                player()->get<CInput>().left = true;
                break;

            case sf::Keyboard::Scan::D:
                player()->get<CInput>().right = true;
                break;

            default:
                break;
            }
        }

        if (const auto *KeyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            switch (KeyReleased->scancode)
            {
            case sf::Keyboard::Scan::W:
                player()->get<CInput>().up = false;
                break;

            case sf::Keyboard::Scan::S:
                player()->get<CInput>().down = false;
                break;

            case sf::Keyboard::Scan::A:
                player()->get<CInput>().left = false;
                break;

            case sf::Keyboard::Scan::D:
                player()->get<CInput>().right = false;
                break;

            default:
                break;
            }
        }
    }
}