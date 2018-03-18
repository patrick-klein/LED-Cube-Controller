#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
public:
  float fps;
  virtual void init () = 0;
  virtual void nextFrame (bool frameArray[8][8][8]) = 0;
};

#endif
