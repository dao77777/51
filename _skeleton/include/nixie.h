#ifndef __NIXIE_H__
#define __NIXIE_H__

unsigned char position_encode(unsigned char num);
unsigned char position_decode(unsigned char num);
void position_select(unsigned char num);
void position_left_shift(void);
void position_right_shift(void);
unsigned char segment_encode(unsigned char num);
unsigned char segment_decode(unsigned char num);
void segment_select(unsigned char num);
void segment_clear(void);
void segment_plus(void);
void segment_minus(void);
void nixie(unsigned char pos, unsigned char num);

#endif
