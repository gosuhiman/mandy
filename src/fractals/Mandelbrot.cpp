#include "Mandelbrot.hpp"
#include <chrono>
#include <queue>
#include <thread>
#include <mutex>
#include <iostream>

#pragma warning(disable : 26451)
#pragma warning(disable : 28020)

std::mutex mtx;

Mandelbrot::Mandelbrot(unsigned int width, unsigned int height) : width(width), height(height) {
  defaultViewport = ComplexPlane<double>(-2.2, -1.2, 1, 1.2);
  viewport = defaultViewport;
  viewport.updateForProportions(double(height) / double(width));
  threadCount = std::thread::hardware_concurrency();
  if (threadCount == 0) threadCount = DEFAULT_THREAD_COUNT;
  data = new sf::Uint8[width * height];
  currentPaletteIndex = 0;
}

void Mandelbrot::initialize() {
  buildPalette();
}

void Mandelbrot::draw(std::function<void(sf::Uint8*)> callback) {
  callback(generate());
}

void Mandelbrot::setLastGenerationDurationCallback(std::function<void(Duration)> callback) {
  lastGenerationDurationCallback = callback;
}

void Mandelbrot::changeColoringMode(std::function<void(sf::Uint8*)> callback) {
  currentPaletteIndex++;
  if (currentPaletteIndex >= palettes.size()) currentPaletteIndex = 0;
  callback(regenerateWithNewColoringMode());
}

void Mandelbrot::zoomIn(unsigned int x, unsigned int y) {
  Complex zoomPoint = transformToComplexPlane(x, y);
  viewport.zoomTo(zoomPoint.real(), zoomPoint.imag(), ZOOM_AMMOUNT);
}

void Mandelbrot::resize(unsigned int newWidth, unsigned int newHeight) {
  width = newWidth;
  height = newHeight;
  viewport.updateForProportions(double(height) / double(width));
  delete[] data;
  data = new sf::Uint8[width * height];
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

  auto timePointBefore = std::chrono::high_resolution_clock::now();

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

  auto timePointAfter = std::chrono::high_resolution_clock::now();
  lastGenerationDurationCallback(timePointAfter - timePointBefore);

  return pixels;
}

void Mandelbrot::generatePixelRow(int py, sf::Uint8* pixels) {
  for (unsigned int px = 0; px < width; px++) {
    Complex c = transformToComplexPlane(px, py);
    sf::Uint8 i = 0;

    double cr = c.real();
    double ci = c.imag();
    double zr = 0;
    double zi = 0;
    double zrsqr = zr * zr;
    double zisqr = zi * zi;
    while (zrsqr + zisqr < 4 && i < MAX_ITERATIONS) {
      zi = zr * zi;
      zi += zi;
      zi += ci;
      zr = zrsqr - zisqr + cr;
      zrsqr = zr * zr;
      zisqr = zi * zi;
      i++;
    }
    data[px + py * width] = i;
    colorPixel(px, py, pixels);
  }
}

sf::Uint8* Mandelbrot::regenerateWithNewColoringMode() {
  sf::Uint8* pixels = new sf::Uint8[width * height * BYTES_IN_PIXEL];
  for (unsigned int py = 0; py < height; py++) {
    for (unsigned int px = 0; px < width; px++) {
      colorPixel(px, py, pixels);
    }
  }
  return pixels;
}

void Mandelbrot::colorPixel(unsigned int px, unsigned int py, sf::Uint8* pixels) {
  sf::Uint8 i = data[px + py * width];
  sf::Color color = palettes[currentPaletteIndex][i - 1];
  pixels[(px + py * width) * 4] = color.r;
  pixels[(px + py * width) * 4 + 1] = color.g;
  pixels[(px + py * width) * 4 + 2] = color.b;
  pixels[(px + py * width) * 4 + 3] = 255;
}

void Mandelbrot::buildPalette() {
  float r, g, b;

  for (int i = 0; i < MAX_ITERATIONS; i++) {
    for (int c = 0; c < 6; c++) {
      r = i * (float)colors[c].r / MAX_ITERATIONS;
      g = i * (float)colors[c].g / MAX_ITERATIONS;
      b = i * (float)colors[c].b / MAX_ITERATIONS;
      palettes[c][i] = sf::Color(sf::Uint8(r), sf::Uint8(g), sf::Uint8(b));
    }
  }

  currentPaletteIndex = 0;
}
