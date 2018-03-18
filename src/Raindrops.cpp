/* CONSIDERATIONS */
// check when done, and reset initialization flag
// error check rule, lattice vals

#include "common.h"
#include "Raindrops.h"


Raindrops::Raindrops (float f_fps, int i_chance, bool b_memory)
  : chance(i_chance), memory(b_memory), fps(f_fps)
{}

void Raindrops::init ()
{}


void Raindrops::nextFrame (bool frameArray[8][8][8])
{

  int x, y, z;
  int zLim = (memory) ? 6 : 7;

  /* shift array down (negative z direction) */
  for (z=0; z<zLim; z++) {
    for (y=0; y<8; y++) {
      for (x=0; x<8; x++) {
        frameArray[x][y][z] = frameArray[x][y][z+1];
      }
    }
  }

  /* set new top layer */
  for (y=0; y<8; y++) {
    for (x=0; x<8; x++) {
      if (memory) {
        if (rand()%100 < chance) {
          frameArray[x][y][7] = ON;
          frameArray[x][y][6] = ON;
        } else if (frameArray[x][y][7]==frameArray[x][y][0]) {
          frameArray[x][y][7] = OFF;
        } else {
          frameArray[x][y][6] = OFF;
        }

      } else {
        if (rand()%100 < chance) {
          frameArray[x][y][7] = ON;
        } else {
          frameArray[x][y][7] = OFF;
        }
      }
    }
  }

}
