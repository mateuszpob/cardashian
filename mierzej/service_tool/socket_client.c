#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <termios.h>
#include "socket_client.h"
#include "front.h"

#define TOTAL_BUFFER_SIZE 4096

int frame_response_finish;
int response_timeout_ms = RESPONSE_TIMEOUT_MS;
uint8_t *response_frame;
int opcode = -1;
FILE *f;

uint8_t total_buffer[TOTAL_BUFFER_SIZE] = {0};
int total_buffer_counter = 0;

void print_frame(uint8_t *frame, int frame_length) {
    display("[ ");
    for (int i = 0; i < frame_length; i++)
        display("%02x ", (uint8_t) frame[i]);
    display("]\n");
}

uint8_t checksum(uint8_t *buffer) {
    int length = buffer[1] - 2;
    uint8_t lrc = 0;
    while (length--) {
        lrc ^= *buffer;
        buffer++;
    }
    return lrc;
}

void make_and_send_frame(uint8_t *payload, int payload_length) {

    int frame_length = 1 + 1 + 4 + payload_length + 1 + 1; // STX, Length, 4B address, Payload, LRC, ETX;

    uint8_t frame[frame_length];
    frame[0] = STX;
    frame[1] = frame_length;
    frame[2] = (uint8_t) device_address[0];
    frame[3] = (uint8_t) device_address[1];
    frame[4] = (uint8_t) device_address[2];
    frame[5] = (uint8_t) device_address[3];

    for (int i = 0; i < payload_length; i++) {
        frame[i + 6] = payload[i];
    }

    frame[frame_length - 2] = checksum((uint8_t*) & frame);
    frame[frame_length - 1] = ETX;



    send_frame(frame, frame_length);
}

void * read_frame(void * args) {

    while (1) {
        usleep(10);

        int read_bytes = 0;

        // SERIAL MODE
        int bytes_avaiable;
        ioctl(serial_descriptor, FIONREAD, &bytes_avaiable);
        if (bytes_avaiable <= 0)
            continue;

            read_bytes = read(serial_descriptor, &total_buffer[total_buffer_counter], bytes_avaiable);
        
        if (verbose_mode == 1) {
            printf("RAW read: ");
            print_frame(&total_buffer[total_buffer_counter], read_bytes);
            //printf("TOTAL r:  ");
            //print_frame(&total_buffer[0], total_buffer_counter + read_bytes);
        }

        total_buffer_counter += read_bytes;

        frameValidator();

        if (read_bytes <= 0)
            continue;

        //display("TOTAL (%dB): ", read_bytes);
        //print_frame(total_buffer, total_buffer_counter);

        if (total_buffer_counter >= TOTAL_BUFFER_SIZE) {
            fprintf(stderr, "Socket buffer overflow.\n");
            exit(3);
        }

    }
}

int send_frame(uint8_t *frame, int frame_length) {
    if (verbose_mode == 1) {
        display("REQUEST:  ");
        print_frame(frame, frame_length);
    }
    frame_response_finish = 0;
    bzero(response_frame, MAX_FRAME_LENGTH);


    write(serial_descriptor, frame, frame_length);
    tcflush(serial_descriptor, TCIOFLUSH);
    
    opcode = (int) frame[6];
    wait_for_response();
    return 0;
}

int frameValidator(void) {
    int i = 0;
    int start = 0;

    while (1) {
        int stx_position = -1;
        int etx_position = -1;
        int frame_length = 0;

        // Find STX
        //printf("Szukam STX od [%d]\n", start);
        for (i = start; i < total_buffer_counter; i++) {
            if (total_buffer[i] == STX) {
                //printf("STX [%d]\n", i);
                stx_position = i;
                break;
            }
        }
        if (stx_position < 0)
            return 1;

        // Find frame length
        frame_length = total_buffer[stx_position + 1];
        etx_position = frame_length + stx_position - 1;

        if (frame_length <= 0 || etx_position > total_buffer_counter)
            return 1;

        // printf("Len [%d], STX [%d], ETX_pos [%d]\n", frame_length, stx_position, etx_position);

        if (total_buffer[etx_position] == ETX) { //@TODO CRC
            if (total_buffer[stx_position + 6] == (opcode | 0x80)) {
                if (verbose_mode == 1) {
                    display("RESPONSE: ");
                    print_frame(&(total_buffer)[stx_position], frame_length);
                }
                memcpy(response_frame, &total_buffer[stx_position], total_buffer[stx_position + 1]);
                frame_response_finish = 1;
            } else {
                if (verbose_mode == 1) {
                    display("OTHER:    ");
                    print_frame(&(total_buffer)[stx_position], frame_length);
                }
            }
            int move_length = total_buffer_counter - etx_position - 1;

            memmove(total_buffer, &(total_buffer)[etx_position + 1], move_length);
            bzero(&(total_buffer)[move_length], TOTAL_BUFFER_SIZE - move_length);

            total_buffer_counter -= (frame_length + stx_position);

            start = 0;
        } else {
            start++;
        }

        if (start >= total_buffer_counter) {
            return 1;
        }
    }
    return 0;
}

void wait_for_response(void) {

    time_t t = time(NULL) + 2;
    while (time(NULL) < t) {
        if (frame_response_finish == 1) {
            frame_response_finish = 0;
            return;
        }
        usleep(100);
    }
    //    usleep(10000000);
    display_error("Timeouted.\n");
    exit(1);
    return;
}

// https://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
int set_interface_attribs(int fd, int speed, int parity) {
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr\n");
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr\n");
        return -1;
    }
    return 0;
}

void set_blocking (int fd, int should_block) {
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0){
        printf ("error from tggetattr\n");
        return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
        printf ("error setting term attributes\n");
}

int start_socket_client(void) {

    frame_response_finish = 0;
    response_frame = (uint8_t *) malloc(MAX_FRAME_LENGTH);

    // SERIAL
    serial_descriptor = open(serial_path, O_RDWR | O_NOCTTY | O_SYNC); // O_NOCTTY, O_NONBLOCK
    
    if(custom_baudrate > 0) {
        int baud;
        // 4800, 9600, 19200, 38400, 115200, 25(0.25M), 5(0.5M), 1(1M)
        switch(custom_baudrate) {
            case 4800:
                baud = B4800;
                break;
            case 9600:
                baud = B9600;
                break;
            case 19200:
                baud = B19200;
                break;
            case 38400:
                baud = B38400;
                break;
            case 115200:
                baud = B115200;
                break;
            case 5:
                baud = B500000;
                break;
            case 1:
                baud = B1000000;
                break;
            default:
                baud = B9600;
        }
        
        set_interface_attribs(serial_descriptor, baud, 0);
    } else {
        set_interface_attribs(serial_descriptor, DEFAULT_BAUD, 0);
    }
        
        
    

    pthread_t socket_read_thread;
    pthread_create(&socket_read_thread, NULL, &read_frame, NULL);
    pthread_detach(socket_read_thread);

    //    pthread_t frame_validator_thread;
    //    pthread_create(&frame_validator_thread, NULL, &frameValidator, NULL);
    //    pthread_detach(frame_validator_thread);

    return 0;
}
