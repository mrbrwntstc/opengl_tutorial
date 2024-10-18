#ifndef __TIME_H__
#define __TIME_H__

namespace time
{
  extern float dt;
  extern float current;
  extern float previous;

  extern unsigned int frame_rate;
  extern unsigned int frame_count;
  extern float seconds_per_frame;
  extern float frame_previous;

  void init(float frame_rate);
  void update();
  void update_late();
}

#endif // __TIME_H__