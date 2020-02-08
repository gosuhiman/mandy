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
	std::shared_ptr<sf::RenderWindow> window;

	std::vector<std::shared_ptr<Widget>> widgets;
	std::shared_ptr<Canvas> canvas;
	std::shared_ptr<FpsCounter> fpsCounter;
};