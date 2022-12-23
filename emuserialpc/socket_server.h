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

#define MAX_CLIENTS 1

int socket_file_descriptor;
struct sockaddr_in serv_addr, cli_addr;
int clilen;
int total_client_couter;
int connfd;
uint8_t read_buffer[256];

int run_socket_server(int port, struct emu_data_t *emu_data_struct);
void send_data(int connfd, struct emu_data_t *emu_data_struct);
void wait_for_client( struct emu_data_t *emu_data_struct);

#endif