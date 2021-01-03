#include "Player.h"

Player::Player()
{
	variablesSetup();
	textureSetup();
	spriteSetup();
}

Player::~Player()
{
}

void Player::update()
{
	updateCalmDown();
}

void Player::updateCalmDown()
{
	if(attackCalmDown < attackCalmDownMax)
	attackCalmDown += 0.6f;
}

void Player::render(RenderTarget& target)
{
	target.draw(playerSprite);
}

void Player::movement(const float xdir, const float ydir)
{
	playerSprite.move(movementSpeed*xdir, movementSpeed*ydir);
}

const bool Player::canAttack()
{
	if (attackCalmDown >= attackCalmDownMax)
	{
		attackCalmDown = 0.f;
		return true;
	}
	return false;
}

void Player::setPlayerPosition(const Vector2f position)
{
}

void Player::setPlayerPosition(const float x, const float y)
{
	playerSprite.setPosition(x, y);
}

void Player::setHP(const int hp)
{
	this->hp = hp;
}

void Player::setLoseHp(const int pointLosed)
{
	hp -= pointLosed;
}

const Vector2f& Player::getPosition() const
{
	return playerSprite.getPosition();
}

FloatRect Player::getBounds() const
{
	return playerSprite.getGlobalBounds();
}

const int& Player::getHP() const
{
	return hp;
}

const int& Player::getHPmax() const
{
	return hpMax;
}

void Player::textureSetup()
{
	if (playerTexture.loadFromFile("war/warrior.png") != true)
	{
		cerr << "Player texture not found!\n";
	}

	spriteSetup();
}

void Player::spriteSetup()
{
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(0.76f, 0.76f);
	playerSprite.setColor(Color::White);
}

void Player::variablesSetup()
{
	movementSpeed = 2.f;
	attackCalmDownMax = 10.f;
	attackCalmDown = attackCalmDownMax;
	hpMax = 10;
	hp = hpMax;
}


