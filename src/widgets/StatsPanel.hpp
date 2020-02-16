#include <SFML/Graphics.hpp>
#include "../services/StatsService.hpp"
#include "../Widget.hpp"

class StatsPanel : public Widget {
public:
	StatsPanel(std::shared_ptr<StatService> statService);

//Widget methods
public:
	void initialize() {};
	void update();
	void draw(std::shared_ptr<sf::RenderWindow> target);

private:
	std::shared_ptr<StatService> statService;

	sf::Clock clock;
	sf::Clock viewUpdateClock;
	sf::Text fpsText;
	sf::Text lastGeneretionDurationText;
	sf::Text maxIterationsText;
	sf::Font font;

	float averageSecondsPerFrame;

	void setDefaultTextStyle(sf::Text& text);
};
