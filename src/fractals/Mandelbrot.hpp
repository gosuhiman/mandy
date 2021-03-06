#include <array>
#include <functional>
#include <SFML/Graphics.hpp>
#include "../ComplexPlane.hpp"
#include "../services/StatsService.hpp"

const unsigned int BYTES_IN_PIXEL = 4;

const unsigned int ZOOM_INCREASE = 12;
const unsigned int DEFAULT_THREAD_COUNT = 1;

const sf::Color colors[] = {
	sf::Color(132, 195, 24),
	/*sf::Color(248, 243, 43),
	sf::Color(219, 84, 97),
	sf::Color(45, 94, 245),
	sf::Color(119, 45, 139),
	sf::Color(224, 224, 226),*/
};

class Mandelbrot {
public:
	Mandelbrot(unsigned int width, unsigned int height);
	void initialize();
	void zoomIn(unsigned int x, unsigned int y);
	void resize(unsigned int newWidth, unsigned int newHeight);
	void draw(std::function<void(sf::Uint8*)> callback);
	void changeColoringMode(std::function<void(sf::Uint8*)> callback);
	void setLastGenerationDurationCallback(std::function<void(Duration)> callback);
	void setMaxIterationsCallback(std::function<void(unsigned int)> callback);

private:
	unsigned int width;
	unsigned int height;
	unsigned int threadCount;

	std::function<void(Duration)> lastGenerationDurationCallback;
	std::function<void(unsigned int)> maxIterationsCallback;

	ComplexPlane<Number> defaultViewport;
	ComplexPlane<Number> viewport;
	unsigned int currentZoom;
	unsigned int maxIterations;

	sf::Uint8* data;
	std::array<std::vector<sf::Color>, 6> palettes;
	unsigned short currentPaletteIndex;

	Complex transformToComplexPlane(int x, int y);
	sf::Uint8* generate();
	void generatePixelRow(int py, sf::Uint8* pixels);
	sf::Uint8* regenerateWithNewColoringMode();
	void buildPalette();
	void colorPixel(unsigned int px, unsigned int py, sf::Uint8* pixels);
};
