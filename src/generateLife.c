/* CONSIDERATIONS */
// check when done, and reset initialization flag
// error check rule, lattice vals

#include "common.h"
#include "generateLife.h"

void lifeInitialize (lifeStruct* ls, int lifeType)
{
	int x, y, z, randVal;
	int zLim = (lifeType==THREE_D) ? 4 : 1;
	int xyLim = (lifeType==THREE_D) ? 4 : 8;
	for (z=0;z<zLim;z++) {
    for (y=0;y<xyLim;y++) {
      for (x=0;x<xyLim;x++) {
        randVal = rand()%10>7;
        frameArray[x][y][7-z] = randVal;
        if (lifeType==THREE_D) {
          frameArray[7-x][y][z] = randVal;
					frameArray[x][7-y][z] = randVal;
					frameArray[x][y][z] = randVal;
					frameArray[7-x][7-y][z] = randVal;
					frameArray[7-x][y][7-z] = randVal;
					frameArray[x][7-y][7-z] = randVal;
					frameArray[7-x][7-y][7-z] = randVal;
        }
      }
    }
  }
  ls->init = FALSE;
}

void generateLife3D (lifeStruct* ls)
{
  int front, back, left, right, top, bottom;
	int frontPixel, backPixel, leftPixel, rightPixel, topPixel, bottomPixel;
	int topFrontPixel, topBackPixel, topLeftPixel, topRightPixel;
	int bottomFrontPixel, bottomBackPixel, bottomLeftPixel, bottomRightPixel;
  int frontRightPixel, frontLeftPixel, backLeftPixel, backRightPixel;
	int topFrontRightPixel, topFrontLeftPixel, topBackLeftPixel, topBackRightPixel;
	int bottomFrontRightPixel, bottomFrontLeftPixel, bottomBackLeftPixel, bottomBackRightPixel;
	int cardinalLattice, topLattice, bottomLattice, middleLattice, topCornerLattice, bottomCornerLattice;;

  int b[2];
  int s[2];

	char tempArray[8][8][8];

  int n = 0;
  int x, y, z;

	if (ls->init) { lifeInitialize (ls, THREE_D); }

    // Loop through each element
    for (z = 0; z<8; z++) {
        for (y = 0; y<8; y++) {
            for (x = 0; x<8; x++) {

                switch (x) {
                  case 0:
                    front = x+1;
                    back  = 7;
                    break;
                  case 7:
                    front = 0;
                    back  = x-1;
                    break;
                  default:
                    front = x+1;
                    back  = x-1;
                    break;
                }

                switch (y) {
                  case 0:
                    left  = 7;
                    right = y+1;
                    break;
                  case 7:
                    left  = y-1;
                    right = 0;
          					break;
                  default:
                    left  = y-1;
                    right = y+1;
                    break;
                }

                switch (z) {
                  case 0:
                    top    = z+1;
                    bottom = 7;
                    break;
                  case 7:
                    top    = 0;
                    bottom = z-1;
        						break;
                  default:
                    top    = z+1;
                    bottom = z-1;
                    break;
                }

                frontPixel  = frameArray[front][y][z];
                backPixel   = frameArray[back][y][z];
                leftPixel   = frameArray[x][left][z];
                rightPixel  = frameArray[x][right][z];
                topPixel    = frameArray[x][y][top];
                bottomPixel = frameArray[x][y][bottom];

                topFrontPixel = frameArray[front][y][top];
                topBackPixel  = frameArray[back][y][top];
                topLeftPixel  = frameArray[x][left][top];
                topRightPixel = frameArray[x][right][top];

                bottomFrontPixel = frameArray[front][y][bottom];
                bottomBackPixel  = frameArray[back][y][bottom];
                bottomLeftPixel  = frameArray[x][left][bottom];
                bottomRightPixel = frameArray[x][right][bottom];

                frontRightPixel = frameArray[front][right][z];
                frontLeftPixel  = frameArray[front][left][z];
                backLeftPixel   = frameArray[back][left][z];
                backRightPixel  = frameArray[back][right][z];

                topFrontRightPixel = frameArray[front][right][top];
                topFrontLeftPixel  = frameArray[front][left][top];
                topBackLeftPixel   = frameArray[back][left][top];
                topBackRightPixel  = frameArray[back][right][top];

                bottomFrontRightPixel	= frameArray[front][right][bottom];
                bottomFrontLeftPixel	= frameArray[front][left][bottom];
                bottomBackLeftPixel		= frameArray[back][left][bottom];
                bottomBackRightPixel	= frameArray[back][right][bottom];

                cardinalLattice = frontPixel + backPixel + leftPixel + rightPixel + topPixel + bottomPixel;

                topLattice = topFrontPixel + topBackPixel + topLeftPixel + topRightPixel;
                bottomLattice = bottomFrontPixel + bottomBackPixel + bottomLeftPixel + bottomRightPixel;
                middleLattice = frontRightPixel + frontLeftPixel + backLeftPixel + backRightPixel;
                topCornerLattice = topFrontRightPixel + topFrontLeftPixel + topBackLeftPixel + topBackRightPixel;
                bottomCornerLattice = bottomFrontRightPixel + bottomFrontLeftPixel + bottomBackLeftPixel + bottomBackRightPixel;

                switch (ls->threeDLattice) {
                  case CUBE_LATTICE: // cubeLattice
                    n = cardinalLattice + topLattice + bottomLattice + middleLattice + topCornerLattice + bottomCornerLattice;
                    break;
                  case CARDINAL_LATTICE: // cardinalLattice
                    n = cardinalLattice;// + topLattice + bottomLattice + middleLattice;
                    break;
                  case PLANAR_LATTICE: // planarLattice
                    n = middleLattice + frontPixel + backPixel + leftPixel + rightPixel;
                    break;
                }

                switch (ls->rule) {
                  case RULE_0:
                    b[0] = 3;
                    b[1] = 3;
                    s[0] = 2;
                    s[1] = 3;
                    break;
                  case RULE_1:
                    b[0] = 3;
                    b[1] = 6;
                    s[0] = 2;
                    s[1] = 3;
                    break;
                }

                switch (frameArray[x][y][z]) {
                  case OFF: // born
                    if (n==b[0] || n==b[1]) { tempArray[x][y][z] = ON; }
						        else { tempArray[x][y][z] = OFF; }
                    break;
                  case ON: // survive
                    if ( n==s[0] || n==s[1] ) { tempArray[x][y][z] = ON; }
			              else { tempArray[x][y][z] = OFF; }
                    break;
                  }


            }
        }
    }

  /* check if life is stale */
  int sum=0, dif1=0, dif2=0;
	bool end;
	for (z=0; z<8; z++) {
    for (y=0; y<8; y++) {
      for (x=0; x<8; x++) {
        sum += frameArray[x][y][0];
        dif1 += ls->oldFrameOne[x][y][z]-frameArray[x][y][z];
        dif2 += ls->oldFrameTwo[x][y][z]-frameArray[x][y][z];
        if (sum | dif1 | dif2) { end = TRUE; break; }
      }
      if (end) { break; }
    }
    if (end) { break; }
  }
  /* re-initilize if empty */
  if (!sum || !dif1 ||  !dif2) { ls->init = TRUE; }

	/* replace frame with tempArray -- consider just assigning address */
	for (z=0;z<8;z++){
		for (y=0;y<8;y++){
			for (x=0;x<8;x++){
        frameArray[x][y][z] = tempArray[x][y][z];
				ls->oldFrameOne[x][y][z] = frameArray[x][y][z];
				ls->oldFrameTwo[x][y][z] = ls->oldFrameOne[x][y][z];
			}
		}
	}

}



