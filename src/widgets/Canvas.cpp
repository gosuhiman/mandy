#include "Canvas.hpp"

#pragma warning(disable : 26451)

Canvas::Canvas(unsigned int width, unsigned int height) : width(width), height(height) {
  texture = std::make_unique<sf::Texture>();
  sprite = std::make_unique<sf::Sprite>();

  if (!texture->create(width, height))
    throw std::exception("failed creating texture");

  fractal = std::make_unique<Mandelbrot>(width, height);

  texture->update(fractal->pixels);
  sprite->setTexture(*texture);
}

void Canvas::update() {
}

void Canvas::draw(std::shared_ptr<sf::RenderWindow> target) {
  target->draw(*sprite);
}

void Canvas::onClick(unsigned int x, unsigned int y) {
  fractal->zoomIn(x, y);
  texture->update(fractal->pixels);
}

void Canvas::onResize(unsigned int newWidth, unsigned int newHeight) {
  width = newWidth;
  height = newHeight;

  fractal->resize(width, height);

  texture = std::make_unique<sf::Texture>();
  if (!texture->create(width, height))
    throw std::exception("failed creating texture");

  texture->update(fractal->pixels);
  sprite->setTexture(*texture, true);
}
