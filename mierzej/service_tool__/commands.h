/* 
 * File:   commands.h
 * Author: mp
 *
 * Created on 14 września 2018, 10:13
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#define REGT2(reg) (uint8_t)(reg & 0xff), (uint8_t)(reg >> 8)
#define REGF2(reg, n) reg[n] | ((reg[n + 1]) << 8)

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 


#define MAX_PARAMS 12
#define RESPONSE_BITMASK 0x80

    // Locker opcodes
#define GET_VERSION 0x00
#define VERSION_MAJOR 0x07 
#define VERSION_MINOR 0x08 
    
#define TEMPERATURE_L 0x07
#define TEMPERATURE_H 0x08

#define GET_STATE 0x01
#define RES_DOOR_STATE 0x07
#define RES_PEAK_CURRENS 0x08 // 2 Bytes

#define GET_OPEN_TIMES 0x09
#define RES_PUSH_TIME 0x07
#define RES_WAIT_TIME 0x08
#define RES_PULL_TIME 0x09

#define SET_OPEN_TIMES 0x08
#define OPEN 0x10
#define OPEN_BY_DELAY 0x11
#define GET_TEMPERATURE 0x20
#define SET_LED_ON 0x30
#define SET_LED_OFF 0x31
    
#define EXCESSIVE_LOAD 1
#define NO_LOAD 2
    
    int interactive_mode;
    
    char * command_arguments[3];
    int command_params[MAX_PARAMS];

    struct input_command {
        uint8_t *cmd;
        void (*function_pointer)(void);
    };

    int * get_input_params(int number_of_parameters);
    void set_serial();
    void set_serial_(char *serial_string);

    void locker_get_version(void);
    void locker_get_state(void);
    void locker_get_open_times(void);
    void locker_set_open_times(void);
    void locker_open(void);
    void locker_open_by_delay(void);
    void locker_get_temperature(void);
    void set_led_on(void);
    void set_led_off(void);

    
    void run_many_cmds(void);
    void exit_application(void);

    void list_command(void);
    void run_command(char *command);

    extern void display(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_H */

