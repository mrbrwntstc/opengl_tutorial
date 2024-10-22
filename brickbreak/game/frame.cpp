#include "../game.h"
#include "../time.h"


namespace game
{
namespace frame
{
  void start()
  {
    time::update();
  } 

  void end()
  {
    time::update_late();
  }
}
}
