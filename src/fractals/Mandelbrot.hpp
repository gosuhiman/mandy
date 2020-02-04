#include <SFML/Graphics.hpp>
#include "../ComplexPlane.hpp"

class Mandelbrot {
public:
	Mandelbrot(unsigned int width, unsigned int height);
	void zoomIn(unsigned int x, unsigned int y);
	void resize(unsigned int newWidth, unsigned int newHeight);

	sf::Uint8* pixels;

private:
	unsigned int width;
	unsigned int height;

	ComplexPlane<double> defaultViewport;
	ComplexPlane<double> viewport;

	sf::Color* palette;

	Complex transformToComplexPlane(int x, int y);
	void generate(sf::Uint8* pixels);
	void generatePixelRow(int py, sf::Uint8* pixels);
	void buildPalette();
};
