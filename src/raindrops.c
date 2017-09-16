/* CONSIDERATIONS */
// check when done, and reset initialization flag
// error check rule, lattice vals

#include "common.h"
#include "raindrops.h"

void raindrops(rainStruct* rs)
{

	int x, y, z;

	int zLim = (rs->memory) ? 6 : 7;

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
			if (rs->memory){
				if (rand()%100 < rs->chance) { frameArray[x][y][7] = ON; frameArray[x][y][6] = ON; }
				else if (frameArray[x][y][7]==frameArray[x][y][0]) { frameArray[x][y][7] = OFF; }
				else { frameArray[x][y][6] = OFF; }
			} else {
				if (rand()%100 < rs->chance) { frameArray[x][y][7] = ON; }
				else { frameArray[x][y][7] = OFF; }
			}
		}
	}

}
