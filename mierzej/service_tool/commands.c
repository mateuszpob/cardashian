#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include "commands.h"
#include "socket_client.h"
#include "front.h"

/**
 * mierzejS
 */
int serial_mode = 0;
int interactive_mode = 0;
char * command_arguments[3] = {0, 0, 0};
//uint8_t device_address[] = {0xa5, 0xc1, 0x8d, 0x07};
uint8_t device_address[] = {0xaa, 0xbb, 0xcc, 0xdd};

void set_serial() {
    display("Type device serial: ");
    uint8_t *address_string = (uint8_t*) malloc(9 * sizeof (uint8_t));
    fgets(address_string, 9, stdin);
    set_serial_(address_string);
}

void set_serial_(char *address_string) {
    int j = 0;
    for (int i = 0; i < 8; i += 2) {
        uint8_t *hex_part = (uint8_t*) malloc(sizeof (uint8_t) * 3);
        memcpy(hex_part, &address_string[i], 2);
        hex_part[2] = '\0';
        device_address[j++] = (int) strtol(hex_part, NULL, 16);
    }
}

int * get_input_params(int number_of_parameters) {
    if (interactive_mode == 0) {
        int *params = (int*) malloc(3 * sizeof (int));
        for (int i = 0; i < number_of_parameters; i++) {
            params[i] = atoi(command_arguments[i]);
        }
        return params;
    }
    uint8_t *string = (uint8_t*) malloc(255 * sizeof (uint8_t));
    fgets(string, 255, stdin);
    int i = 0;
    char * part;
    part = strtok(string, " ");
    while (part != NULL && i < MAX_PARAMS) {
        command_params[i++] = atoi(part);
        part = strtok(NULL, " ");
    }
    if (number_of_parameters != i) {
        
        display_error("Invalid arguments count.\n");
        exit(1);
    }

    return (int *) &command_params;
}

// ============================== mierzejs ======================================

void mierzej_get_version(void) {
    uint8_t frame[] = {GET_VERSION};
    make_and_send_frame((uint8_t*) & frame, 1);

    display("Version: %d.%d\n\n", response_frame[VERSION_MAJOR], response_frame[VERSION_MINOR]);
}



void mierzej_get_state(void) {
    uint8_t frame[] = {GET_STATE};
    make_and_send_frame((uint8_t*) & frame, 1);

    uint32_t channel_1 = (uint32_t) (response_frame[10] << 24) | (response_frame[9] << 16) | (response_frame[8] << 8) | response_frame[7];
    uint32_t channel_2 = (uint32_t) (response_frame[14] << 24) | (response_frame[13] << 16) | (response_frame[12] << 8) | response_frame[11];
    uint32_t channel_3 = (uint32_t) (response_frame[18] << 24) | (response_frame[17] << 16) | (response_frame[16] << 8) | response_frame[15];
    uint32_t channel_4 = (uint32_t) (response_frame[22] << 24) | (response_frame[21] << 16) | (response_frame[20] << 8) | response_frame[19];
    uint32_t channel_5 = (uint32_t) (response_frame[26] << 24) | (response_frame[25] << 16) | (response_frame[24] << 8) | response_frame[23];

    display("Channel 1: %lu\nChannel 2: %lu\nChannel 3: %lu\nChannel 4: %lu\nChannel 5: %lu\n", channel_1, channel_2, channel_3, channel_4, channel_5);
}

void mierzej_read_voltage(void) {
    uint8_t frame[] = {READ_VOLTAGE};
    make_and_send_frame((uint8_t*) & frame, 1);

    uint32_t channel_1 = (uint32_t) (response_frame[10] << 24) | (response_frame[9] << 16) | (response_frame[8] << 8) | response_frame[7];
    uint32_t channel_2 = (uint32_t) (response_frame[14] << 24) | (response_frame[13] << 16) | (response_frame[12] << 8) | response_frame[11];
    uint32_t channel_3 = (uint32_t) (response_frame[18] << 24) | (response_frame[17] << 16) | (response_frame[16] << 8) | response_frame[15];
    uint32_t channel_4 = (uint32_t) (response_frame[22] << 24) | (response_frame[21] << 16) | (response_frame[20] << 8) | response_frame[19];
    uint32_t channel_5 = (uint32_t) (response_frame[26] << 24) | (response_frame[25] << 16) | (response_frame[24] << 8) | response_frame[23];

    display("Channel 1: %lu\nChannel 2: %lu\nChannel 3: %lu\nChannel 4: %lu\nChannel 5: %lu\n", channel_1, channel_2, channel_3, channel_4, channel_5);
}

