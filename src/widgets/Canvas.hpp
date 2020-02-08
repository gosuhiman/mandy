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
	void draw(std::shared_ptr<sf::RenderWindow> target);
	void onResize(unsigned int newWidth, unsigned int newHeight);

private:
	unsigned int width;
	unsigned int height;

	std::unique_ptr<Mandelbrot> fractal;

	std::unique_ptr<sf::Texture> texture;
	std::unique_ptr<sf::Sprite> sprite;
};
