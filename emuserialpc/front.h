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
#include "EMUSerial.h"
#include "globals.h"

extern char * command_arguments[3];

int display_hint(char option);
void display_help(void);
void display(const char *format, ...);
int start_client(int argc, char** argv);
void display_error(const char *format, ...);

#endif