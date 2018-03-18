#include "common.h"
#include "RandomToggle.h"


RandomToggle::RandomToggle (float f_fps)
  : fps(f_fps)
{}


void RandomToggle::init ()
{
  clear_frame = true;
}


void RandomToggle::nextFrame (bool frameArray[8][8][8])
{

  if (clear_frame) {
    int x, y, z;
    for(z=0; z<8; z++) {
      for(y=0; y<8; y++) {
        for(x=0; x<4; x++) {
          frameArray[x][y][z] = OFF;
        }
      }
    }
    clear_frame = false;
  }

  int randX = rand()%4;
  int randY = rand()%8;
  int randZ = rand()%8;

  frameArray[randX][randY][randZ] = !frameArray[randX][randY][randZ];

}
