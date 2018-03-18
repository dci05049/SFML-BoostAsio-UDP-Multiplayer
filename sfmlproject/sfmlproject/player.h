#ifndef PLAYER_H
#define PLAYER_H


#include "game.h"
#include "mob.h"
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class Player : public Mob
{
public:
	Player(Game* game, sf::Vector2f initpos);

	void input(const float dt);

	std::string getId();

private:

	void updateView();
private:
	sf::View            m_view;
	sf::RenderWindow*   m_window;
	float maxVel;
	std::string player_id;

	//Animation           m_walkAnim;
};

#endif // PLAYER_H