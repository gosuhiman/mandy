#include <SFML/Graphics.hpp>

class Canvas {
public:
	Canvas(unsigned int _width, unsigned int _height);
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
