#include <SFML/Graphics.hpp>
#include "../Widget.hpp"
#include "../fractals/Mandelbrot.hpp"

class Canvas : public Widget {
public:
	Canvas(unsigned int width, unsigned int height);
	void onClick(unsigned int x, unsigned int y);

//Widget methods
public:
	void update();
	void draw(sf::RenderWindow* target);
	void onResize(unsigned int newWidth, unsigned int newHeight);

private:
	unsigned int width;
	unsigned int height;

	Mandelbrot* fractal;

	sf::Texture* texture;
	sf::Sprite* sprite;
};
