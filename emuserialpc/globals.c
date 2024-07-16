// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdint.h>
#include <stdint.h>
#include <pthread.h>
#include <netinet/in.h>
#include "globals.h"
#include "EMUSerial.h"
#include "format/emuStruct.h"  // Dodaj to
struct emu_data_t emu_data = {0}; 
struct emu_frame decoded_frame;

char * serial_device_patch;
int serial_descriptor;
char * data_patch;
FILE *fptr;
pthread_t serial_reader_thread;
pthread_t data_reader_thread;
uint8_t store_frame_option;
uint8_t show_raw_frames_option;
uint8_t show_live_params_option;
char * data_logger_filename;
int quiet_mode;
int socket_file_descriptor;
struct sockaddr_in serv_addr;
struct sockaddr_in cli_addr;
int clilen;
int total_client_couter;
int connfd;
char read_buffer[256];

#endif // GLOBALS_H