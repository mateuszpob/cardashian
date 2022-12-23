#include "socket_server.h"

int run_socket_server(int port, struct emu_data_t *emu_data_struct) {

    printf("Starting server localhost:%d\n", port);

    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_file_descriptor < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(socket_file_descriptor, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(2);
    }

    listen(socket_file_descriptor, MAX_CLIENTS);

    wait_for_client(emu_data_struct);
    return 0;
}

void wait_for_client(struct emu_data_t *emu_data_struct) {
    clilen = sizeof(cli_addr);

    connfd = accept(socket_file_descriptor, (struct sockaddr *) &cli_addr, &clilen);
    printf("Client accepted\n");

    send_data(connfd, emu_data_struct);

    
}

void send_data(int connfd, struct emu_data_t *emu_data_struct) {
    int datalen = sizeof(struct emu_data_t);

    printf("Struct len %d\n", datalen); 
    
    do {
        printf("write %d to socket client...\n", datalen);
        write(connfd, emu_data_struct, datalen);
        usleep(50000);
    } while(read(connfd, read_buffer, 2) > 0);
    
    printf("Client spierdolil.\n");
    wait_for_client(emu_data_struct);
}