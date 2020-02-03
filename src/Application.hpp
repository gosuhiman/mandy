#include <SFML/Graphics.hpp>
#include "Canvas.hpp"
#include "FpsCounter.hpp"

struct ApplicationSettings {
	size_t windowWidth;
	size_t windowHeight;
	const sf::String title;
	unsigned int frameLimit;
};

class Application {
public:
	Application(ApplicationSettings settings);
	void run();

private:
	ApplicationSettings settings;
	sf::RenderWindow* window;
	Canvas* canvas;
	FpsCounter* fpsCounter;
};