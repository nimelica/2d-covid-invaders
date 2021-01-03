#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include <map>
#include <memory>
#include "Enemy.h"

using namespace sf;
using namespace std;

class Bullet;

class Game 
{
public:
	Game();
	virtual ~Game();

	//Public update functions
	void run();                    //run the game
	void update();                 //updating positions
	void updateEvent();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullet();
	void updateEnemies();
	void updateCombat();
	void updatePlayerMove();

	//public render functions
	void render();              //draw the game
	void renderBullet();
	void renderGUI();
	void renderEnemy();
	void renderWorld();

private:
	//Window
	RenderWindow* window;
	ContextSettings settings;
	Event eventObj;
	int width = 575;
	int height = 865;

	//Resources
	map<string, Texture*>textures; //if it doesnt work, change as a pointer
	vector<Bullet*>bullets;

	//Player
	unique_ptr<Player>player;

	//Player GUI Health Bar
	RectangleShape playerHealthBar;
	RectangleShape playerHealthBarBack;

	//Enemy
	unique_ptr<Enemy>enemy;
	vector<Enemy*>enemies;
	float spawnTimer;
	float spawnTimerMax;

	//World
	Sprite backgroundSprite;
	Texture backgroundTexture;

	//Score points
	unsigned score;

	//GUI
	Font font;
	Text pointText;

	//Privite functions
	void systemSetup();
	void textureSetup();
	void windowSetup();
	void worldSetup();
	void GUIsetup();
	void createPlayer();
	void createEnemies();
};

