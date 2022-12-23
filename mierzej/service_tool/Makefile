# make CC=gcc
# make CC=aarch64-linux-gnu-gcc		#Artik730
# make CC=arm-linux-gnueabihf-gcc	#RPI3
# CLIENT=iodriver


DIRS_BUILD=build
DIRS_OUTPUT=output

all: mierzej_dir mierzej_front.o mierzej_main.o mierzej_socket_client.o mierzej_commands.o
	$(CC) -g $(DIRS_BUILD)/main.o $(DIRS_BUILD)/front.o $(DIRS_BUILD)/socket_client.o $(DIRS_BUILD)/commands.o -o $(DIRS_OUTPUT)/mierzej -lpthread -lm
	
mierzej_main.o: main.c socket_client.h front.h commands.h
	$(CC) -g main.c -c -o $(DIRS_BUILD)/main.o

mierzej_socket_client.o: socket_client.c socket_client.h
	$(CC) -g socket_client.c -c -o $(DIRS_BUILD)/socket_client.o -lpthread

mierzej_commands.o: commands.c commands.h socket_client.h
	$(CC) -g commands.c -c -o $(DIRS_BUILD)/commands.o -lm

mierzej_front.o: front.c front.h
	$(CC) -g front.c -c -o $(DIRS_BUILD)/front.o

mierzej_dir:
	$(shell mkdir -p $(DIRS_BUILD) $(DIRS_OUTPUT))

clean:
	rm -f -r $(DIRS_BUILD)

