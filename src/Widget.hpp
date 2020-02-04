#pragma once

#include <SFML/Graphics.hpp>

class Widget {
public:
	virtual void update() {};
	virtual void draw(sf::RenderWindow* target) {};
};
