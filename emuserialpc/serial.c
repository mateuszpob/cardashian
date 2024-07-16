#include "serial.h"
#include "globals.h"

int run_serial_client(char * device_path, int speed) {
    serial_descriptor = open(device_path, O_RDWR | O_NOCTTY | O_SYNC); // O_NOCTTY, O_NONBLOCK
    set_interface_attribs(serial_descriptor, speed, 0);
    set_blocking(serial_descriptor, 0);
    return 0;
}

// https://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c

int set_interface_attribs(int fd, int speed, int parity) {
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr\n");
        return -1;
    }

    cfsetospeed(&tty, (speed_t) speed);
    cfsetispeed(&tty, (speed_t) speed);

    tty.c_cflag |= (CLOCAL | CREAD); /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8; /* 8-bit characters */
    tty.c_cflag &= ~PARENB; /* no parity bit */
    tty.c_cflag &= ~CSTOPB; /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS; /* no hardware flowcontrol */

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

void set_blocking(int fd, int should_block) {
    struct termios tty;
    memset(&tty, 0, sizeof tty);
    if (tcgetattr(fd, &tty) != 0) {
        printf("error from tggetattr\n");
        return;
    }

    tty.c_cc[VMIN] = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5; // 0.5 seconds read timeout

    if (tcsetattr(fd, TCSANOW, &tty) != 0)
        printf("error setting term attributes\n");
}

int write_frame_to_serial(uint8_t * frame) {
    tcflush(serial_descriptor, TCIOFLUSH);
    if (write(serial_descriptor, frame, frame[1]) < 0) {
        printf("Send frame to serial ERROR. Trying reconnect...\n");

        // run_serial_client(serial_device_patch);

        return 1;
    }
    return 0;
}
