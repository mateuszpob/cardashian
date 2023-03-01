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
*/

void sig_handler(int signum){

  //Return type of the handler function should be void
  fclose(fptr);
  pthread_exit(&serial_reader_thread);
  printf("\nClose.\n");
  exit(0);
}





int main(int argc, char** argv) {
    signal(SIGINT,sig_handler);

    start_client(argc, argv);

    run_socket_server(9990, &emu_data);

    while(1) {
        usleep(1000000);
    }

}
