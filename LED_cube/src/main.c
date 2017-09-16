// CONSIDERATIONS
//
// set timer to ITIMER_REAL rather than ITIMER_VIRTUAL
// rewrite in c++ to learn more about classes/objects/methods
// find reasonable timer periods
// pipeline new frame generation with frame displaying (with "vsync")
// high frequency toggling to change brightness


#include "common.h"
#include "animateBullet.h"
#include "edgeLight.h"
#include "generateLife.h"
#include "raindrops.h"
#include "movingPlane.h"
#include "randomToggle.h"

/******************************************************************************
 * global variables
 ******************************************************************************/

int z;
bool frameArray[8][8][8];

/******************************************************************************
 * display layer handler
 *		increment z
 * 		displays layer
 ******************************************************************************/
void display_handler (int signum)
{

	pin_low (HEADER, Z_CLK_PIN);			/* drive clock low */
	if (z<7) {
		pin_low (HEADER, Z_DATA_PIN);			/* shift 0 into register */
		z++;									/* increment z */
	} else {
		pin_high (HEADER, Z_DATA_PIN);			/* shift 1 into register */
		z = 0;									/* reset z to 0 */
	}
	pin_high (HEADER, Z_CLK_PIN);			/* transition clock */

	int x, y;

   	/* shift in data across y dim */
   	for (y=0;y<8;y++) {				/* cycle across y dim */
       	pin_low (HEADER, Y_CLK_PIN);			/* ensure Y_CLK is driven low */
       	for (x=0;x<8;x++) {					/* cycle through x dim */
       		if (frameArray[x][y][z]) {				/* load 1's complement onto pins */
       			pin_low (HEADER, getPin(x));
       		} else {
       			pin_high (HEADER, getPin(x));
       		}
		}
       	pin_high (HEADER, Y_CLK_PIN);		/* transition clock to move data into place */
	}
}


/******************************************************************************
 * getPin support function
 *		converts integer into corresponding pin number
 *		may want to consider just using an array instead
 ******************************************************************************/
int getPin (const int pin)
{
 		switch (pin){
 			case 0: return X_DATA_PIN_0;
 			case 1: return X_DATA_PIN_1;
 			case 2: return X_DATA_PIN_2;
 			case 3: return X_DATA_PIN_3;
 			case 4: return X_DATA_PIN_4;
 			case 5: return X_DATA_PIN_5;
 			case 6: return X_DATA_PIN_6;
 			case 7: return X_DATA_PIN_7;
 		}
 		/* should never be reached -- error code */
 		return -1;
}


/******************************************************************************
 * timerSetup
 ******************************************************************************/

void timerSetup (void (*fcn_pntr)(int), const int period)
{

	struct sigaction sa;
	struct itimerval timer;

	/* Install *fcn_pntr as the signal handler for SIGVTALRM.  */
    memset (&sa, 0, sizeof (sa));
    sa.sa_handler = fcn_pntr;
    sigaction (SIGALRM, &sa, NULL);
    /* Configure the timer to expire after period...  */
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = period;
    /* ... and every period after that.  */
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = period;
    /* Start a virtual timer. It counts down whenever this process is executing.*/
    setitimer (ITIMER_REAL, &timer, NULL);
}


/******************************************************************************
 * main
 ******************************************************************************/
