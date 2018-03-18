#ifndef ENEMYPLAYER_H
#define ENEMYPLAYER_H


#include "game.h"
#include "mob.h"
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class EnemyPlayer : public Mob
{
public:
	EnemyPlayer(Game *game, std::string player_id, sf::Vector2f initpos);

	std::string getId();

private:
	float maxVel;
	std::string player_id;

	//Animation           m_walkAnim;
};

#endif // PLAYER_H