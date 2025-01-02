#include <mcs51/8051.h>

void delay(unsigned int time) {
  unsigned int i, j;
  for (i = 1; i <= time; i++)
    for (j = 1; j <= 100; j++);
}

unsigned char key1status = 0;
unsigned char key2status = 0;
unsigned char LED = 1;

void keydown_cb(unsigned char keynum) {}

void keyup_cb(unsigned char keynum) {
  switch (keynum) {
    case 1:
      LED = LED >> 1;
      LED = LED ? LED : 0x80;
      P2 = ~LED;
      break;
    case 2:
      LED = LED << 1;
      LED = LED ? LED : 1;
      P2 = ~LED;
      break;
    default:
      break;
  }
}

void main() {
  P2 = ~LED;
  while (1) {
    if (key1status != P3_1) {
      key1status = P3_1;
      if (P3_1) {
        keydown_cb(1);
      } else {
        keyup_cb(1);
      }
      delay(20);
    }

    if (key2status != P3_0) {
      key2status = P3_0;
      if (P3_0) {
        keydown_cb(2);
      } else {
        keyup_cb(2);
      }
      delay(20);
    }
  }
}
