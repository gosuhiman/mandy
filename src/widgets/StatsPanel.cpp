#include "../utils.hpp"
#include "StatsPanel.hpp"

StatsPanel::StatsPanel(std::shared_ptr<StatService> statService) : statService(statService) {
  if (!font.loadFromFile("assets/fonts/JetBrainsMono-Regular.ttf"))
    throw std::exception("failed loading font");

  setDefaultTextStyle(fpsText);
  setDefaultTextStyle(lastGeneretionDurationText);

  lastGeneretionDurationText.setPosition(0.f, 30.f);

  averageSecondsPerFrame = 0;
};

void StatsPanel::update() {
  float deltaTime = clock.getElapsedTime().asSeconds();
  averageSecondsPerFrame += (deltaTime - averageSecondsPerFrame) * 0.03f;
  clock.restart();

  if (viewUpdateClock.getElapsedTime() > sf::seconds(0.1f)) {
    float fps = 1.0f / averageSecondsPerFrame;
    fpsText.setString(numberToString<float>(fps));
    viewUpdateClock.restart();
  }

  double lastGeneretionDuration = statService->data.lastGeneretionDuration.count();
  lastGeneretionDurationText.setString(numberToString<double>(lastGeneretionDuration));
};

void StatsPanel::draw(std::shared_ptr<sf::RenderWindow> target) {
  target->draw(fpsText);
  target->draw(lastGeneretionDurationText);
}

void StatsPanel::setDefaultTextStyle(sf::Text& text) {
  text.setFont(font);
  text.setString("0");
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Regular);
}
