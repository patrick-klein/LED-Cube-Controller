#include "common.h"
#include "animateBullet.h"

/******************************************************************************
* animateBullet
*		shoots a single lit voxel in random directions
******************************************************************************/
void animateBullet (bulletStruct* bs)
{

  if (bs->init) {               /* initialize if bs.init set */
    bs->pointX = rand()%4;
    bs->pointY = rand()%8;
    bs->pointZ = rand()%8;
    bs->dir = rand()%6;
    int x,y,z;
    for(z=0; z<8; z++) {
      for(y=0; y<8; y++) {
        for(x=0; x<4; x++) {
          frameArray[x][y][z]=bs->erase;
        }
      }
    }
    bs->init = FALSE;
  } else {                  /* 1/8 chance of randomly changing direction */
    if (!(rand()%3)) {
      bs->dir = rand()%6;
    }
  }

  /* randomly change direction if at boundary, repeat until valid dir is found */
  bool err;
  do {
    err = FALSE;
    if ( (bs->dir==POS_X)&&(bs->pointX>=3) ) { err = TRUE; }
    if ( (bs->dir==NEG_X)&&(bs->pointX<=0) ) { err = TRUE; }
    if ( (bs->dir==POS_Y)&&(bs->pointY>=7) ) { err = TRUE; }
    if ( (bs->dir==NEG_Y)&&(bs->pointY<=0) ) { err = TRUE; }
    if ( (bs->dir==POS_Z)&&(bs->pointZ>=7) ) { err = TRUE; }
    if ( (bs->dir==NEG_Z)&&(bs->pointZ<=0) ) { err = TRUE; }
    if (err) { bs->dir = rand()%6; }
  } while (err);

  /* set voxel point to 0 */
  if (!bs->trail) {
    frameArray[bs->pointX][bs->pointY][bs->pointZ] = OFF;
  }

  /* set new voxel based on dir */
  switch (bs->dir) {
  case POS_X: (bs->pointX)++; break;
  case NEG_X: (bs->pointX)--; break;
  case POS_Y: (bs->pointY)++; break;
  case NEG_Y: (bs->pointY)--; break;
  case POS_Z: (bs->pointZ)++; break;
  case NEG_Z: (bs->pointZ)--; break;
  }

  if (bs->toggle) {
    frameArray[bs->pointX][bs->pointY][bs->pointZ] = !frameArray[bs->pointX][bs->pointY][bs->pointZ];
  } else {
    frameArray[bs->pointX][bs->pointY][bs->pointZ] = ON;
  }

}
