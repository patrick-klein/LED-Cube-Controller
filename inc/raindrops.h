#ifndef RAINDROPS_H
#define RAINDROPS_H

typedef struct {  /* container for raindrops parameters */
  int chance;   // must be int from 0-100;
  bool memory;
  float fps;
} rainStruct;

void raindrops (rainStruct* rs);

#endif
