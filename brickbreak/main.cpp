#include "render.h"
#include "input.h"
#include "time.h"
#include "game.h"

#include <Windows.h>

static const unsigned int width_window = 800;
static const unsigned int height_window = 600;

int main()
{
  render::init(width_window, height_window, "brickbreak", width_window, height_window);
  input::init();
  time::init(60);

  game::init();

  while(!render::window::should_close())
  {
    game::frame::start();

    game::process_input();
    
    game::render();

    game::frame::end();
  }

  // cleanup
  game::cleanup();

  return 0;
}
