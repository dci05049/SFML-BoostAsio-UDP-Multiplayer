#include "EnemyPlayer.h"

#include "math.h"
#include <iostream>

EnemyPlayer::EnemyPlayer(Game *game, std::string player_id, sf::Vector2f initpos)
	: Mob(game, std::make_unique<sf::CircleShape>(50)), player_id(player_id)
{
	setPosition({ initpos.x,initpos.y });
	centerSpriteOrigin();
}

std::string EnemyPlayer::getId() {
	return player_id;
}