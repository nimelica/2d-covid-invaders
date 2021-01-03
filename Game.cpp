#include "Game.h"
#include "Bullet.h"
#include <sstream>

Game::Game()
{
	windowSetup();
	textureSetup();
	GUIsetup();
	systemSetup();
	createPlayer();
	createEnemies();
	worldSetup();
}

Game::~Game()
{
	delete window;

	//delete textures

	for (auto &next : textures)
	{
		delete next.second;
	}
	
	for( auto *next : bullets)
	{
		delete next;
	}

	for (auto* next : enemies)
	{
		delete next;
	}
}

void Game::systemSetup()
{
	score = 0;
}

void Game::textureSetup()
{
	textures["BULLET"] = new Texture();      //instead of doing new Texture
	textures["BULLET"]->loadFromFile("war/vaccine.png");
}

void Game::windowSetup()
{
	settings.antialiasingLevel = 8;
	window = new RenderWindow(VideoMode(width, height), "VACCINE WAR!", Style::Close | Style::Titlebar, settings);
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(false);
}

void Game::worldSetup()
{
	if (backgroundTexture.loadFromFile("war/world.png") != true)
	{
		cerr << "The world background file not found!\n";
	}
	backgroundSprite.setTexture(backgroundTexture);
}

void Game::GUIsetup()
{
	//LOAD FONT
	if (!font.loadFromFile("war/PixellettersFull.ttf"))
	{
		cerr << "Font not found\n";
	}
	//POINT TEXT
	pointText.setFont(font);
	pointText.setCharacterSize(50);
	pointText.setFillColor(Color::White);

	//PLAYER GUI
	playerHealthBar.setSize(Vector2f(300.f, 25.f));
	playerHealthBar.setFillColor(Color::Red);
	playerHealthBar.setPosition(Vector2f(20.f, 20.f));

	playerHealthBarBack = playerHealthBar;
	playerHealthBarBack.setFillColor(Color(25, 25, 25, 200));
}

void Game::createPlayer()
{
	player = make_unique<Player>(); //TESTME: If it doesn't work change it as Player* player
}

void Game::createEnemies()
{
	spawnTimerMax = 50.f;
	spawnTimer = spawnTimerMax;
}

void Game::run()
{
	while (window->isOpen())
	{
		update();
		render();
	}
}

void Game::render()
{
	//clear
	window->clear(Color::Black);

	//draw/render
	renderWorld();
	player->render(*window);
	renderBullet();
	renderEnemy();
	renderGUI();

	//display
	window->display();
}

void Game::update()
{
	updateEvent();
	updatePlayerMove();
	player->update();
	updateCollision();
	updateBullet();
	updateEnemies();
	updateCombat();
	updateGUI();
	updateWorld();
}

void Game::updateEvent()
{
	while (window->pollEvent(eventObj))
	{
		if (eventObj.type == Event::Closed)
			window->close();
		if (eventObj.Event::KeyPressed && eventObj.key.code == Keyboard::Escape)
			window->close();
	}
}

void Game::updateGUI()
{
	stringstream ss;
	ss <<"SCORE: "<< score;
	pointText.setString(ss.str());

	//update playerHPbar

}

void Game::updateWorld()
{
}

void Game::updateCollision() //bounce of the world and the player (thus player cannot go to outside of the world)
{
	//left side of the world collision
	if (player->getBounds().left < 0.f) //x for 0.f is the most left 
	{
		player->setPlayerPosition(0.f, player->getBounds().top);
	}

	//right side of the world collision
	else if (player->getBounds().left + player->getBounds().width >= window->getSize().x)
	{
		player->setPlayerPosition(window->getSize().x - player->getBounds().width, player->getBounds().top);
	}

	//top side of the world collision
	if (player->getBounds().top < 0.f) //0.f is the most left 
	{
		player->setPlayerPosition(player->getBounds().left, 0.f); //y for 0.f most top
	}

	//bottom side of the world collision
	else if (player->getBounds().top + player->getBounds().height >= window->getSize().y)
	{
		player->setPlayerPosition(player->getBounds().left, window->getSize().y - player->getBounds().height);
	}
	
}

void Game::updateBullet()
{
	unsigned counter=0; 

	for (auto *bullet : bullets)
	{
		bullet->update();

		//If bullet top of screen
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete bullets.at(counter);
			bullets.erase(bullets.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void Game::updateEnemies()
{
	//spawning
	spawnTimer += 0.5f;
	//pushing new enemies
	if (spawnTimer >= spawnTimerMax)
	{
		enemies.push_back(new Enemy(rand() % window->getSize().x-20, rand()% 20)); //send enemies randomly to x and y pos
		spawnTimer = 0.f;
	}
	//updating
	unsigned counter = 0;

	for (auto* enemy : enemies)
	{
		enemy->update();

		//DESTROY THE ENEMIES AND PREVENT ACCUMULATION AND DELETE THEM WHEN THEY OUT OF THE WINDOW
		if (enemy->getBounds().top + enemy->getBounds().height > window->getSize().y)
		{
			//Delete enemy from vector
			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);
			--counter;
		}
		else if (enemy->getBounds().intersects(player->getBounds()))//if they are in the screen but when they touch the player
		{
			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);
			--counter;
		}

		++counter;
	}
	
}

void Game::updateCombat()
{
	//note: enemies "i", bullets "k"
	for (int i = 0; i < enemies.size(); ++i)
	{
		bool enemyDeleted = false;
		for (size_t k = 0; k < bullets.size() && enemyDeleted==false; k++) //until you've reached the end of bullet or enemy deleted
		{
			//CHECK THE COLLISION by using their intersection
			if (enemies[i]->getBounds().intersects(bullets[k]->getBounds()))
			{
				score += enemies[i]->getPoints();                          //each damaged enemy gives point

				delete enemies.at(i);
				enemies.erase(enemies.begin() + i); //if bullet hit (collision) erase that enemy

				delete bullets.at(k);
				bullets.erase(bullets.begin() + k); //also bullet is gone

				enemyDeleted = true;
			}
		}
	}
}

void Game::updatePlayerMove()
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) player->movement(-2.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Right)) player->movement(2.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Up)) player->movement(0.f, -2.f);
	if (Keyboard::isKeyPressed(Keyboard::Down)) player->movement(0.f, 2.f);

	if (Keyboard::isKeyPressed(Keyboard::Space) && player->canAttack())
	{
		bullets.push_back(new Bullet(textures["BULLET"],
			player->getPosition().x + player->getBounds().width / 2.f, player->getPosition().y, 0.f, -1.f, 5.f));
	}
}

void Game::renderBullet()
{
	for (auto* bullet : bullets)
	{
		bullet->render(*window);
	}
}

void Game::renderGUI()
{
	window->draw(pointText);
	//window->draw(playerHealthBarBack);
	//window->draw(playerHealthBar);
}

void Game::renderEnemy()
{
	for (auto* enemy : enemies)
	{
		enemy->render(*window);
	}
}

void Game::renderWorld()
{
	window->draw(backgroundSprite);
}




