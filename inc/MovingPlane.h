#ifndef MOVINGPLANE_H
#define MOVINGPLANE_H

#include "Animation.h"

class MovingPlane : public Animation
{
public:
  float fps;
  bool rand_dir;
  MovingPlane (float f_fps=1, bool b_rand=true);
  void init ();
  void nextFrame (bool frameArray[8][8][8]);
private:
  bool newDir;
  int dir;
  int val;
  bool done;
  bool clear;
};

#endif
