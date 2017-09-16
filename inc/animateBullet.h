#ifndef ANIMATEBULLET_H
#define ANIMATEBULLET_H

typedef struct {        /* container for animateBullet parameters */
	/* public */
	float fps;			/* need to test which combinations are valid */
	bool trail;
	bool erase;
	bool init;
	bool toggle;
	/* private */
	int pointX;
	int pointY;
	int pointZ;
	int dir;
} bulletStruct;

void animateBullet (bulletStruct* bs);

#endif
