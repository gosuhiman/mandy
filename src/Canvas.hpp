#include <SFML/Graphics.hpp>
#include "ComplexPlane.hpp"

class Canvas {
public:
	Canvas(unsigned int, unsigned int);
	void update();
	sf::Sprite getSprite() { return sprite; }
	void zoomIn(unsigned int x, unsigned int y);

private:
	unsigned int width;
	unsigned int height;

	sf::Uint8* pixels;
	sf::Texture texture;
	sf::Sprite sprite;

	ComplexPlane<double> defaultViewport;
	ComplexPlane<double> viewport;

	sf::Color* palette;

	Complex transformToComplexPlane(int x, int y);
	void generate();
	void generatePixelRow(int py);
	void buildPalette();
};
