#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Player
{
public:
	Player();
	virtual ~Player();

	//Public functions
	void update();
	void updateCalmDown();
	void render(RenderTarget& target);
	void movement(const float xdir, const float ydir);
	const bool canAttack();

	//modifiers/setters
	void setPlayerPosition(const Vector2f position);
	void setPlayerPosition(const float x, const float y);
	void setHP(const int hp);
	void setLoseHp(const int pointLosed);

	//Accessor/getters
	const Vector2f& getPosition() const;
	FloatRect getBounds()const;
	const int& getHP() const;
	const int& getHPmax() const;

private:
	Texture playerTexture;
	Sprite playerSprite;
	float movementSpeed;

	int hp;
	int hpMax;

	float attackCalmDown;
	float attackCalmDownMax;

	//Private functions
	void textureSetup();
	void spriteSetup();
	void variablesSetup();
	
};