void mierzej_read_resistance(void) {
    uint8_t frame[] = {READ_RESISTANCE};
    make_and_send_frame((uint8_t*) & frame, 1);

    uint32_t channel_1 = (uint32_t) (response_frame[10] << 24) | (response_frame[9] << 16) | (response_frame[8] << 8) | response_frame[7];
    uint32_t channel_2 = (uint32_t) (response_frame[14] << 24) | (response_frame[13] << 16) | (response_frame[12] << 8) | response_frame[11];
    uint32_t channel_3 = (uint32_t) (response_frame[18] << 24) | (response_frame[17] << 16) | (response_frame[16] << 8) | response_frame[15];
    uint32_t channel_4 = (uint32_t) (response_frame[22] << 24) | (response_frame[21] << 16) | (response_frame[20] << 8) | response_frame[19];
    uint32_t channel_5 = (uint32_t) (response_frame[26] << 24) | (response_frame[25] << 16) | (response_frame[24] << 8) | response_frame[23];

    display("Channel 1: %lu\nChannel 2: %lu\nChannel 3: %lu\nChannel 4: %lu\nChannel 5: %lu\n", channel_1, channel_2, channel_3, channel_4, channel_5);
}

void mierzej_read_value(void) {
    uint8_t frame[] = {READ_VALUE};
    make_and_send_frame((uint8_t*) & frame, 1);

    uint32_t channel_1 = (uint32_t) (response_frame[10] << 24) | (response_frame[9] << 16) | (response_frame[8] << 8) | response_frame[7];
    uint32_t channel_2 = (uint32_t) (response_frame[14] << 24) | (response_frame[13] << 16) | (response_frame[12] << 8) | response_frame[11];
    uint32_t channel_3 = (uint32_t) (response_frame[18] << 24) | (response_frame[17] << 16) | (response_frame[16] << 8) | response_frame[15];
    uint32_t channel_4 = (uint32_t) (response_frame[22] << 24) | (response_frame[21] << 16) | (response_frame[20] << 8) | response_frame[19];
    uint32_t channel_5 = (uint32_t) (response_frame[26] << 24) | (response_frame[25] << 16) | (response_frame[24] << 8) | response_frame[23];

    display("Channel 1: %lu\nChannel 2: %lu\nChannel 3: %lu\nChannel 4: %lu\nChannel 5: %lu\n", channel_1, channel_2, channel_3, channel_4, channel_5);
}

void run_many_cmds(void) {
    int i = 1;
    while (1) {
        mierzej_get_version();
        printf("===================> %d\n", i++);
        mierzej_get_state();
        printf("===================> %d\n", i++);
    }
}

void exit_application(void) {
    display("Exit\n");
    exit(0);
}
// =============================================================================

void list_command(void) {
    display("setserial serial\n");
    display("GET_VERSION\n");
    display("GET_STATE\n");
    display("READ_VOLTAGE\n");
    display("READ_RESISTANCE\n");
    display("READ_VALUE\n");
    display("GET_VALUE channel\n");

    display("exit\n");
    display("\n");
}

void run_command(char *command) {
    int command_valid = 0;
    struct input_command cmds[] = {
        {"", &list_command},
        {"setserial", &set_serial},
        {"GET_VERSION", &mierzej_get_version},
        {"GET_STATE", &mierzej_get_state},
        {"READ_VOLTAGE", &mierzej_read_voltage},
        {"READ_RESISTANCE", &mierzej_read_resistance},
        {"READ_VALUE", &mierzej_read_value},
        
        {"exit", &exit_application}
    };

    for (int i = 0; i < sizeof (cmds) / sizeof (struct input_command); i++) {
        if (strcmp(cmds[i].cmd, command) == 0) {
            cmds[i].function_pointer();
        }
    }
}




