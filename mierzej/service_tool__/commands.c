#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include "commands.h"
#include "../socket_client.h"
#include "../front.h"

/**
 * LOCKERS
 */
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

// ============================== Lockers ======================================

void locker_get_version(void) {
    uint8_t frame[] = {GET_VERSION};
    make_and_send_frame((uint8_t*) & frame, 1);

    display("Version: %d.%d\n\n", response_frame[VERSION_MAJOR], response_frame[VERSION_MINOR]);
}

void locker_get_state(void) {
    uint8_t frame[] = {GET_STATE};
    make_and_send_frame((uint8_t*) & frame, 1);

    display("Door state: %d\n", response_frame[RES_DOOR_STATE]);
    display("Peak current: %d\n\n", response_frame[RES_PEAK_CURRENS]);
}

void locker_get_open_times(void) {
    uint8_t frame[] = {GET_OPEN_TIMES};
    make_and_send_frame((uint8_t*) & frame, 1);

    display("Push time: %d\n", response_frame[RES_PUSH_TIME]);
    display("Wait time: %d\n", response_frame[RES_WAIT_TIME]);
    display("Pull time: %d\n\n", response_frame[RES_PULL_TIME]);
}

void locker_set_open_times(void) {
    if (interactive_mode == 1)
        display("Please push_time off_time pull_time:\n");
    int * input = get_input_params(3);

    uint8_t frame[] = {SET_OPEN_TIMES, input[0], input[1], input[2]};
    make_and_send_frame((uint8_t*) & frame, 4);
    display("\n");
}

void locker_open(void) {
    uint8_t frame[] = {OPEN};
    make_and_send_frame((uint8_t*) & frame, 1);
    display("\n");
}

void locker_open_by_delay(void) {
    uint8_t frame[] = {OPEN_BY_DELAY};
    make_and_send_frame((uint8_t*) & frame, 1);
    display("\n");
}

void locker_get_temperature(void) {
    uint8_t frame[] = {GET_TEMPERATURE};
    make_and_send_frame((uint8_t*) & frame, 1);

    uint16_t temperature_celsius = (response_frame[TEMPERATURE_L] | (response_frame[TEMPERATURE_H] << 8)) / 16;
    
    display("Temperature: %d°C\n\n", temperature_celsius);
}

void set_led_on(void) {
    uint8_t frame[] = {SET_LED_ON};
    make_and_send_frame((uint8_t*) & frame, 1);
    display("\n");
}

void set_led_off(void) {
    uint8_t frame[] = {SET_LED_OFF};
    make_and_send_frame((uint8_t*) & frame, 1);
    display("\n");
}

void run_many_cmds(void) {
    int i = 1;
    while (1) {
        locker_get_version();
        printf("===================> %d\n", i++);
        locker_get_state();
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
    display("GET_OPEN_TIMES\n");
    display("SET_OPEN_TIMES push_time wait_time pull_time");
    display("OPEN\n");
    display("OPEN_BY_DELAY\n");
    display("GET_TEMPERATURE\n");
    display("SET_LED_ON\n");
    display("SET_LED_OFF\n");
    display("exit\n");
    display("\n");
}

void run_command(char *command) {
    int command_valid = 0;
    struct input_command cmds[] = {
        {"", &list_command},
        {"setserial", &set_serial},
        {"GET_VERSION", &locker_get_version},
        {"GET_STATE", &locker_get_state},
        {"GET_OPEN_TIMES", &locker_get_open_times},
        {"SET_OPEN_TIMES", &locker_set_open_times},
        {"OPEN", &locker_open},
        {"OPEN_BY_DELAY", &locker_open_by_delay},
        {"GET_TEMPERATURE", &locker_get_temperature},
        {"SET_LED_ON", &set_led_on},
        {"SET_LED_OFF", &set_led_off},
        {"exit", &exit_application},
        {"run", &run_many_cmds}
    };

    for (int i = 0; i < sizeof (cmds) / sizeof (struct input_command); i++) {
        if (strcmp(cmds[i].cmd, command) == 0) {
            cmds[i].function_pointer();
        }
    }
}




