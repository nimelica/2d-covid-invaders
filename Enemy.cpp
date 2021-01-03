#include "Enemy.h"

Enemy::Enemy(float xpos, float ypos)
{
	virusShape.setPosition(xpos, ypos);
	shapeSetup();
	variablesSetup();
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
	virusShape.move(0.f, speed);
}

void Enemy::render(RenderTarget& target)
{
	target.draw(virusShape);
}

const FloatRect Enemy::getBounds() const
{
	return virusShape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return points;
}

void Enemy::variablesSetup()
{
	hp = 0;
	type = 0;
	speed = 6.f;
	maxHP = 10;
    damage = 1;
    points = 5;
	scorePoint = rand() % 8 + 3; //minimum score value is gonna be 3 and rand()% 8 mean is 0 to 8 so 7 numbers, 10 at total
	//if score is 0 when hit a virus, the point automatically will be 3 because of the +3

}

void Enemy::shapeSetup()
{
	virusShape.setRadius(rand() % 20 + 20);
	virusShape.setPointCount(static_cast<size_t>(rand() % 20 + 3));
	virus.loadFromFile("war/virus.png");
	virusShape.setTexture(&virus);
	virusShape.setFillColor(Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)); //RGB colors randomly between 1 and 255
	virusShape.setOutlineThickness(3.f);
	virusShape.setOutlineColor(Color::Black);
}


