/******************************************************************************
* movingPlane
*    moves a lit plane across the cube
******************************************************************************/

#include "common.h"
#include "MovingPlane.h"


MovingPlane::MovingPlane (float f_fps, bool b_rand)
  : fps(f_fps), rand_dir(b_rand)
{}


void MovingPlane::init ()
{
  newDir = false;
  dir = POS_X;
  val = 0;
  done = false;
  clear = false;
}


void MovingPlane::nextFrame (bool frameArray[8][8][8])
{

  int x, y, z;

  /* check if new direction is needed */
  if (newDir) {
    for(z=0; z<8; z++) {
      for(y=0; y<8; y++) {
        for(x=0; x<4; x++) {
          frameArray[x][y][z] = OFF;
        }
      }
    }
  }

  /* check if new direction is needed */
  if (clear) {
    for(z=0; z<8; z++) {
      for(y=0; y<8; y++) {
        for(x=0; x<4; x++) {
          frameArray[x][y][z] = OFF;
        }
      }
    }
    clear = false;
    return;
  }

  /* set new direction if flag is set */
  if (newDir) {
    if (rand_dir) {
      int nextDir;
      do {
        nextDir = rand()%6;
      } while (nextDir == dir);
      dir = nextDir;
    } else {
      dir = (dir+1)%6;
    }
    val = 0;
    newDir = false;
  }

  switch (dir) {
  case POS_X:
    for(z=0; z<8; z++) {
      for(y=0; y<8; y++) {
        frameArray[val][y][z] = ON;
        if(val>0) { frameArray[val-1][y][z] = OFF; }
      }
    }
    break;
  case NEG_X:
    for(z=0; z<8; z++) {
      for(y=0; y<8; y++) {
        frameArray[3-val][y][z] = ON;
        if(val>0) { frameArray[3-(val-1)][y][z] = OFF; }
      }
    }
    break;
  case POS_Y:
    for(z=0; z<8; z++) {
      for(x=0; x<4; x++) {
        frameArray[x][val][z] = ON;
        if(val>0) { frameArray[x][val-1][z] = OFF; }
      }
    }
    break;
  case NEG_Y:
    for(z=0; z<8; z++) {
      for(x=0; x<4; x++) {
        frameArray[x][7-val][z] = ON;
        if(val>0) { frameArray[x][7-(val-1)][z] = OFF; }
      }
    }
    break;
  case POS_Z:
    for(y=0; y<8; y++) {
      for(x=0; x<4; x++) {
        frameArray[x][y][val] = ON;
        if(val>0) { frameArray[x][y][val-1] = OFF; }
      }
    }
    break;
  case NEG_Z:
    for(y=0; y<8; y++) {
      for(x=0; x<4; x++) {
        frameArray[x][y][7-val] = ON;
        if(val>0) { frameArray[x][y][7-(val-1)] = OFF; }
      }
    }
    break;
  }

  val++;

  /* check if new direction is needed */
  if (val == 8 || (val == 4 && dir == POS_X) || (val == 4 && dir == NEG_X)) {
    newDir = true;
    done = true;
    clear = true;
  }


}
