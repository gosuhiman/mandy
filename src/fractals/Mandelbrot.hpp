#include <array>
#include <SFML/Graphics.hpp>
#include "../ComplexPlane.hpp"

const unsigned int BYTES_IN_PIXEL = 4;

const unsigned int MAX_ITERATIONS = 200;
const unsigned int ZOOM_AMMOUNT = 3;
const unsigned int THREAD_COUNT = 8;

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

	std::array<sf::Color, MAX_ITERATIONS> palette;

	Complex transformToComplexPlane(int x, int y);
	void generate(sf::Uint8* pixels);
	void generatePixelRow(int py, sf::Uint8* pixels);
	void buildPalette();
};
