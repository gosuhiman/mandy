#include "../utils.hpp"
#include "StatsPanel.hpp"

StatsPanel::StatsPanel(std::shared_ptr<StatService> statService) : statService(statService) {
  if (!font.loadFromFile("assets/fonts/JetBrainsMono-Regular.ttf"))
    throw std::exception("failed loading font");

  setDefaultTextStyle(fpsText);
  setDefaultTextStyle(lastGeneretionDurationText);
  setDefaultTextStyle(maxIterationsText);

  fpsText.setPosition(2.f, 2);
  lastGeneretionDurationText.setPosition(2.f, 17.f);
  maxIterationsText.setPosition(2.f, 32.f);

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

  maxIterationsText.setString(numberToString<int>(statService->data.maxIterations));
};

void StatsPanel::draw(std::shared_ptr<sf::RenderWindow> target) {
  target->draw(fpsText);
  target->draw(lastGeneretionDurationText);
  target->draw(maxIterationsText);
}

void StatsPanel::setDefaultTextStyle(sf::Text& text) {
  text.setFont(font);
  text.setString("0");
  text.setCharacterSize(14);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Regular);
}
