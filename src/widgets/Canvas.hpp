#include <future>
#include <SFML/Graphics.hpp>
#include "../Widget.hpp"
#include "../fractals/Mandelbrot.hpp"

class Canvas : public Widget {
public:
	Canvas(unsigned int width, unsigned int height);
	void onClick(unsigned int x, unsigned int y);

//Widget methods
public:
	void initialize();
	void update() {};
	void draw(std::shared_ptr<sf::RenderWindow> target);
	void onResize(unsigned int newWidth, unsigned int newHeight);
	void saveScreenshot();

private:
	unsigned int width;
	unsigned int height;
	bool inputBlocked;

	std::unique_ptr<Mandelbrot> fractal;

	std::unique_ptr<sf::Texture> texture;
	std::unique_ptr<sf::Sprite> sprite;

	void drawFractal();
	void updateTexture(sf::Uint8* pixels);

	std::future<void> drawFuture;
	sf::Uint8* currentPixels = nullptr;
	std::function<void(sf::Uint8*)> updateTextureCallback;
};
