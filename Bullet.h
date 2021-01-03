#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Bullet
{
public:
	Bullet();
	Bullet(Texture* texture, float xpos, float ypos, float xdir, float ydir, float speed);
	virtual ~Bullet();

	void update();
	void render(RenderTarget& target); //if it doesnt work change as a pointer
	FloatRect getBounds()const;

private:
	Sprite shapeSprite;

	Vector2f directions;    //provides x and y
	float moveSpeed;
};

