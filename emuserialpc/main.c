#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "EMUSerial.h"
#include "socket_server.h"
#include "front.h"








/*
uint16_t:   2
uint8_t:    1
int8_t:     1
float:      4
struct emu_data_t 116
*/

void sig_handler(int signum){

  //Return type of the handler function should be void
  fclose(fptr);
  pthread_exit(&serial_reader_thread);
  printf("\nClose.\n");
  exit(0);
}

int main(int argc, char** argv) {
  printf ("Start emuserial.\n");
  
  signal(SIGINT,sig_handler);

  start_client(argc, argv);
  run_socket_server(9990, &emu_data);

}
