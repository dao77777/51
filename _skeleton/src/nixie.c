#include <mcs51/8051.h>
#include "nixie.h"

unsigned char position_encode(unsigned char num) {
  return ~((num - 1) << 2);
}

unsigned char position_decode(unsigned char num) {
  unsigned char mask = 0x07 << 2;
  return (~(num | ~mask)>> 2) + 1;
}

void position_select(unsigned char num) {
  P2 = (P2 | (0x07 << 2)) & position_encode(num);
}

void position_left_shift(void) {
  unsigned char cur_pos = position_decode(P2);
  unsigned char next_pos = cur_pos == 1 ? 8 : cur_pos - 1;
  position_select(next_pos);
}

void position_right_shift(void) {
  unsigned char cur_pos = position_decode(P2);
  unsigned char next_pos = cur_pos % 8 + 1;
  position_select(next_pos);
}

unsigned char segment_encode(unsigned char num) {
  // Display rule: clock wise followed by 0x01 0x02 0x04 0x08 0x10 0x20, 0x40 for middle line, 0x80 for dot
  unsigned char num_map[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
  if (num <= 9) {
    return num_map[num];
  } else {
    return 0x00;
  }
}

unsigned char segment_decode(unsigned char num) {
  switch (num) {
    case 0x3F:
      return 0;
    case 0x06:
      return 1;
    case 0x5B:
      return 2;
    case 0x4F:
      return 3;
    case 0x66:
      return 4;
    case 0x6D:
      return 5;
    case 0x7D:
      return 6;
    case 0x07:
      return 7;
    case 0x7F:
      return 8;
    case 0x6F:
      return 9;
    default:
      return 0;
  }
}

void segment_select(unsigned char num) {
  P0 = segment_encode(num);
}

void segment_clear(void) {
  P0 = 0x00;
}

void segment_plus(void) {
  unsigned char cur_seg = segment_decode(P0);
  unsigned char next_seg = (cur_seg + 1) % 10;
  segment_select(next_seg);
}

void segment_minus(void) {
  unsigned char cur_seg = segment_decode(P0);
  unsigned char next_seg = cur_seg == 0 ? 9 : cur_seg - 1;
  segment_select(next_seg);
}

void nixie(unsigned char pos, unsigned char num) {
  position_select(pos);
  segment_select(num);
}

