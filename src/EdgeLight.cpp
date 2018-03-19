/******************************************************************************
* edgeLight
*		displays various cube-based shapes
******************************************************************************/

#include "common.h"
#include "EdgeLight.h"


EdgeLight::EdgeLight (float f_fps, bool b_stat, int i_mode, bool b_cycleMode, int i_numCount, bool b_randMode)
  : fps(f_fps), stat(b_stat), mode(i_mode), cycleMode(b_cycleMode), numCount(i_numCount), randMode(b_randMode)
{}


void EdgeLight::init()
{
  iVal = stat ? 3 : 0;
  iDir = POS;
  modeCount = 0;
  mode = stat ? mode : (randMode ? rand()%5 : 0);
}


void EdgeLight::nextFrame (bool frameArray[8][8][8])
{

  int xInd, yInd, zInd;
  bool xEdge, yEdge, zEdge;
  int i, iLoop;

  i = iVal;

  for (xInd=0; xInd<4; xInd++) {
    for (yInd=0; yInd<8; yInd++) {
      for (zInd=0; zInd<8; zInd++) {
        switch (mode) {
        case 0:
          #define CORNER_CUBE(p,i) ( p>=(3-i) && p<=(4+i) && (i==0 || !(p>(4-i) && p<(3+i))) )
          xEdge = CORNER_CUBE(xInd,i);
          yEdge = CORNER_CUBE(yInd,i);
          zEdge = CORNER_CUBE(zInd,i);
          frameArray[xInd][yInd][zInd] = xEdge + yEdge + zEdge == 3;
          break;
        case 1:
          #define PULSE_EDGE(p1,p2,i) ( p1>=(3-i) && p1<=(4+i) && (p2==(3-i) || p2==(4+i)) )
          xEdge = PULSE_EDGE(xInd, yInd, i) && PULSE_EDGE(xInd, zInd, i);
          yEdge = PULSE_EDGE(yInd, xInd, i) && PULSE_EDGE(yInd, zInd, i);
          zEdge = PULSE_EDGE(zInd, xInd, i) && PULSE_EDGE(zInd, yInd, i);
          frameArray[xInd][yInd][zInd] = xEdge || yEdge || zEdge;
          break;
        case 2:
          #define PULSE_CUBE(p,i) ( p>=(3-i) && p<=(4+i) )
          xEdge = PULSE_CUBE(xInd, i);
          yEdge = PULSE_CUBE(yInd, i);
          zEdge = PULSE_CUBE(zInd, i);
          frameArray[xInd][yInd][zInd] = xEdge && yEdge && zEdge;
          break;
        case 3:
          #define NESTED_CUBE(p1,p2,i) ( p1>=(3-(i)) && p1<=(4+(i)) && p2>=(3-(i)) && p2<=(4+(i)) )
          xEdge = NESTED_CUBE(xInd, yInd, i) && !NESTED_CUBE(xInd, yInd, i-1);
          yEdge = NESTED_CUBE(yInd, zInd, i) && !NESTED_CUBE(yInd, zInd, i-1);
          zEdge = NESTED_CUBE(zInd, xInd, i) && !NESTED_CUBE(zInd, xInd, i-1);
          frameArray[xInd][yInd][zInd] = xEdge + yEdge + zEdge > 1;
          break;
        case 4:
          #define HYPERCUBE_EDGE(p1,p2,p3) ( ((p1==7)||(p1==0))+((p2==7)||(p2==0))+((p3==7)||(p3==0))>1 )
          if (i==3 && HYPERCUBE_EDGE(xInd,yInd,zInd)) {
            frameArray[xInd][yInd][zInd] = ON;
          } else {
            frameArray[xInd][yInd][zInd] = OFF;
            #define HYPERCUBE_DIAG(p,i) ( p==(3-i) || p==(4+i) )
            for (iLoop=0; iLoop<=i; iLoop++) {
              xEdge = HYPERCUBE_DIAG(xInd, iLoop);
              yEdge = HYPERCUBE_DIAG(yInd, iLoop);
              zEdge = HYPERCUBE_DIAG(zInd, iLoop);
              if (xEdge && yEdge && zEdge) {
                frameArray[xInd][yInd][zInd] = ON;
                break;
              }
            }
          }
          break;
        }
      }
    }
  }

  if (!stat) {
    if ( iVal==3 && iDir==POS) { iDir=NEG; }
    else if (iVal==0 && iDir==NEG) {
      iDir = POS;
      /* new mode condition */
      if (++modeCount == numCount && !stat ) {
        modeCount = 0;
        if (randMode) {
          int newMode;
          do {
            newMode = rand()%5; /* consider tracking already used modes if repeat modes a problem */
          } while (newMode == mode);
          mode = newMode;
        } else {
          mode = (mode+1)%5;
        }
      }
    }
    else if (iDir==POS) { iVal++; }
    else if (iDir==NEG) { iVal--; }
  }

}
