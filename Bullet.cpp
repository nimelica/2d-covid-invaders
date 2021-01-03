#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(Texture* texture, float xpos, float ypos, float xdir, float ydir, float speed)
{
	shapeSprite.setTexture(*texture);
	directions.x = xdir;
	directions.y = ydir;
	moveSpeed = speed;
	shapeSprite.setPosition(xpos, ypos);
}

Bullet::~Bullet()
{

}

void Bullet::update()
{
	//Update movement
	shapeSprite.move(moveSpeed * directions);
}

void Bullet::render(RenderTarget& target)
{
	target.draw(shapeSprite);
}

FloatRect Bullet::getBounds() const
{
	return shapeSprite.getGlobalBounds();
}
