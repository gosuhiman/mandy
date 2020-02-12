#include "Application.hpp"

Application::Application(ApplicationSettings settings) : settings(settings) {
  window = std::make_shared<sf::RenderWindow>(sf::VideoMode(settings.windowWidth, settings.windowHeight), settings.title);
  window->setFramerateLimit(settings.frameLimit);

  canvas = std::make_shared<Canvas>(settings.windowWidth, settings.windowHeight);
  fpsCounter = std::make_shared<FpsCounter>();

  widgets.push_back(canvas);
  widgets.push_back(fpsCounter);
};

void Application::run() {
  for (auto widget : widgets) widget->initialize();

  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window->close();
      }

      if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
        window->setView(sf::View(visibleArea));

        for (auto widget : widgets) {
          widget->onResize(event.size.width, event.size.height);
        }
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          canvas->onClick(event.mouseButton.x, event.mouseButton.y);
        }
      }

      if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Space) {
          canvas->saveScreenshot();
        }
      }

      if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::C) {
          canvas->changeColoringMode();
        }
      }
    }

    window->clear(sf::Color::Black);

    for (auto widget : widgets) {
      widget->update();
      widget->draw(window);
    }

    window->display();
  }
};
