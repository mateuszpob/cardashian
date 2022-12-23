#include "front.h"

int cmd_compare(uint8_t *cmd, uint8_t *command_buffer) {
    int len = strlen(command_buffer) - 1;
    uint8_t cmd_tmp[255];
    bzero(cmd_tmp, 255);
    memcpy(cmd_tmp, command_buffer, len);

    if (strlen(cmd_tmp) == strlen(cmd) && strcmp(cmd_tmp, cmd) == 0)
        return 1;
    return 0;
}

void run_interactive_mode() {
    list_command();
    while (1) {
        char command_buffer[255];
        fgets(command_buffer, 255, stdin);
        strtok(command_buffer, "\n");
        run_command(command_buffer);
    }
}

int display_hint(char option) {
    switch (option) {
        case 'd':
            fprintf(stderr, "Option -d require a device path.\n");
            break;
        case 'H':
            fprintf(stderr, "Option -H require a hostname.\n");
            break;
        case 'p':
            fprintf(stderr, "Option -p require a port number.\n");
            break;
        case 'c':
            fprintf(stderr, "Option -c require a command.\n");
            break;
        case 's':
            fprintf(stderr, "Option -s require a device serial.\n");
        case 'b':
            fprintf(stderr, "Available baud rates:\n");
            fprintf(stderr, "4800, 9600, 19200, 38400, 115200, 5(0.5M), 1(1M)\n");
            break;
        default:
            fprintf(stderr, "Unexpected option %c\n", option);
    }
    return 2;
}

void display_help(void) {
    printf("-h host             Host for socket mode\n");
    printf("-p port             Port for socket mode\n");
    printf("-d device_path      Device for serial mode\n");
    printf("-c command [args..] Run one command\n");
    printf("-s serial           Set device serial\n");
    printf("-i                  Run in interactive mode\n");
    printf("-l                  Display command list\n");
    printf("-q                  Quiet mode\n");
    printf("-b                  Set baud rate\n");
    printf("-v                  Verbose mode (display frames)\n");
    printf("--help              Display this help\n");
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
    quiet_mode = 0;
    verbose_mode = 0;

    opterr = 0;
    custom_baudrate = 0;
    char *command = NULL;
    int command_line_arg;
    int command_arg_used = 0;
    int display_command_list = 0;
    int port_setted = 0;
    int host_setted = 0;
    static int help_flag;
    int option_index = 0;

    static struct option long_options[] = {
        {"help", no_argument, &help_flag, 1},
        {0, 0, 0, 0}
    };

    while ((command_line_arg = getopt_long(argc, argv, "d:h:p:c:s:ilqb:v", long_options, &option_index)) != -1) {
        switch (command_line_arg) {
            case 'd':
                serial_mode = 1;
                serial_path = optarg;
                break;
            case 'h':
                hostname = optarg;
                host_setted = 1;
                break;
            case 'p':
                portno = atoi(optarg);
                port_setted = 1;
                break;
            case 'c':
                command = optarg;
                command_arg_used = 1;
                break;
            case 's':
                set_serial_(optarg);
                break;
            case 'i':
                interactive_mode = 1;
                break;
            case 'l':
                display_command_list = 1;
                list_command();
                return 0;
            case 'q':
                quiet_mode = 1;
                break;
            case 'b':
                custom_baudrate = atoi(optarg);
                break;
            case 'v':
                verbose_mode = 1;
                break;
            case '?':
                return display_hint(optopt);
                break;
        }
        if (command_line_arg == 'c') {
            int command_args_index = optind;
            int j = 0;
            for (int i = command_args_index; i < argc && j < 4; i++) {
                command_arguments[j] = argv[i];
                j++;
            }
        }
    }

    if (help_flag) {
        display_help();
        return 0;
    }

    if ((hostname == NULL || portno == 0) && serial_mode == 0 && (host_setted == 0 || port_setted == 0)) {
        printf("Type host (-h host) and port (-p port) or device path (-d path). Try '%s --help' for more information.\n", argv[0]);
        return 1;
    }

    if (command_arg_used == 0 && interactive_mode == 0) {
        printf("Type command (-c command) or use interactive mode (-i). Try '%s --help' for more information.\n", argv[0]);
        return 2;
    }

    start_socket_client();

    if (interactive_mode == 1) {
        run_interactive_mode();
        return 0;
    }
    if (command_arg_used == 1) {
        run_command(command);
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