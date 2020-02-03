#include "Canvas.hpp"

Canvas::Canvas(unsigned int _width, unsigned int _height) {
  width = _width;
  height = _height;

	pixels = new sf::Uint8[800 * 600 * 4];

  if (!texture.create(width, height))
    throw std::exception("failed creating texture");

  for (unsigned int x = 0; x < width; x++) {
    for (unsigned int y = 0; y < height; y++) {
      pixels[(x + y * width) * 4] = 255;
      pixels[(x + y * width) * 4 + 1] = 0;
      pixels[(x + y * width) * 4 + 2] = 255;
      pixels[(x + y * width) * 4 + 3] = 255;
    }
  }

  texture.update(pixels);
  sprite.setTexture(texture);

  i = 1;
};

void Canvas::update() {
  for (unsigned int x = 0; x < width; x++) {
    for (unsigned int y = 0; y < height; y++) {
      pixels[(x + y * width) * 4] = i;
    }
  }

  texture.update(pixels);

  i++;
  if (i > 255) i = 1;
};
