#ifndef GENERATELIFE_H
#define GENERATELIFE_H

/* lifeType for initialization */
#define THREE_D 0
#define HISTORY 1

/* threeDLattice */
#define CARDINAL_LATTICE	0
#define CUBE_LATTICE		1
#define PLANAR_LATTICE		2

/* historyLattice */
#define CARDINAL_LATTICE	0
#define CORNER_LATTICE		1
#define SQUARE_LATTICE		2

/* rule */
#define RULE_0 0
#define RULE_1 1

typedef struct {        /* container for generateLife parameters */
	/* public */
  int threeDLattice;
  int historyLattice;
	float td_fps;
	float hist_fps;
  int rule;
  bool init;
	/* private */
	bool oldFrameOne[8][8][8];
	bool oldFrameTwo[8][8][8];
} lifeStruct;

void generateLife3D (lifeStruct* ls);
void generateLifeHistory(lifeStruct* ls);

#endif
