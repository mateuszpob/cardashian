#include "front.h"



int display_hint(char option) {
    switch (option) {
        case 'd':
            fprintf(stderr, "Option -d require a device path.\n");
            break;
        case 'r':
            fprintf(stderr, "Option -r require a file path.\n");
            break;
        case 's':
            fprintf(stderr, "Option -s require a data log file path.\n");
            break;
    }
    return 0;
}

void display_help(void) {
    printf("-d                  Set emu device path\n");
    printf("-r                  Run read data file mode\n");
    printf("-s                  Data logger mode\n");
    printf("--help              Display this help\n");
    exit(0);
}

/**
 * Printf with silent mode
 * @param format
 * @param ...
 */
void display(const char *format, ...) {
    if (quiet_mode)
        return;
    va_list arg;
    int done;

    va_start(arg, format);
    done = vfprintf(stdout, format, arg);
    va_end(arg);

    return;
}

int startClient(int argc, char** argv) {
    opterr = 0;
    static int help_flag;
    int option_index = 0;
    int command_line_arg;

    store_frame_option = 0;

    static struct option long_options[] = {
        {"help", no_argument, &help_flag, 1},
        {0, 0, 0, 0}
    };

    while ((command_line_arg = getopt_long(argc, argv, "d:r:s:", long_options, &option_index)) != -1) { // "d:h:p:c:s:ilqb:v"
        switch (command_line_arg) {
            case 'd':
                // serial_mode = 1;
                // serial_path = optarg;
                serial_device_patch = optarg;
                run_serial_reader();
                break;
            case 'r':
                data_patch = optarg;
                run_data_reader();
            case 's': // must be 'd' option selected
                store_frame_option = 1;
                data_logger_filename = optarg;
            case '?':
                return display_hint(optopt);
                break;
        }
    }

    if (help_flag) {
        display_help();
        return 0;
    }

    return 0;
}

void display_error(const char *format, ...) {
    va_list arg;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char * timestring = (char *) malloc(32);
    sprintf(timestring, "[%d-%d-%d %d:%d:%d] ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    const char * errorstring = strcat(timestring, format);
    va_start(arg, format);
    vfprintf(stderr, errorstring, arg);
    va_end(arg);

    return;
}

void print_frame(uint8_t *frame, int frame_length) {
    printf("[");
    for (int i = 0; i < frame_length; i++)
        printf("%02x ", (uint8_t) frame[i]);
    printf("]\n");
}