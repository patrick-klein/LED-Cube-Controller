#ifndef ANIMATEBULLET_H
#define ANIMATEBULLET_H

#include "Animation.h"

class AnimateBullet : public Animation
{
public:
  float fps;
  bool trail;
  bool erase;
  bool toggle;
  AnimateBullet (float f_fps=16, bool b_trail=true, bool b_erase=false, bool b_toggle=true);
  void init ();
  void nextFrame (bool frameArray[8][8][8]);
private:
  int pointX;
  int pointY;
  int pointZ;
  int dir;
  bool clear_frame;
};

#endif
