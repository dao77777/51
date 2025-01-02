#include <mcs51/8051.h>
#include "delay.h"
#include "nixie.h"

unsigned char key1status = 1;
unsigned char key2status = 1;
unsigned char key3status = 1;
unsigned char key4status = 1;

void keyup_cb(unsigned char keynum) {
  switch (keynum) {
    case 1:
      position_left_shift();
      break;
    case 2:
      position_right_shift();
      break;
    case 3:
      segment_minus();
      break;
    case 4:
      segment_plus();
      break;
    default:
      break;
  }
}

void main(void) {
  nixie(1, 0);
  P3 = P3 | 0x0F;  

  while(1) {
    if (key1status != P3_1) {
      key1status = P3_1;
      if (!key1status) keyup_cb(1);
      delay(20);
    }

    if (key2status != P3_0) {
      key2status = P3_0;
      if (!key2status) keyup_cb(2);
      delay(20);
    }

    if (key3status != P3_2) {
      key3status = P3_2;
      if (!key3status) keyup_cb(3);
      delay(20);
    }

    if (key4status != P3_3) {
      key4status = P3_3;
      if (!key4status) keyup_cb(4);
      delay(20);
    }

    segment_clear();
    nixie(1, 2);
    delay(1);

    segment_clear();
    nixie(2, 5);
    delay(1);

    segment_clear();
    nixie(3, 6);
    delay(1);
  }
}
