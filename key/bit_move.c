#include <mcs51/8051.h>

void delay(unsigned int time) {
  unsigned int i, j;
  for (i = 1; i <= time; i++)
    for (j = 1; j <= 100; j++);
}

unsigned char keystatus = 0;
unsigned char LED = 1;

void keydown_cb() {}

void keyup_cb() {
  LED = LED << 1;
  LED = LED ? LED : 1;
  P2 = ~LED;
}

void main() {
  P2 = ~LED;
  while (1) {
    if (keystatus != P3_1) {
      keystatus = P3_1;
      if (P3_1) {
        keydown_cb();
      } else {
        keyup_cb();
      }
      delay(20);
    }
  }
}
