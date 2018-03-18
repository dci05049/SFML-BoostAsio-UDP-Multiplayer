#ifndef SHAPES_H
#define SHAPES_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "window.h"

enum Shape_Name {
	Player_Shape,
	Enemy_Shape
};

class Shapes {
public:
	Shapes();
	void initialize();
	void loadShape(const Shape_Name name);
	std::unique_ptr<sf::Shape> getShape(const Shape_Name name);
	
private:
	std::map < Shape_Name, std::unique_ptr<sf::Shape>> shape_map;
	
};

#endif // SF_ENTITY_H