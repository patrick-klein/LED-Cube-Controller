#ifndef RANDOMTOGGLE_H
#define RANDOMTOGGLE_H

#include "Animation.h"

class RandomToggle : public Animation
{
public:
  float fps;
  bool clear_frame;
  RandomToggle (float f_fps=16);
  void init ();
  void nextFrame (bool frameArray[8][8][8]);
};

#endif
