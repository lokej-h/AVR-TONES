#ifndef _MY_KEYPAD_H
#define _MY_KEYPAD_H

int get_row();

int get_col();

unsigned char is_pressed(unsigned char r, unsigned char c);

char getButtonValue(int buttonIn);

unsigned char findWhichPin();

char get_button_press();

void button_test();


#endif /* _MY_KEYPAD_H */