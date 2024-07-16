// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <netinet/in.h>
#include "format/emuStruct.h"  // Dodaj to


// Deklaracje zmiennych globalnych
extern struct emu_data_t emu_data;
extern struct emu_frame decoded_frame;

extern char * serial_device_patch;
extern int serial_descriptor;
extern char * data_patch;
extern FILE *fptr;
extern pthread_t serial_reader_thread;
extern pthread_t data_reader_thread;
extern uint8_t store_frame_option;
extern uint8_t show_raw_frames_option;
extern uint8_t show_live_params_option;
extern char * data_logger_filename;
extern int quiet_mode;
extern int socket_file_descriptor;
extern struct sockaddr_in serv_addr;
extern struct sockaddr_in cli_addr;
extern int clilen;
extern int total_client_couter;
extern int connfd;
extern char read_buffer[256];

#endif // GLOBALS_H