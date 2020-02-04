#include "Application.hpp"

Application::Application(ApplicationSettings settings) : settings(settings) {
  window = new sf::RenderWindow(sf::VideoMode(settings.windowWidth, settings.windowHeight), settings.title);
  window->setFramerateLimit(settings.frameLimit);

  canvas = new Canvas(settings.windowWidth, settings.windowHeight);
  fpsCounter = new FpsCounter();

  widgets.push_back(canvas);
  widgets.push_back(fpsCounter);
};

void Application::run() {
  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window->close();
      }

      if (event.type == sf::Event::Resized) {
        canvas->resize(event.size.width, event.size.height);
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          canvas->zoomIn(event.mouseButton.x, event.mouseButton.y);
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
