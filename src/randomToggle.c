#include "common.h"
#include "randomToggle.h"

/******************************************************************************
 * randomToggle
 *		toggles random voxel each frame
 ******************************************************************************/
void randomToggle (randomStruct* rnds)
{

	if (rnds->clear) {
		int x,y,z;
		for(z=0;z<8;z++){
      for(y=0;y<8;y++){
        for(x=0;x<4;x++){
          frameArray[x][y][z]=OFF;
        }
      }
    }
		rnds->clear = FALSE;
	}

	int randX = rand()%4;
	int randY = rand()%8;
	int randZ = rand()%8;

	frameArray[randX][randY][randZ] = !frameArray[randX][randY][randZ];

}
