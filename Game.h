#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.hpp"
#include "Entity.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

struct WindowConfig
{
int wHeight, wWidth, wFrameLimit, wMode;
};
struct FontConfig
{
    std::string fontUrl;
    int fSize, fR, fG, fB;
};
struct PlayerConfig
{
	int SR, CR, FR, FG, FB, OR, OG, OB, OT, V;
	float S;
};
struct EnemyConfig
{
	int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI;
	float SMIN, SMAX;
};
struct BulletConfig
{
	int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L;
	float S;
};

class Game
{
private:
	sf::RenderWindow m_window;
	EntityManager m_entities;
	sf::Font m_font;
	sf::Text m_text;
	PlayerConfig m_playerConfig;
	EnemyConfig m_enemyConfig;
	BulletConfig m_bulletConfig;
	WindowConfig m_windowConfig;
	FontConfig m_fontConfig;
	sf::Clock m_deltaClock;
	int m_sore = 0;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;
	bool m_paused = false;
	bool m_running = true;

	void init(const std::string &config);
	void setPaused(bool paused);

	void sMovement();
	void sRender();
	void sSpawner();
	void sCollision();
	void sUserInput();
	void sLifespan();
	void sEnemySpawner();
	void sGUI();
	// void sSpecialShoot();

	void spawnPlayer();
	void spawnEnemy();
	void spawnBullet(std::shared_ptr<Entity> enitity, const Vec2f &mousePos);
	void spawnSmallEnemies(std::shared_ptr<Entity> enitity);

	std::shared_ptr<Entity> player();

public:
	Game(const std::string &config);

	void run();
};
