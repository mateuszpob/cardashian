/* 
 * File:   main.c
 * Author: mp
 *
 * Created on 12 września 2018, 10:52
 * Created on 22 czerwca  2022, 23:55
 */


#include <stdio.h>
#include "socket_client.h"
#include "front.h"



int main(int argc, char** argv) {
    char * config_path = "/etc/qps/mierzejs_client.conf";
    
    return start_client(argc, argv);
}

