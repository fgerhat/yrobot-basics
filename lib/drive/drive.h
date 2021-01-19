#ifndef DRIVE_H
#define DRIVE_H

#define DIR_STOP 0
#define DIR_FWD 1
#define DIR_REV -1

extern long steps_l;
extern long steps_r;

int init_drive();
int motors_stop();
int set_motor_l(signed int speed);
int set_motor_r(signed int speed);

#endif