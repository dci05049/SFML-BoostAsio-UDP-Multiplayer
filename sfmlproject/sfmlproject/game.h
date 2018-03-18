#ifndef GAME_H
#define	GAME_H

#include <boost/asio.hpp>
#include "window.h"
#include "fps_counter.h"
#include "handler.h"
#include "textures.h"
#include "shapes.h"
#include <Vector>

class Game
{
public: 
	Game();

	void Start();

	void runLoop(); 

	void sendToServer(std::string message);

	Window& getwindow();

	State::Handler& getState();

	std::unique_ptr<sf::Shape> getShape(const Shape_Name shape);

private: 

	const double calculateDeltaTime(sf::Clock& c, sf::Time&t);

	Window m_window;

	FPS_Counter fps;

	State::Handler m_states;

	boost::asio::io_service io_service;

	Shapes m_shapes;
};

#endif // ! Game_H