void main (int argc, char** argv)
{

	/* get mode from input */
	int mode;
	bool demo;
	if (argc>1) {
		mode = atoi(argv[1]);
		demo = FALSE;
	} else {
		mode = 0;
		demo = TRUE;
	}

	/* probably not necessary */
	float fps = FPS;

	/* declare variables */
	z = 7;						/* z is set to account for immediate incrementation */

    /* initialize frameArray */
    memset (frameArray, OFF, 512*sizeof(bool));

	/* initialize library */
	iolib_init();
	/* set pin directions */
	iolib_setdir(HEADER, X_DATA_PIN_0, DIR_OUT);
	iolib_setdir(HEADER, X_DATA_PIN_1, DIR_OUT);
	iolib_setdir(HEADER, X_DATA_PIN_2, DIR_OUT);
	iolib_setdir(HEADER, X_DATA_PIN_3, DIR_OUT);
	iolib_setdir(HEADER, X_DATA_PIN_4, DIR_OUT);
	iolib_setdir(HEADER, X_DATA_PIN_5, DIR_OUT);
	iolib_setdir(HEADER, X_DATA_PIN_6, DIR_OUT);
	iolib_setdir(HEADER, X_DATA_PIN_7, DIR_OUT);
	iolib_setdir(HEADER, Y_CLK_PIN, DIR_OUT);
	iolib_setdir(HEADER, Z_CLK_PIN, DIR_OUT);
	iolib_setdir(HEADER, Z_DATA_PIN, DIR_OUT);

	/* initialize timers */
	timerSetup (display_handler, (1/REFRESH_RATE)*1e6 );	/* implicit float->int cast */

	/* set random seed */
	srand(time(NULL));

	/* create struct for animateBullet */
	bulletStruct bs;
	bs.fps = 16;
	bs.trail = TRUE;
	bs.erase = FALSE;
	bs.toggle = TRUE;
	bs.init = TRUE;

	/* create struct for generateLife */
	lifeStruct ls;
	ls.td_fps =6;
	ls.hist_fps = 12;
	ls.init = TRUE;
	ls.rule = RULE_1;						/* 0, 1 */
	ls.threeDLattice = CUBE_LATTICE;	/* cube, cardinal, planar */
	ls.historyLattice = SQUARE_LATTICE;		/* cardinal, corner, square */

	/* create struct for raindrops */
	rainStruct rs;
	rs.fps = 12;
	rs.chance = (int) (100/64*2);
	rs.memory = FALSE;

    /* create struct for edgeLight */
    edgeStruct es;
	es.fps = 8;
	es.stat = FALSE;		/* incompatible with cycleMode? */
	es.init = TRUE;
    es.cycleMode = TRUE;     /* following two variables only needed if cycleMode */
    es.numCount = 1;
    es.randMode = FALSE;

    /* create struct for movingPlanes */
    planeStruct ps;
	ps.fps = 8;
    ps.init = TRUE;
	ps.rand = TRUE;

    /* create struct for randomToggle */
    randomStruct rnds;
	rnds.fps = 16;
    rnds.clear = FALSE;

	/* initialize frame clock */
	clock_t refTime = clock();
	float framePeriod = 1/FPS;

	/* set demo clock */
	clock_t demoTime = clock();
	float demoPeriod = 15;		/* seconds */

	/* clear clean flag */
	bool clean = FALSE;

    /* main display loop */
    while (TRUE) {
		if ( ((float)(clock()-refTime)/CLOCKS_PER_SEC) > framePeriod ) {

			refTime = clock();

			/* if demo mode is on, check if demo timer is up */
			if (demo) {
				if ( ((float)(refTime-demoTime)/CLOCKS_PER_SEC) > demoPeriod ) {
					if (mode==2||mode==3||mode==4||mode==5) {
						//clean = TRUE;
						//ps.init = TRUE;
						//framePeriod = 1/ps.fps;
					}
					mode = (mode+1)%6;
					ls.init = bs.init = es.init = ps.init = TRUE;	/* wow, it actually works */
					demoTime = clock();
				}
			}

			/* 'wipe' frame clean before new animation */
			if (clean) {
				movingPlane (&ps);
				if (ps.done) { clean=FALSE; }
			} else {
				/* generate new frame -- choose one based on mode (if input) */
				switch (mode) {
					case 0:
						framePeriod = 1/bs.fps;
						animateBullet (&bs);
						break;
					case 1:
						framePeriod = 1/rnds.fps;
						randomToggle (&rnds);
						break;
					case 2:
                	    framePeriod = 1/ls.hist_fps;
						generateLifeHistory (&ls);
						break;
					case 3:
            	        framePeriod = 1/rs.fps;
						raindrops (&rs);
						break;
					case 4:
                	    framePeriod = 1/ls.td_fps;
						generateLife3D (&ls);
						break;
					case 5:
                    	framePeriod = 1/es.fps;
						edgeLight (&es);
						break;
				}
			}
		}
    }

    /* free io pins */
    iolib_free ();

    /* free memory */
    free (frameArray);

}

