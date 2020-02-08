#include <SFML/Graphics.hpp>
#include "../Widget.hpp"

class FpsCounter : public Widget {
public:
	FpsCounter();

//Widget methods
public:
	void update();
	void draw(std::shared_ptr<sf::RenderWindow> target);

private:
	sf::Clock clock;
	sf::Clock viewUpdateClock;
	sf::Text text;
	sf::Font font;

	float averageSecondsPerFrame;
};
