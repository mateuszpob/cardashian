
# CC=cc
CC=arm-linux-gnueabihf-gcc

all: build_dir main.o
	$(CC) build/main.o build/front.o build/socket_server.o build/EMUSerial.o build/serial.o -o emuserial -lpthread

main.o: 	socket_server.o front.o
	$(CC) main.c -c -o build/main.o

front.o:	EMUSerial.o
	$(CC) front.c -c -o build/front.o

socket_server.o:	EMUSerial.o
	$(CC) socket_server.c -c -o build/socket_server.o -lpthread

EMUSerial.o:	serial.o 
	$(CC) EMUSerial.c -c -o build/EMUSerial.o

serial.o: 
	$(CC) serial.c -c -o build/serial.o

build_dir:
	$(shell mkdir -p build)

clean:
	rm build/*