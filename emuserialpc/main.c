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

    
    // open data file 
    // if( argc >= 2 ) {
    //     if(strcmp(argv[1], "-l") == 0) {
    //         data_patch = (char*)argv[2];
    //         run_data_reader();

    //     } else {
            
    //         serial_device_patch = (char*)argv[1];
    //         run_serial_reader();
    //     }
    // } 
    // open reading from device
    // else {
    //     serial_device_patch = (char*)"/dev/ttyUSB0";
    //     run_serial_reader();
    // }

    startClient(argc, argv);

    run_socket_server(9990, &emu_data);

    while(1) {
        usleep(1000000);
    }

}
