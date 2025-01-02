#include <stdbool.h>
#include <mcs51/8051.h>
#include "LCD1602.h"
#include "matrix_key.h"
#include "delay.h"

unsigned char key_status = 0;
unsigned int correct_password = 1234;
unsigned int password = 0;
short int password_status = 0; // 0 represent null, 1 represent ok, -1 represent err

void key_up_cb(unsigned char up_key) {
  // LCD_ShowNum(2, 1, up_key, 2);
  bool is_password_ready = (password / 1000) != 0;

  if (up_key <= 10) {
    /*
     * input
     */
    if (!is_password_ready) {
      password *= 10;
      password += (up_key % 10);
    }
  } else if (up_key == 11) {
    password_status = password != correct_password ? -1 : 1;
  } else if (up_key == 12) {
    /*
     * clean
     */
    password = 0;
    password_status = 0;
  } else if (up_key == 13) {
    /*
     * revert
     */
    password /= 10;
  }

}

void key_down_cb(unsigned char down_key) {

}

void main(void) {
  // row pin P1_3, P1_2, P1_1, P1_0
  // col pin P1_7, P1_6, P1_5, P1_4
  LCD_Init();
  LCD_ShowString(1, 1, "Password:");
  while (1) {
    /*
     * Event
     */
    unsigned char key = get_matrix_key();
    // key_down event
    if(key_status == 0 && key != 0) {
      delay(20);
      key_down_cb(key);
      key_status = key;
    // key_up event
    } else if (key_status != 0 && key == 0){
      delay(20);
      key_up_cb(key_status);
      key_status = key;
    }

    /*
     * UI
     */ 
    LCD_ShowNum(2, 1, password, 4);
    switch (password_status) {
      case 1:
        LCD_ShowString(1, 14, "OK ");
        break;
      case -1:
        LCD_ShowString(1, 14, "ERR");
        break;
      default:
        LCD_ShowString(1, 14, "   ");
        break;
    }
  }
}
