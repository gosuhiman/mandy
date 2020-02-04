#include <SFML/Graphics.hpp>
#include "../Widget.hpp"

class FpsCounter : public Widget {
public:
	FpsCounter();

//Widget methods
public:
	void update();
	void draw(sf::RenderWindow* target);

private:
	sf::Clock clock;
	sf::Text text;
	sf::Font font;
};
