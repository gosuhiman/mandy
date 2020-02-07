#include "Canvas.hpp"

#pragma warning(disable : 26451)

Canvas::Canvas(unsigned int width, unsigned int height) : width(width), height(height) {
  texture = new sf::Texture();
  sprite = new sf::Sprite();

  if (!texture->create(width, height))
    throw std::exception("failed creating texture");

  fractal = new Mandelbrot(width, height);

  texture->update(fractal->pixels);
  sprite->setTexture(*texture);
}

void Canvas::update() {
}

void Canvas::draw(sf::RenderWindow* target) {
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

  delete texture;
  texture = new sf::Texture();
  if (!texture->create(width, height))
    throw std::exception("failed creating texture");

  texture->update(fractal->pixels);
  sprite->setTexture(*texture, true);
}
