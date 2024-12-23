#include <mcs51/8051.h>

void delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 100; j++);
}

void key_down_cb() {
}

void key_up_cb() {
  if (P2_0 == 0) {
    P2_0 = 1;
  } else {
    P2_0 = 0;
  }
}

void main() {
  unsigned char key_status = 1;
  while (1) {
    if (key_status != P3_1) {
      if (P3_1) {
        key_down_cb();
      } else {
        key_up_cb();
      }
      delay(20);
      key_status = P3_1;
     }
  }
}
