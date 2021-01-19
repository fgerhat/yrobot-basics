#ifndef DISPLAY_H
#define DISPLAY_H

int init_disp();
int disp_off();
int disp_on();
unsigned short get_segments(unsigned short value);
int disp(unsigned short value);
int disp_raw(unsigned short left, unsigned short right);

#endif