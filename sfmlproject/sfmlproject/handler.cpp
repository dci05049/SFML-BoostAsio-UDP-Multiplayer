#include "handler.h"

/**
State::Handler handles all the states that will be used by the main "Game" class
*/

namespace State
{

	typedef std::unique_ptr<State_Base> StatePtr;

	Handler :: ~Handler()
	{
		while (!states.empty())
		{
			popState();
		}
	}

	void Handler::changeState(StatePtr state)
	{
		popState();
		states.push(std::move(state));
	}


	void Handler::pushState(StatePtr state)
	{
		states.push(std::move(state));
	}

	void Handler::popState()
	{
		if (!states.empty())
		{
			states.pop();
		}
	}

	State_Base* Handler::peekState()
	{
		return states.top().get();
	}

}