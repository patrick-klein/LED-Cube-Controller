#ifndef EDGELIGHT_H
#define EDGELIGHT_H

#include "Animation.h"

class EdgeLight : public Animation
{
public:
  float fps;
  bool stat;      /* static frames */
  int mode;
  bool cycleMode;   /* following two variables only needed if cycleMode */
  int numCount;
  bool randMode;
  EdgeLight (float f_fps=8, bool b_stat=false, int i_mode=2, bool b_cycleMode=true, int i_numCount=1, bool b_randMode=false);
  void init ();
  void nextFrame (bool frameArray[8][8][8]);
private:
  int iVal;
  int iDir;
  int modeCount;
};

#endif
