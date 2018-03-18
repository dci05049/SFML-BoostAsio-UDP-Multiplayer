#include "window.h"

Window::Window()
{
	//General window stuff
	m_window.create(sf::VideoMode(Win_Info::WIDTH, Win_Info::HEIGHT),
		"Window",
		sf::Style::Default,
		sf::ContextSettings(24));
	m_window.setFramerateLimit(120);
	m_window.setPosition({ 0, 0 });

}

sf::RenderWindow& Window::get()
{
	return m_window;
}

void Window::clear()
{
	m_window.clear();
}

void Window::update()
{
	m_window.display();
	winEvents();
}

bool Window::isOpen()
{
	return m_window.isOpen();
}

bool Window::isFocus() {
	return focused;
}

void Window::winEvents()
{
	sf::Event e;

	while (m_window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			m_window.close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_window.close();
		}
		else if (e.type == sf::Event::GainedFocus) {
			focused = true;
		}
		else if (e.type == sf::Event::LostFocus) {
			focused = false;
		}
	}
}

void Window::close()
{
	m_window.close();
}