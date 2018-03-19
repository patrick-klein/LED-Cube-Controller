// TODO
// find reasonable timer periods
// sync new frame generation with frame displaying
// high frequency toggling to change brightness
// properly assign variables (const, static, volatile, etc.)

#include "common.h"
#include "Animation.h"
#include "AnimateBullet.h"
#include "EdgeLight.h"
#include "Raindrops.h"
#include "MovingPlane.h"
#include "RandomToggle.h"

/******************************************************************************
* global variables
******************************************************************************/

int Z;
bool FRAME_ARRAY[8][8][8];

/******************************************************************************
* display layer handler
*   --shift layer into array
*   --increment Z
******************************************************************************/
void display_handler (int signum)
{

  pin_low (HEADER, Z_CLK_PIN);        /* drive clock low */
  if (Z<7) {
    pin_low (HEADER, Z_DATA_PIN);     /* shift 0 into register */
    Z++;                              /* increment Z */
  } else {
    pin_high (HEADER, Z_DATA_PIN);    /* shift 1 into register */
    Z = 0;                            /* reset Z to 0 */
  }
  pin_high (HEADER, Z_CLK_PIN);       /* transition clock */

  int x, y;

  /* shift in data across y dim */
  for (y=0; y<8; y++) {               /* cycle across y dim */
    pin_low (HEADER, Y_CLK_PIN);      /* ensure Y_CLK is driven low */
    for (x=0; x<8; x++) {             /* cycle through x dim */
      if (FRAME_ARRAY[x][y][Z]) {      /* load 1's complement onto pins */
        pin_low (HEADER, getPin(x));
      } else {
        pin_high (HEADER, getPin(x));
      }
    }
    pin_high (HEADER, Y_CLK_PIN);     /* transition clock to move data into place */
  }
}


/******************************************************************************
* getPin support function
*    --converts integer into corresponding pin number
*    --TODO: just make this an array
******************************************************************************/
int getPin (const int pin)
{
  switch (pin) {
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
*   TODO: find original source and give credit
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
*   --generates frames according to various animations
*   --sends frame to shift register array
*   --shifts layers to create persistent image
*   --sets animation mode if called with argument,
*     otherwise runs demo looping through different modes
******************************************************************************/
int main (int argc, char** argv)
{

  /* get mode from input */
  int mode;
  bool demo;
  if (argc>1) {
    mode = atoi(argv[1]);
    demo = false;
  } else {
    mode = 0;
    demo = true;
  }

  /* Z is set to account for immediate incrementation */
  Z = 7;

  /* initialize FRAME_ARRAY */
  memset (FRAME_ARRAY, OFF, 512*sizeof(bool));

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
  timerSetup (display_handler, (1/REFRESH_RATE)*1e6 );       /* implicit float->int cast */

  /* set random seed */
  srand(time(NULL));

  /* intialize animation states */
  AnimateBullet bs;
  Raindrops rs;
  EdgeLight es;
  MovingPlane ps;
  RandomToggle rnds;

  /* initialize vector of animation modes */
  std::vector<Animation*> anim_modes = {&bs, &rs, &es, &ps, &rnds};
  int num_modes = anim_modes.size();
  Animation* anim = anim_modes[mode];
  anim->init();
  float framePeriod = 1/anim->fps;

  /* initialize frame clock */
  clock_t refTime = clock();

  /* set demo clock */
  clock_t demoTime = clock();
  float demoPeriod = 60;        /* seconds */

  /* main display loop */
  while (true) {

    /* compare clock to framePeriod */
    if ( ((float)(clock()-refTime)/CLOCKS_PER_SEC) > framePeriod ) {
      refTime = clock();

      /* if demo mode is on, check if demo timer is up */
      if (demo && ((float)(refTime-demoTime)/CLOCKS_PER_SEC) > demoPeriod ) {
        /* increment mode and initialize new animation */
        mode = (mode + 1) % num_modes;
        anim = anim_modes[mode];
        anim->init();
        framePeriod = 1/anim->fps;
        demoTime = clock();
      }

      /* get next frame */
      anim->nextFrame(FRAME_ARRAY);

    }
  }

  /* free io pins */
  iolib_free();

  /* free memory */
  free(FRAME_ARRAY);

  return 0;

}
