/******************************************************************************
* animateBullet
*		shoots a single lit voxel in random directions
******************************************************************************/

#include "common.h"
#include "AnimateBullet.h"


AnimateBullet::AnimateBullet (float f_fps, bool b_trail, bool b_erase, bool b_toggle)
  : fps(f_fps), trail(b_trail), erase(b_erase), toggle(b_toggle)
{}


void AnimateBullet::init ()
{
  pointX = rand()%4;
  pointY = rand()%8;
  pointZ = rand()%8;
  dir = rand()%6;
  clear_frame = true;
}


void AnimateBullet::nextFrame (bool frameArray[8][8][8])
{

  if (clear_frame) {
    int x, y, z;
      for(z=0; z<8; z++) {
        for(y=0; y<8; y++) {
          for(x=0; x<4; x++) {
            frameArray[x][y][z] = erase;
          }
        }
      }
      clear_frame = false;
    }

  /* 1/8 chance of randomly changing direction */
  if (!(rand()%3)) {
    dir = rand()%6;
  }

  /* randomly change direction if at boundary, repeat until valid dir is found */
  bool err;
  do {
    err = false;
    if ( (dir==POS_X)&&(pointX>=3) ) { err = true; }
    if ( (dir==NEG_X)&&(pointX<=0) ) { err = true; }
    if ( (dir==POS_Y)&&(pointY>=7) ) { err = true; }
    if ( (dir==NEG_Y)&&(pointY<=0) ) { err = true; }
    if ( (dir==POS_Z)&&(pointZ>=7) ) { err = true; }
    if ( (dir==NEG_Z)&&(pointZ<=0) ) { err = true; }
    if (err) { dir = rand()%6; }
  } while (err);

  /* set voxel point to 0 */
  if (!trail) {
    frameArray[pointX][pointY][pointZ] = OFF;
  }

  /* set new voxel based on dir */
  switch (dir) {
  case POS_X: (pointX)++; break;
  case NEG_X: (pointX)--; break;
  case POS_Y: (pointY)++; break;
  case NEG_Y: (pointY)--; break;
  case POS_Z: (pointZ)++; break;
  case NEG_Z: (pointZ)--; break;
  }

  if (toggle) {
    frameArray[pointX][pointY][pointZ] = !frameArray[pointX][pointY][pointZ];
  } else {
    frameArray[pointX][pointY][pointZ] = ON;
  }

}
