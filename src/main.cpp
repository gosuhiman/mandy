#include "Application.hpp"

int main()
{
  Application application({ 1024, 768, "mandy", 60 });
  application.run();

  return 0;
}