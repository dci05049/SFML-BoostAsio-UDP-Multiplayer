#ifndef  STATE_BASE_H
#define STATE_BASE_H

#include <string>

class Game;

namespace State
{
	class State_Base
	{
	public:
		State_Base(Game * game);

		virtual
			~State_Base();

		virtual void input(const double dt) = 0;

		virtual void update(const double dt) = 0;

		virtual void glDraw(const double dt) = 0;

		virtual void sfDraw(const double dt) = 0;

		virtual void sendToServer(std::string message) = 0;

		virtual void start_receive() = 0;

	protected:
		Game* m_game;
	};
}

#endif // ! STATE_BASE_H
