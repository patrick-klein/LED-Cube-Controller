#ifndef COMMON_H
#define COMMON_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <vector>

#include <iolib.h>

/******************************************************************************
* macro definitions
******************************************************************************/

#define REFRESH_RATE 288.0
#define FPS 12.0

#define POS_X 0
#define NEG_X 1
#define POS_Y 2
#define NEG_Y 3
#define POS_Z 4
#define NEG_Z 5

#define POS 0
#define NEG 1

/* find good pins */
#define HEADER        8       /* might possibly need both headers */
#define X_DATA_PIN_0  14
#define X_DATA_PIN_1  15
#define X_DATA_PIN_2  16
#define X_DATA_PIN_3  17
#define X_DATA_PIN_4  18
#define X_DATA_PIN_5  19

#define X_DATA_PIN_6  20
#define X_DATA_PIN_7  20

#define Y_CLK_PIN     11
#define Z_CLK_PIN     12
#define Z_DATA_PIN    13

// pwr 5,6

/* known good */
//	11
//	12
//	13
//	14
//	15
//	16
//	17
//	18
//	19
//

#define ON  1
#define OFF 0

/******************************************************************************
* global variables
******************************************************************************/



/******************************************************************************
* function declarations
******************************************************************************/

void display_handler (int signum);
void timerSetup (void (*fcn_pntr)(int), int period);
int getPin (int);

#endif
