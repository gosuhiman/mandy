#include <math.h>
#include "FpsCounter.hpp"

FpsCounter::FpsCounter() {
  if (!font.loadFromFile("assets/fonts/JetBrainsMono-Regular.ttf"))
    throw std::exception("failed loading font");

  text.setFont(font);
  text.setString("0");
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Regular);
};

void FpsCounter::update() {
  sf::Time time = clock.getElapsedTime();
  std::string fpsString = std::to_string(round(1.0f / time.asSeconds()));
  text.setString(fpsString);
  clock.restart();
};

void FpsCounter::draw(sf::RenderWindow* target) {
  target->draw(text);
}
