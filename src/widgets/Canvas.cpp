#include "Canvas.hpp"
#include "../ScreenshotSaver.hpp"

#pragma warning(disable : 26451)

Canvas::Canvas(unsigned int width, unsigned int height) : width(width), height(height) {
  inputBlocked = true;

  sprite = std::make_unique<sf::Sprite>();
  fractal = std::make_unique<Mandelbrot>(width, height);

  createNewTexture();
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
  inputBlocked = true;
  fractal->resize(width, height);
  createNewTexture();
  sprite->setTexture(*texture, true);
  drawFractal();
}

void Canvas::saveScreenshot() {
  ScreenshotSaver::save(*texture);
}

void Canvas::changeColoringMode() {
  if (inputBlocked) return;
  inputBlocked = true;
  drawFuture = std::async(std::launch::async, &Mandelbrot::changeColoringMode, &*fractal, updateTextureCallback);
}

void Canvas::drawFractal() {
  drawFuture = std::async(std::launch::async, &Mandelbrot::draw, &*fractal, updateTextureCallback);
}

void Canvas::createNewTexture() {
  texture = std::make_unique<sf::Texture>();
  if (!texture->create(width, height)) throw std::exception("failed creating texture");
}

void Canvas::updateTexture(sf::Uint8* pixels) {
  if (currentPixels != nullptr) delete[] currentPixels;
  currentPixels = pixels;
  texture->update(currentPixels);
  inputBlocked = false;
}
