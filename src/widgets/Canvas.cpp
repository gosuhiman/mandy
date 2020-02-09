#include "Canvas.hpp"

#pragma warning(disable : 26451)
#pragma warning(disable : 26444)

Canvas::Canvas(unsigned int width, unsigned int height) : width(width), height(height) {
  texture = std::make_unique<sf::Texture>();
  sprite = std::make_unique<sf::Sprite>();
  fractal = std::make_unique<Mandelbrot>(width, height);

  if (!texture->create(width, height)) throw std::exception("failed creating texture");
  sprite->setTexture(*texture);
}

void Canvas::initialize() {
  fractal->initialize();
  drawFuture = std::async(std::launch::async, &Mandelbrot::draw, *fractal, [&](sf::Uint8* pixels) {
    currentPixels = pixels;
    texture->update(currentPixels);
  });
}

void Canvas::update() {
}

void Canvas::draw(std::shared_ptr<sf::RenderWindow> target) {
  target->draw(*sprite);
}

void Canvas::onClick(unsigned int x, unsigned int y) {
  fractal->zoomIn(x, y);
  drawFuture = std::async(std::launch::async, &Mandelbrot::draw, *fractal, [&](sf::Uint8* pixels) {
    delete[] currentPixels;
    currentPixels = pixels;
    texture->update(currentPixels);
  });
}

void Canvas::onResize(unsigned int newWidth, unsigned int newHeight) {
  width = newWidth;
  height = newHeight;

  fractal->resize(width, height);

  texture = std::make_unique<sf::Texture>();
  if (!texture->create(width, height))
    throw std::exception("failed creating texture");

  drawFuture = std::async(std::launch::async, &Mandelbrot::draw, *fractal, [&](sf::Uint8* pixels) {
    delete[] currentPixels;
    currentPixels = pixels;
    texture->update(currentPixels);
    sprite->setTexture(*texture, true);
  });
}
