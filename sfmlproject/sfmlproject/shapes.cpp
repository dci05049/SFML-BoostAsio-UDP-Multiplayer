#include "shapes.h"

Shapes::Shapes() {
	initialize();
}

void Shapes::initialize() {
	shape_map[Player_Shape] = std::make_unique<sf::CircleShape>(50);
	shape_map[Enemy_Shape] = std::make_unique<sf::CircleShape>(50);
}

void Shapes::loadShape(const Shape_Name shapeName) {

}

std::unique_ptr<sf::Shape> Shapes::getShape(const Shape_Name name) {
	return std::move(shape_map[name]);
}