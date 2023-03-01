/* 
 * File:   main.c
 * Author: mp
 *
 * Created on 12 września 2018, 10:52
 */


#include <stdio.h>
#include "../socket_client.h"
#include "../front.h"

int configure(char * config_path) {
    FILE * fp;
    fp = fopen(config_path, "r");
    if (fp == NULL) {
        return 1;
    }
    char * line;
    size_t len = 0;
    ssize_t read;
    read = getline(&line, &len, fp);
    fclose(fp);
    
    hostname = strtok(line, ":");
    if (hostname == NULL)
        return 2;
    
    char *port = strtok(NULL, ":");
    if (port == NULL)
        return 3;
    portno = atoi(port);
    return 0;
}

int main(int argc, char** argv) {
    char * config_path = "/etc/qps/lockers_client.conf";
    portno = 0;
    hostname = NULL;
    if(configure(config_path) != 0)
        printf("Config [%s] not found or invalid.\n", config_path);
    return start_client(argc, argv);
}

