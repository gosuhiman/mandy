#include "Mandelbrot.hpp"
#include <queue>
#include <thread>
#include <mutex>

#pragma warning(disable : 26451)

std::mutex mtx;

Mandelbrot::Mandelbrot(unsigned int width, unsigned int height) : width(width), height(height) {
  pixels = new sf::Uint8[width * height * BYTES_IN_PIXEL];

  defaultViewport = ComplexPlane<double>(-2.2, -1.2, 1, 1.2);
  viewport = defaultViewport;
  viewport.updateForProportions(double(height) / double(width));

  buildPalette();
  generate(pixels);
}

void Mandelbrot::zoomIn(unsigned int x, unsigned int y) {
  Complex zoomPoint = transformToComplexPlane(x, y);
  viewport.zoomTo(zoomPoint.real(), zoomPoint.imag(), ZOOM_AMMOUNT);
  generate(pixels);
}

void Mandelbrot::resize(unsigned int newWidth, unsigned int newHeight) {
  width = newWidth;
  height = newHeight;
  viewport.updateForProportions(double(height) / double(width));
  delete[] pixels;
  pixels = new sf::Uint8[width * height * BYTES_IN_PIXEL];
  generate(pixels);
}

Complex Mandelbrot::transformToComplexPlane(int x, int y) {
  Complex c((double)x / (double)width * viewport.width() + viewport.minX,
    (double)y / (double)height * viewport.height() + viewport.minY);

  return c;
}

void Mandelbrot::generate(sf::Uint8* pixels) {
  std::vector<std::thread> threads;
  std::queue<int> tasks;

  for (unsigned int py = 0; py < height; py++) tasks.push(py);

  for (int t = 0; t < THREAD_COUNT; t++) {
    std::thread thread([&]() {
      while (tasks.size() > 0) {
        mtx.lock();
        int py = tasks.front();
        tasks.pop();
        mtx.unlock();
        generatePixelRow(py, pixels);
      }
    });
    threads.push_back(std::move(thread));
  }

  std::for_each(threads.begin(), threads.end(), [](std::thread& t) {
    t.join();
  });
}

void Mandelbrot::generatePixelRow(int py, sf::Uint8* pixels) {
  for (unsigned int px = 0; px < width; px++) {
    Complex c = transformToComplexPlane(px, py);
    Complex z = Complex(0);
    int i = 0;

    while (std::abs(z) < 2 && i < MAX_ITERATIONS) {
      z = z * z + c;
      i++;
    }

    sf::Color color = palette[i - 1];
    pixels[(px + py * width) * 4] = color.r;
    pixels[(px + py * width) * 4 + 1] = color.g;
    pixels[(px + py * width) * 4 + 2] = color.b;
    pixels[(px + py * width) * 4 + 3] = 255;
  }
}

void Mandelbrot::buildPalette() {
  float r, g, b;

  for (int i = 0; i < MAX_ITERATIONS; i++)
  {
    r = i * 100.f / MAX_ITERATIONS;
    g = i * 255.f / MAX_ITERATIONS;
    b = i * 50.f / MAX_ITERATIONS;
    palette[i] = sf::Color(sf::Uint8(r), sf::Uint8(g), sf::Uint8(b));
  }
}