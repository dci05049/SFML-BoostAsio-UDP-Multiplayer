#include "player.h"

#include "math.h"
#include <iostream>

using namespace boost::property_tree;
Player::Player(Game* game, sf::Vector2f initpos = { 0,0 })
	: Mob(game, game->getShape(Player_Shape))
	, m_window(&game->getwindow().get()), maxVel(15)
{
	setPosition(initpos);
	centerSpriteOrigin();
}

void Player::input(const float dt)
{
	m_isMoving = false;
	int x_dir = 0;
	int y_dir = 0;

	ptree root;
	root.put("type", "movement");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		y_dir -= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{	
		y_dir += 1;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		x_dir -= 1;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		x_dir += 1;
	}

	root.put("x", getPosition().x);
	root.put("y", getPosition().y);

	std::ostringstream buf;
	write_json(buf, root, false);
	std::string data = buf.str();

	m_game->sendToServer(data);
	calculateVelocity(x_dir, y_dir);
}

std::string Player::getId() {
	return player_id;
}

void Player::updateView()
{
	m_view.setCenter(object->getPosition());   //Centres camera
												//to the player
	m_window->setView(m_view);      //Set the windows view to the camera
}