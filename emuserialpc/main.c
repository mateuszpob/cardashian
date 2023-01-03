#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "EMUSerial.h"
#include "socket_server.h"




// void print_frame(uint8_t *frame, int frame_length) {
//     printf("[");
//     for (int i = 0; i < frame_length; i++)
//         printf("%02x ", (uint8_t) frame[i]);
//     printf("]\n");
// }



/*
uint16_t:   2
uint8_t:    1
int8_t:     1
float:      4
*/



int main(int argc, char** argv) {
    if( argc == 2 ) {
        serial_device_patch = (char*)argv[1];
    } else {
        serial_device_patch = (char*)"/dev/ttyUSB0";
    }

    printf("Connectiong to %s\n", serial_device_patch);
    pthread_t serial_reader_thread;

    pthread_create(&(serial_reader_thread), NULL, &start_reading, NULL);
    pthread_detach(serial_reader_thread);

    run_socket_server(9990, &emu_data);

    while(1) {
        usleep(1000000);
    }

}
