#include "Mandelbrot.hpp"
#include <queue>
#include <thread>
#include <mutex>

#pragma warning(disable : 26451)

std::mutex mtx;

Mandelbrot::Mandelbrot(unsigned int width, unsigned int height) : width(width), height(height) {
  defaultViewport = ComplexPlane<double>(-2.2, -1.2, 1, 1.2);
  viewport = defaultViewport;
  viewport.updateForProportions(double(height) / double(width));
  threadCount = std::thread::hardware_concurrency();
  if (threadCount == 0) threadCount = DEFAULT_THREAD_COUNT;
}

void Mandelbrot::initialize() {
  buildPalette();
}

void Mandelbrot::draw(std::function<void(sf::Uint8*)> callback) {
  callback(generate());
}

void Mandelbrot::zoomIn(unsigned int x, unsigned int y) {
  Complex zoomPoint = transformToComplexPlane(x, y);
  viewport.zoomTo(zoomPoint.real(), zoomPoint.imag(), ZOOM_AMMOUNT);
}

void Mandelbrot::resize(unsigned int newWidth, unsigned int newHeight) {
  width = newWidth;
  height = newHeight;
  viewport.updateForProportions(double(height) / double(width));
}

Complex Mandelbrot::transformToComplexPlane(int x, int y) {
  Complex c((double)x / (double)width * viewport.width() + viewport.minX,
    (double)y / (double)height * viewport.height() + viewport.minY);

  return c;
}

sf::Uint8* Mandelbrot::generate() {
  sf::Uint8* pixels = new sf::Uint8[width * height * BYTES_IN_PIXEL];
  std::queue<int> tasks;
  std::vector<std::thread> threads;

  for (unsigned int py = 0; py < height; py++) tasks.push(py);

  for (int t = 0; t < threadCount; t++) {
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

  for (std::thread& t : threads) t.join();
  return pixels;
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