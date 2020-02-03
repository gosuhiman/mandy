#include "Canvas.hpp"
#include <queue>
#include <thread>
#include <mutex>

#pragma warning(disable : 26451)

const unsigned int BYTES_IN_PIXEL = 4;

const unsigned int MAX_ITERATIONS = 200;
const unsigned int ZOOM_AMMOUNT = 3;
const unsigned int THREAD_COUNT = 8;

std::mutex mtx;

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

void Canvas::zoomIn(unsigned int x, unsigned int y) {
  Complex zoomPoint = transformToComplexPlane(x, y);
  viewport.zoomTo(zoomPoint.real(), zoomPoint.imag(), ZOOM_AMMOUNT);
  generate();
}

Complex Canvas::transformToComplexPlane(int x, int y) {
  Complex c((double)x / (double)width * viewport.width() + viewport.minX,
    (double)y / (double)height * viewport.height() + viewport.minY);
  return c;
}

void Canvas::generate() {
  std::vector<std::thread> threads;
  std::queue<int> tasks;

  for (unsigned int py = 0; py < height; py++) tasks.push(py);

  for (int t = 0; t < THREAD_COUNT; t++) {
    std::thread thread([this, &tasks]() {
      while (tasks.size() > 0) {
        mtx.lock();
        int py = tasks.front();
        tasks.pop();
        mtx.unlock();
        generatePixelRow(py);
      }
    });
    threads.push_back(std::move(thread));
  }

  std::for_each(threads.begin(), threads.end(), [](std::thread& t) {
    t.join();
  });
}

void Canvas::generatePixelRow(int py) {
  for (unsigned int px = 0; px < width; px++) {
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

