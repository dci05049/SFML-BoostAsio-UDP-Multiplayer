#include "state_base.h"
#include "game.h"

/**
The base class for all the games states, such as menus, roaming, battles etc
*/

namespace State
{

	State_Base::State_Base(Game* game)
		: m_game(game)
	{ }

	State_Base :: ~State_Base() { }

}