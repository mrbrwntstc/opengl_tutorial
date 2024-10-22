#include "game.h"

#include <Windows.h>

int main()
{
  game::init();

  while(!render::window::should_close())
  {
    game::frame::start();

    game::update();
    
    game::render();

    game::frame::end();
  }

  // cleanup
  game::cleanup();

  return 0;
}
