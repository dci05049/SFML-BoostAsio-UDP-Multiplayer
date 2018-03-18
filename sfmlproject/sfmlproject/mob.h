#ifndef MOB_H
#define MOB_H

#include "sf_entity.h"

#include <vector>
#include <memory>
#include "game.h"

	enum Mob_State
{
	MOB_STATE_AIR
	, MOB_STATE_GROUND
	, MOB_STATE_WATER
};

class Mob : public Sf_Entity
{
	//using Comp = std::unique_ptr<Component::Component_Base>;

public:
	const sf::Vector2i& getTileMapPosition();

	void update(const float dt);

	bool isAlive() { return m_isLiving; }

	void setAlive(const bool alive) { m_isLiving = alive; }

	void setMobState(const Mob_State state) { m_mobState = state; }

	Mob_State getMobState() { return m_mobState; }

	void calculateVelocity(int x, int y);

	void setTarget(Mob* mob);

	const Mob* getTarget() const;

	const sf::Vector2i getTargetTilePosition();

	bool hasTarget() const;


protected:
	Mob(Game* game, std::unique_ptr<sf::Shape> shape); //Tile_Map* tiles);


protected:
	Game*           m_game;
	//Tile_Map*       m_tileMap;
	bool            m_isMoving{ false };

	Mob*            m_target{ nullptr };

private:

	void checkVel();

private:
	//std::vector< Comp > m_components;

	sf::Vector2i    m_tileMapPos;

	bool            m_isLiving;

	Mob_State       m_mobState;

protected: //temp
	/*const*/ float     m_walkSpeed{ 5 };
};

#endif // MOB_H