#ifndef EDGELIGHT_H
#define EDGELIGHT_H

typedef struct {    /* container for edgeLight parameters and flags */
	/* public */
    bool init;
	float fps;
    bool stat;			/* static frames */
	bool cycleMode;		/* following two variables only needed if cycleMode */
		int numCount;
		bool randMode;
	/* private */
    int iVal;
	int iDir;
	int mode;
	int modeCount;
} edgeStruct;

void edgeLight (edgeStruct* es);

#endif
