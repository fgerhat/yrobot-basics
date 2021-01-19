#ifndef DISPLAY_H
#define DISPLAY_H

extern unsigned short disp_l;
extern unsigned short disp_r;

int init_disp();
int disp_off();
int disp_on();
unsigned short get_segments(unsigned short value);
int disp_hex(unsigned short value);
int disp_dec(unsigned short value);
int disp_raw(unsigned short left, unsigned short right);

#endif