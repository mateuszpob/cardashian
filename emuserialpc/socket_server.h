#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <stdio.h>
#include <netdb.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "format/emuStruct.h"
#include "globals.h"
#define MAX_CLIENTS 1
#define FRAME_WAIT_UTIME 10000

int run_socket_server(int port, struct emu_data_t *emu_data_struct);
void send_data(int connfd, struct emu_data_t *emu_data_struct);
void wait_for_client( struct emu_data_t *emu_data_struct);

#endif