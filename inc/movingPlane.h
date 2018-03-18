#ifndef MOVINGPLANE_H
#define MOVINGPLANE_H

typedef struct {    /* container for movingPlane parameters */
  /* public */
  bool init;
  float fps;
  bool rand;
  /* private */
  bool newDir;
  int dir;
  int val;
  bool done;
  bool clear;
} planeStruct;

void movingPlane (planeStruct* es);

#endif
