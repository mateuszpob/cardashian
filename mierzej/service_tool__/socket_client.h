/* 
 * File:   socket_client.h
 * Author: mp
 *
 * Created on 13 września 2018, 15:27
 */

#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#define STX 0x02
#define ETX 0x03
#define MAX_FRAME_LENGTH 255
#define DEFAULT_BAUD B9600

#include <semaphore.h>
#include <sys/ioctl.h>
#include <stdint.h>
    
#define RESPONSE_TIMEOUT_MS 2100
#define CATCH_ALL 0
    extern int frame_response_finish;
    extern uint8_t *response_frame;
    uint8_t *hostname;
    int portno;
    int verbose_mode;
    int socket_file_descriptor;
    uint8_t *serial_path;
    // int serial_descriptor;
    sem_t queue_mutex;
    uint8_t device_address[4];
    
    void wait_for_response(void);
    int start_socket_client(void);
    void * read_frame(void * args);
    int send_frame(uint8_t *payload, int payload_length);
    int frameValidator(void);
    void make_and_send_frame(uint8_t *payload, int payload_length);
    uint8_t checksum(uint8_t *buffer);
    void print_frame(uint8_t *frame, int frame_length);
    int set_interface_attribs(int fd, int speed, int parity);
    void set_blocking (int fd, int should_block);
    extern void display(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* SOCKET_CLIENT_H */

