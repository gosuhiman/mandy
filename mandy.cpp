#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  unsigned width = 800;
  unsigned height = 600;

  sf::RenderWindow window(sf::VideoMode(width, height), "mandy");
  window.setFramerateLimit(200);

  sf::Clock clock;

  sf::Texture texture;
  if (!texture.create(width, height))
    return -1;

  sf::Uint8* pixels = new sf::Uint8[800 * 600 * 4];

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      pixels[(x + y * width) * 4] = 255;
      pixels[(x + y * width) * 4 + 1] = 0;
      pixels[(x + y * width) * 4 + 2] = 255;
      pixels[(x + y * width) * 4 + 3] = 255;
    }
  }

  texture.update(pixels);
  sf::Sprite sprite;
  sprite.setTexture(texture);

  int i = 1;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    sf::Time time = clock.getElapsedTime();
    std::cout << 1.0f / time.asSeconds() << std::endl;
    clock.restart();

    window.clear(sf::Color::Green);

    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        pixels[(x + y * width) * 4] = i;
      }
    }

    texture.update(pixels);

    window.draw(sprite);

    window.display();
    i++;
    if (i > 255) i = 1;
  }

  return 0;
}