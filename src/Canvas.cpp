#include "Canvas.hpp"

#pragma warning(disable : 26451)

const unsigned int BYTES_IN_PIXEL = 4;

const unsigned int MAX_ITERATIONS = 80;

Canvas::Canvas(unsigned int width, unsigned int height) : width(width), height(height) {
	pixels = new sf::Uint8[width * height * BYTES_IN_PIXEL];

  if (!texture.create(width, height))
    throw std::exception("failed creating texture");

  texture.update(pixels);
  sprite.setTexture(texture);

  defaultViewport = ComplexPlane<double>(-2.4, -1.2, 0.9, 1.2);
  viewport = defaultViewport;

  buildPalette();
  generate();
}

void Canvas::update() {
  texture.update(pixels);
}

Complex Canvas::transformToComplexPlane(int x, int y) {
  Complex c((double)x / (double)width * viewport.width() + viewport.minX,
    (double)y / (double)height * viewport.height() + viewport.minY);
  return c;
}

void Canvas::generate() {
  for (unsigned int px = 0; px < width; px++) {
    for (unsigned int py = 0; py < height; py++) {
      Complex c = transformToComplexPlane(px, py);
      Complex z = Complex(0);
      int i = 0;

      while (std::abs(z) < 2 && i < MAX_ITERATIONS) {
        z = z * z + c;
        i++;
      }

      sf::Color color = palette[i];
      pixels[(px + py * width) * 4] = color.r;
      pixels[(px + py * width) * 4 + 1] = color.g;
      pixels[(px + py * width) * 4 + 2] = color.b;
      pixels[(px + py * width) * 4 + 3] = 255;
    }
  }
}

void Canvas::buildPalette() {
  palette = new sf::Color[width * height];
  float r, g, b;

  for (int i = 0; i < MAX_ITERATIONS; i++)
  {
    r = i * 100.f / MAX_ITERATIONS;
    g = i * 255.f / MAX_ITERATIONS;
    b = i * 50.f / MAX_ITERATIONS;
    palette[i] = sf::Color(sf::Uint8(r), sf::Uint8(g), sf::Uint8(b));
  }
}

