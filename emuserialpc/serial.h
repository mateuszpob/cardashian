/* 
 * File:   serial.h
 * Author: mp
 *
 * Created on 19 lipca 2019, 11:15
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h> 
#include <termios.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEFAULT_BAUD B9600

int serial_descriptor;
char * serial_device_patch;
char * data_patch;

int run_serial_client(int speed);
int set_interface_attribs(int fd, int speed, int parity);
void set_blocking (int fd, int should_block);
int write_frame_to_serial(uint8_t * frame);

#endif /* SERIAL_H */

