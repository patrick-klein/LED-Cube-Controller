#include "common.h"
#include "movingPlane.h"

/******************************************************************************
 * movingPlane
 *		moves a lit plane across the cube
 ******************************************************************************/
void movingPlane (planeStruct* ps)
{

	int x,y,z;

	/* check if new direction is needed */
	if (ps->newDir) { for(z=0;z<8;z++){for(y=0;y<8;y++){for(x=0;x<4;x++){frameArray[x][y][z]=OFF; }}} }

	/* check if new direction is needed */
	if (ps->clear) {
		for(z=0;z<8;z++){for(y=0;y<8;y++){for(x=0;x<4;x++){frameArray[x][y][z]=OFF;}}}
		ps->clear = FALSE;
		return;
	}

	if (ps->init) {
		ps->newDir = FALSE;
		ps->dir = POS_X;
		ps->val = 0;
		ps->init = FALSE;
		ps->done = FALSE;
		ps->clear = FALSE;
	}

	/* set new direction if flag is set */
	if (ps->newDir) {
		if (ps->rand) {
			int nextDir;
			do { nextDir = rand()%6; } while (nextDir==ps->dir);
			ps->dir=nextDir;
		} else { ps->dir = (ps->dir+1)%6; }
		ps->val = 0;
		ps->newDir = FALSE;
	}

	int val = ps->val;

	switch (ps->dir) {
		case POS_X:			/* expanded for clarity */
			for(z=0;z<8;z++){
				for(y=0;y<8;y++){
					frameArray[val+1][y][z]=ON;
					frameArray[val][y][z]=OFF;
				}
			}
			break;
		case NEG_X:
			for(z=0;z<8;z++){for(y=0;y<8;y++){frameArray[3-(val+1)][y][z]=ON; frameArray[3-val][y][z]=OFF;}}
			break;
		case POS_Y:
            for(z=0;z<8;z++){for(x=0;x<4;x++){frameArray[x][val+1][z]=ON; frameArray[x][val][z]=OFF;}}
			break;
		case NEG_Y:
            for(z=0;z<8;z++){for(x=0;x<4;x++){frameArray[x][7-(val+1)][z]=ON; frameArray[x][7-val][z]=OFF;}}
			break;
		case POS_Z:
            for(y=0;y<8;y++){for(x=0;x<4;x++){frameArray[x][y][val+1]=ON; frameArray[x][y][val]=OFF;}}
			break;
		case NEG_Z:
            for(y=0;y<8;y++){for(x=0;x<4;x++){frameArray[x][y][7-(val+1)]=ON; frameArray[x][y][7-val]=OFF;}}
			break;
	}

	ps->val++;

	/* check if new direction is needed */
	if (ps->val==7 || (ps->val==3 && ps->dir==POS_X) || (ps->val==3 && ps->dir==NEG_X)) {
		ps->newDir = TRUE;
		ps->done = TRUE;
		ps->clear = TRUE;
	}


}
