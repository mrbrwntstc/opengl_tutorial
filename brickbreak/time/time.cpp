#include "../time.h"
#include <GLFW/glfw3.h>
#include <Windows.h>

namespace time
{
  float dt = 0.f;
  float current = 0.f;
  float previous = 0.f;

  unsigned int frame_rate = 0;
  unsigned int frame_count = 0;
  float seconds_per_frame = 0.f;
  float frame_previous = 0.f;
}

namespace time
{
  void init(float frame_rate)
  {
    time::frame_rate = frame_rate;
    time::seconds_per_frame = 1.f / time::frame_rate;
  }

  void update()
  {
    time::current = glfwGetTime();
    time::dt = time::current - time::previous;
    time::previous = time::current;
    time:frame_count += 1;

    if(time::current - time::frame_previous >= 1.f)
    {
      time::frame_rate = frame_count;
      time::frame_count = 0;
      time::frame_previous = time::current;
    }
  }

  void update_late()
  {
    float frame_time = glfwGetTime() - time::current;
    if(time::seconds_per_frame > frame_time)
      Sleep((time::seconds_per_frame - frame_time) * 1000);
  }
}
