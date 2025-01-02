#include "delay.h"

void delay(unsigned int time) {
  unsigned int i, j;
  for (i = 1; i <= time; i++)
    for (j = 1; j <= 100; j++);
}
