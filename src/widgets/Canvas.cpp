#include "Canvas.hpp"
#include "../ScreenshotSaver.hpp"

#pragma warning(disable : 26451)

Canvas::Canvas(unsigned int width, unsigned int height) : width(width), height(height) {
  inputBlocked = true;

  texture = std::make_unique<sf::Texture>();
  sprite = std::make_unique<sf::Sprite>();
  fractal = std::make_unique<Mandelbrot>(width, height);

  if (!texture->create(width, height)) throw std::exception("failed creating texture");
  sprite->setTexture(*texture);

  updateTextureCallback = std::bind(&Canvas::updateTexture, this, std::placeholders::_1);
}

void Canvas::initialize() {
  fractal->initialize();
  drawFractal();
}

void Canvas::draw(std::shared_ptr<sf::RenderWindow> target) {
  target->draw(*sprite);
}

void Canvas::onClick(unsigned int x, unsigned int y) {
  if (inputBlocked) return;
  inputBlocked = true;
  fractal->zoomIn(x, y);
  drawFractal();
}

void Canvas::onResize(unsigned int newWidth, unsigned int newHeight) {
  width = newWidth;
  height = newHeight;

  fractal->resize(width, height);

  texture = std::make_unique<sf::Texture>();
  if (!texture->create(width, height))
    throw std::exception("failed creating texture");

  sprite->setTexture(*texture, true);
  drawFractal();
}

void Canvas::saveScreenshot() {
  ScreenshotSaver::save(*texture);
}

void Canvas::drawFractal() {
  drawFuture = std::async(std::launch::async, &Mandelbrot::draw, *fractal, updateTextureCallback);
}

void Canvas::updateTexture(sf::Uint8* pixels) {
  if (currentPixels != nullptr) delete[] currentPixels;
  currentPixels = pixels;
  texture->update(currentPixels);
  inputBlocked = false;
}
