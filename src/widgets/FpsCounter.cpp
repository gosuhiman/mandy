#include "../utils.hpp"
#include "FpsCounter.hpp"

FpsCounter::FpsCounter() {
  if (!font.loadFromFile("assets/fonts/JetBrainsMono-Regular.ttf"))
    throw std::exception("failed loading font");

  text.setFont(font);
  text.setString("0");
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Regular);

  averageSecondsPerFrame = 0;
};

void FpsCounter::update() {
  float deltaTime = clock.getElapsedTime().asSeconds();
  averageSecondsPerFrame += (deltaTime - averageSecondsPerFrame) * 0.03f;
  clock.restart();

  if (viewUpdateClock.getElapsedTime() > sf::seconds(0.1f)) {
    float fps = 1.0f / averageSecondsPerFrame;
    text.setString(floatToString(fps));
    viewUpdateClock.restart();
  }
};

void FpsCounter::draw(sf::RenderWindow* target) {
  target->draw(text);
}
