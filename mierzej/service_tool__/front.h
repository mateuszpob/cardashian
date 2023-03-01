#ifndef FRONT_H
#define FRONT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <getopt.h>
#include <stdarg.h>
#include <time.h>

int custom_baudrate;
int quiet_mode;
extern int verbose_mode;
extern uint8_t *serial_path;
extern uint8_t *hostname;
extern int portno;
extern int interactive_mode;
extern char * command_arguments[3];

int cmd_compare(uint8_t *cmd, uint8_t *command_buffer);
void run_interactive_mode();
int display_hint(char option);
void display_help(void);
void display(const char *format, ...);
int start_client(int argc, char** argv);
void display_error(const char *format, ...);

extern void list_command(void);
extern void run_command(char *command);
extern void set_serial_(char *serial_string);
extern int start_socket_client(void);

#endif