void generateLifeHistory(lifeStruct* ls)
{

	int left, right, top, bottom;
	int topPixel, bottomPixel, leftPixel, rightPixel;
	int topLeftPixel, topRightPixel, bottomLeftPixel, bottomRightPixel;
	int cardinalLattice, cornerLattice, squareLattice;

	int n;		// neighbors
  int b[2];	// born rule
  int s[2];	// survive rule

	char tempZArray[8][8];

	int x, y, z;

	/* check if life is stale */
	int sum=0, dif1=0, dif2=0;
	for (y=0; y<8; y++) {
		for (x=0; x<8; x++) {
			sum += frameArray[x][y][0];
			dif1 += frameArray[x][y][7]-frameArray[x][y][0];
			dif2 += frameArray[x][y][6]-frameArray[x][y][0];
		}
	}
	/* re-initilize if empty */
	if (sum==0 || dif1==0 || dif2==0) { ls->init = TRUE; };

	/* initialize if flag is set */
  if (ls->init) { lifeInitialize (ls, HISTORY); }

  for (x=0; x<8; x++) {
    for (y=0; y<8; y++) {

      switch (x) {
        case 0:
          left = 7;
          right = x+1;
          break;
        case 7:
          left = x-1;
          right = 0;
          break;
        default:
          left = x-1;
          right = x+1;
          break;
        }

        switch (y) {
          case 0:
          top = y+1;
          bottom = 7;
          break;
        case 7:
          top = 0;
          bottom = y-1;
          break;
        default:
          top = y+1;
          bottom = y-1;
          break;
        }

        topPixel    = frameArray[x][top][7];
        bottomPixel = frameArray[x][bottom][7];
        leftPixel   = frameArray[left][y][7];
        rightPixel  = frameArray[right][y][7];

        topLeftPixel     = frameArray[left][top][7];
        topRightPixel    = frameArray[right][top][7];
        bottomLeftPixel  = frameArray[left][bottom][7];
        bottomRightPixel = frameArray[right][bottom][7];

        cardinalLattice     = topPixel+bottomPixel+rightPixel+leftPixel;
        cornerLattice       = bottomRightPixel+bottomLeftPixel+topLeftPixel+topRightPixel;
        squareLattice       = cardinalLattice+cornerLattice;

        switch (ls->historyLattice) {
          case CARDINAL_LATTICE:
            n = cardinalLattice;
            break;
          case CORNER_LATTICE:
  					n = cornerLattice;
  					break;
  				case SQUARE_LATTICE:
  					n = squareLattice;
  					break;
          }

          switch (ls->rule) {
            case RULE_0:
              b[0] = 3;
              b[1] = 3;
              s[0] = 2;
              s[1] = 3;
              break;
            case RULE_1:
              b[0] = 3;
              b[1] = 6;
              s[0] = 2;
              s[1] = 3;
              break;
            }


            switch (frameArray[x][y][7]) {
              case 0: // Born
                if (n==b[0] || n==b[1]) { tempZArray[x][y] = 1; }
                else { tempZArray[x][y] = 0; }
                break;
              case 1: // Stays alive
                if (n==s[0] || n==s[1]) { tempZArray[x][y] = 1; }
                else { tempZArray[x][y] = 0; }
              default:
                break;
            }

        }
    }

	/* shift array down (negative z direction) */
  for (z=0; z<7; z++) {
    for (y=0; y<8; y++) {
      for (x=0; x<8; x++) {
        frameArray[x][y][z] = frameArray[x][y][z+1];
      }
    }
  }

	/* set new top layer */
  for (y=0; y<8; y++) {
    for (x=0; x<8; x++) {
      frameArray[x][y][7] = tempZArray[x][y];
    }
  }

}
