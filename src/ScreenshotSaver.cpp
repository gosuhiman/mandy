#include <chrono>
#include <string>
#include "ScreenshotSaver.hpp"

using namespace std::chrono;

void ScreenshotSaver::save(sf::Texture& texture) {
	int64_t timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	texture.copyToImage().saveToFile("screenshot" + std::to_string(timestamp) + ".png");
}
