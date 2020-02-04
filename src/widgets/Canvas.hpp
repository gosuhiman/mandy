#include <SFML/Graphics.hpp>
#include "../Widget.hpp"
#include "../ComplexPlane.hpp"

class Canvas : public Widget {
public:
	Canvas(unsigned int, unsigned int);
	void zoomIn(unsigned int x, unsigned int y);
	void resize(unsigned int newWidth, unsigned int newHeight);

//Widget methods
public:
	void update();
	void draw(sf::RenderWindow* target);

private:
	unsigned int width;
	unsigned int height;

	sf::Uint8* pixels;
	sf::Texture* texture;
	sf::Sprite* sprite;

	ComplexPlane<double> defaultViewport;
	ComplexPlane<double> viewport;

	sf::Color* palette;

	Complex transformToComplexPlane(int x, int y);
	void generate();
	void generatePixelRow(int py);
	void buildPalette();
};
