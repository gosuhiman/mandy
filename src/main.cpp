#include <SFML/Graphics.hpp>
#include "Application.hpp"

int main()
{
  Application application({ 1024, 768, "mandy", 200 });
  application.run();

  return 0;
}