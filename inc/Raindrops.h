#ifndef RAINDROPS_H
#define RAINDROPS_H

#include "Animation.h"

class Raindrops : public Animation
{
public:
  float fps;
  int chance;   // must be int from 0-100;
  bool memory;
  Raindrops (float f_fps=12, int i_chance = (int) (100/64*4), bool b_memory=false);
  void init ();
  void nextFrame (bool frameArray[8][8][8]);
};

#endif
