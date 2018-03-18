#include "game.h"
#include "test.h"
#include <iostream>

Game::Game(): io_service() {
	m_states.changeState(std::make_unique<State::Test>(this, io_service));
}

void Game::Start() {
}

void Game::runLoop() {
	sf::Clock dtClock;
	const sf::Time timeStep = sf::seconds(0.005);
	sf::Time accumulated_dt;
	dtClock.restart();
	m_states.peekState()->start_receive();

	while (m_window.isOpen())
	{
		double dt = calculateDeltaTime(dtClock, accumulated_dt);

		m_window.clear();
		if (m_window.isFocus()) {
			m_states.peekState()->input(dt);
		}

		if (accumulated_dt >= timeStep)
		{
			accumulated_dt -= timeStep;
			m_states.peekState()->update(timeStep.asSeconds());
		}

		m_states.peekState()->sfDraw(dt);
		m_window.update();
		io_service.poll();
	}

	fps.update();

}

void Game::sendToServer(std::string message) {
	m_states.peekState()->sendToServer(message);
}

const double Game::calculateDeltaTime(sf::Clock& c, sf::Time& t)
{
	sf::Time dt = c.restart();
	t += dt;
	return dt.asSeconds();
}

Window& Game::getwindow() {
	return m_window;
}

State::Handler& Game::getState() {
	return m_states;
}

std::unique_ptr<sf::Shape> Game::getShape(const Shape_Name name)
{
	return m_shapes.getShape(name);
}