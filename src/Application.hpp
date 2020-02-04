#include <SFML/Graphics.hpp>
#include "Widget.hpp"
#include "widgets/Canvas.hpp"
#include "widgets/FpsCounter.hpp"

struct ApplicationSettings {
	unsigned int windowWidth;
	unsigned int windowHeight;
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

	std::vector<Widget*> widgets;
	Canvas* canvas;
	FpsCounter* fpsCounter;
};