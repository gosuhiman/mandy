#include <array>
#include <functional>
#include <SFML/Graphics.hpp>
#include "../ComplexPlane.hpp"

const unsigned int BYTES_IN_PIXEL = 4;

const unsigned int MAX_ITERATIONS = 200;
const unsigned int ZOOM_AMMOUNT = 3;
const unsigned int DEFAULT_THREAD_COUNT = 1;

class Mandelbrot {
public:
	Mandelbrot(unsigned int width, unsigned int height);
	void initialize();
	void zoomIn(unsigned int x, unsigned int y);
	void resize(unsigned int newWidth, unsigned int newHeight);
	void draw(std::function<void(sf::Uint8*)> callback);

private:
	unsigned int width;
	unsigned int height;
	unsigned int threadCount;

	ComplexPlane<double> defaultViewport;
	ComplexPlane<double> viewport;

	std::array<sf::Color, MAX_ITERATIONS> palette;

	Complex transformToComplexPlane(int x, int y);
	sf::Uint8* generate();
	void generatePixelRow(int py, sf::Uint8* pixels);
	void buildPalette();
};
