#include <mcs51/8051.h>

void delay(unsigned int time) {
  unsigned int i, j;
  for(i = 0; i < time; i++)
    for (j = 0; j < 100; j++);
}

void main() {
  P2 = 0xFE;

  while(1) {
    P2_1 = 0;
    delay(1000);
    P2_1 = 1;
    delay(1000);
  }
}
