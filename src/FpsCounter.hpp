#include <SFML/Graphics.hpp>

class FpsCounter {
public:
	FpsCounter();
	void update();
	sf::Text getText() { return text; }

private:
	sf::Clock clock;
	sf::Text text;
	sf::Font font;
};
