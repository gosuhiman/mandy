#include <SFML/Graphics.hpp>

class Canvas {
public:
	Canvas(unsigned int, unsigned int);
	void update();
	sf::Sprite getSprite() { return sprite; }

private:
	unsigned int width;
	unsigned int height;

	sf::Uint8* pixels;
	sf::Texture texture;
	sf::Sprite sprite;
	int i;
};
