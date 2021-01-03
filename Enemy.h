#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Enemy
{
public:
	Enemy(float xpos, float ypos);
	virtual ~Enemy();

	//public functions
	void update();
	void render(RenderTarget& target); //change as pointer if error
	const FloatRect getBounds() const;
	const int& getPoints() const;

private:
	CircleShape virusShape;
	int hp;
	int type;
	int maxHP;
	int damage;
	int points;
	float speed;
	unsigned scorePoint;
	Texture virus;

	//private functions
	void variablesSetup();
	void shapeSetup();
};

