# make CC=gcc
# make CC=aarch64-linux-gnu-gcc		#Artik730
# make CC=arm-linux-gnueabihf-gcc	#RPI3
# CLIENT=iodriver


DIRS_BUILD=clients/$(CLIENT)/build
DIRS_OUTPUT=output

all:
	$(MAKE) CLIENT=iodriver iodriver_
	$(MAKE) CLIENT=lockers lockers_
	$(MAKE) queue

iodriver:
	$(MAKE) CLIENT=iodriver iodriver_
	
lockers:
	$(MAKE) CLIENT=lockers lockers_
	

# CLIENTS: ioriver lokers
$(CLIENT)_: $(CLIENT)_dir $(CLIENT)_front.o $(CLIENT)_main.o $(CLIENT)_socket_client.o $(CLIENT)_commands.o
	$(CC) -g clients/$(CLIENT)/build/main.o clients/$(CLIENT)/build/front.o clients/$(CLIENT)/build/socket_client.o clients/$(CLIENT)/build/commands.o -o $(DIRS_OUTPUT)/$(CLIENT) -lpthread -lm
	
$(CLIENT)_main.o: clients/$(CLIENT)/main.c clients/socket_client.h clients/front.h clients/$(CLIENT)/commands.h
	$(CC) -g clients/$(CLIENT)/main.c -c -o clients/$(CLIENT)/build/main.o

$(CLIENT)_socket_client.o: clients/socket_client.c clients/socket_client.h
	$(CC) -g clients/socket_client.c -c -o clients/$(CLIENT)/build/socket_client.o -lpthread

$(CLIENT)_commands.o: clients/$(CLIENT)/commands.c clients/$(CLIENT)/commands.h clients/socket_client.h
	$(CC) -g clients/$(CLIENT)/commands.c -c -o clients/$(CLIENT)/build/commands.o -lm

$(CLIENT)_front.o: clients/front.c clients/front.h
	$(CC) -g clients/front.c -c -o clients/$(CLIENT)/build/front.o

$(CLIENT)_dir:
	$(shell mkdir -p clients/$(CLIENT)/build $(DIRS_OUTPUT))


# QUEUE
queue: queue_dir queue_main.o queue_queue.o queue_frame.o queue_serial.o queue_socket_server.o
	$(CC) queue/build/main.o queue/build/queue.o queue/build/frame.o queue/build/serial.o queue/build/socket_server.o -o $(DIRS_OUTPUT)/queue -lpthread
	
queue_main.o: queue/main.c queue/main.h queue/serial.h queue/socket_server.h
	$(CC) queue/main.c -c -o queue/build/main.o
	
queue_socket_server.o: queue/queue.h queue/frame.h queue/socket_server.c queue/socket_server.h 
	$(CC) queue/socket_server.c -c -o queue/build/socket_server.o
	
queue_queue.o: queue/queue.c queue/queue.h queue/frame.h
	$(CC) queue/queue.c -c -o queue/build/queue.o
	
queue_serial.o: queue/serial.c queue/serial.h queue/socket_server.h queue/frame.h
	$(CC) queue/serial.c -c -o queue/build/serial.o
	
queue_frame.o: queue/frame.c queue/frame.h
	$(CC) queue/frame.c -c -o queue/build/frame.o

queue_dir:
	$(shell mkdir -p queue/build $(DIRS_OUTPUT))


clean:
	rm -f -r clients/iodriver/build clients/lockers/build queue/build

