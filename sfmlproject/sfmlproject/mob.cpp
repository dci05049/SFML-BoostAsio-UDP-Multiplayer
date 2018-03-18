#include "mob.h"
#include "math.h"


Mob::Mob(Game* game, std::unique_ptr<sf::Shape> shape)
	: Sf_Entity(std::move(shape))
	, m_game(game)
{

	m_mobState = Mob_State::MOB_STATE_GROUND;
}

void Mob::update(const float dt)
{
	//Check for the mob being OOB of the map
	{
		int mapSize = 1300 * 42;

		int spriteWidth = object->getLocalBounds().width;
		int spriteHeight = object->getLocalBounds().height;
		sf::Vector2f spritePos = object->getPosition();


		if (spritePos.x >= mapSize - spriteWidth - 1)
		{
			object->setPosition(mapSize - spriteWidth - 1, spritePos.y);
		}
		if (spritePos.x + 1 <= 1)
		{
			object->setPosition(spriteWidth, spritePos.y);
		}


		if (spritePos.y > mapSize - spriteHeight - 1)
		{
			object->setPosition(spritePos.x, mapSize - spriteHeight - 1);
		}
		if (spritePos.y + 1 <= 1)
		{
			object->setPosition(spritePos.x, 1);
		}
	}
	checkVel();

	object->move(getVelocity().x, getVelocity().y);
}


const sf::Vector2i& Mob::getTileMapPosition()
{
	return m_tileMapPos;
}

void Mob::calculateVelocity(int x, int y) {
	changeVelocity({ x * m_walkSpeed, y * m_walkSpeed });
}

//Makes sure the mob can go to a complete stop and applies friction
void Mob::checkVel()
{
	const float bound = 0.01;

	if (getVelocity().x < bound &&  getVelocity().x > -bound) setVelocity({ 0, getVelocity().y });
	if (getVelocity().y < bound &&  getVelocity().y > -bound) setVelocity({ getVelocity().x, 0 });
}


void Mob::setTarget(Mob* mob)
{
	m_target = mob;
}


const Mob* Mob::getTarget() const
{
	return (m_target) ? m_target : nullptr;
}


const sf::Vector2i Mob::getTargetTilePosition()
{
	return (m_target) ? m_target->getTileMapPosition() : sf::Vector2i(0, 0);
}


bool Mob::hasTarget() const
{
	return (m_target) ? true : false;
}