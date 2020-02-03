#include <SFML/Graphics.hpp>
#include "Canvas.hpp"
#include "FpsCounter.hpp"

int main()
{
  unsigned int width = 800;
  unsigned int height = 600;

  sf::RenderWindow window(sf::VideoMode(width, height), "mandy");
  window.setFramerateLimit(200);

  Canvas canvas(width, height);
  FpsCounter fpsCounter;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Black);

    canvas.update();
    fpsCounter.update();

    window.draw(canvas.getSprite());
    window.draw(fpsCounter.getText());
    window.display();
  }

  return 0;
}