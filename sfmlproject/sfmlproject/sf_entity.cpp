#include "sf_entity.h"


Sf_Entity::Sf_Entity(std::unique_ptr<sf::Shape> s)
	: object(std::move(s))
{
}

void Sf_Entity::draw(sf::RenderWindow& window)
{
	if (!inWindowBounds(window)) return;
	window.draw(*object);
}


void Sf_Entity::centerSpriteOrigin()
{
	sf::FloatRect r = object->getLocalBounds();

	object->setOrigin(r.width / 2, r.height / 2);
}

bool Sf_Entity::inWindowBounds(const sf::RenderWindow& window) const
{
	sf::Vector2f winPos = window.getView().getCenter();

	if (object->getPosition().x  < winPos.x - Win_Info::WIDTH / 2 - object->getLocalBounds().width)    return false;
	else if (object->getPosition().y  < winPos.y - Win_Info::HEIGHT / 2 - object->getLocalBounds().height)    return false;
	else if (object->getPosition().x  > winPos.x + Win_Info::WIDTH / 2) return false;
	else if (object->getPosition().y  > winPos.y + Win_Info::WIDTH / 2) return false;

	return true;
}

void Sf_Entity::setRotation(const double rot)
{
	object->setRotation(rot);
}

float Sf_Entity::getRotation() const
{
	return object->getRotation();
}


const sf::Vector2f& Sf_Entity::getOrigin() const
{
	return object->getOrigin();
}


void Sf_Entity::setPosition(const sf::Vector2f& pos)
{
	object->setPosition({ pos.x,pos.y });
}


const sf::Vector2f& Sf_Entity::getPosition() const
{
	return object->getPosition();
}


const sf::Vector2u Sf_Entity::getSpriteSize() const
{
	return object->getTexture()->getSize();
}


void Sf_Entity::setVelocity(const sf::Vector2f& velocity)
{
	m_velocity = velocity;
}


void Sf_Entity::changeVelocity(const sf::Vector2f& velocity)
{
	m_velocity = velocity;
}


const sf::Vector2f Sf_Entity::getVelocity() const
{
	return m_velocity;
}


void Sf_Entity::setColor(const sf::Color& col)
{
	object->setFillColor(col);
}