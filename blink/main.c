#include <mcs51/8051.h>

void delay(unsigned int time) {
  unsigned int i, j;
  for(i = 0; i < time; i++)
    for (j = 0; j < 100; j++);
}

void main() {
  while(1) {
    P0_0 = 0;
    delay(5000);
    P0_0 = 1;
    delay(5000);
  }
}
