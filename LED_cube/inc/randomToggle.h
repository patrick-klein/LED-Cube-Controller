#ifndef RANDOMTOGGLE_H
#define RANDOMTOGGLE_H

typedef struct {        /* container for animateBullet parameters */
	float fps;
	bool clear;
} randomStruct;

void randomToggle (randomStruct* rnds);

#endif
