#pragma once

#include <SFML/Graphics.hpp>

class Widget {
public:
	virtual void update() {};
	virtual void draw(std::shared_ptr<sf::RenderWindow> target) {};

	// event handlers
	virtual void onResize(unsigned int newWidth, unsigned int newHeight) {};
};
