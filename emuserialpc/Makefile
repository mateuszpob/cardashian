
CC = gcc
CC = arm-linux-gnueabihf-gcc

CFLAGS = -Wall -Wextra -pthread -Wunused-variable
DEPS = socket_server.h serial.h format/emuFormat.h EMUSerial.h front.h globals.h format/emuStruct.h
OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/socket_server.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/EMUSerial.o $(BUILD_DIR)/globals.o $(BUILD_DIR)/front.o
BUILD_DIR = build

# Build target
all: $(BUILD_DIR)/emuserial

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile source files into object files in build directory
$(BUILD_DIR)/%.o: %.c $(DEPS) | $(BUILD_DIR)
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) -I. -c $< -o $@

# Link object files into the final executable
$(BUILD_DIR)/emuserial: $(OBJ)
	@echo "Linking $@"
	$(CC) $(CFLAGS) $^ -o $@

# Clean build directory
clean:
	@echo "Cleaning build directory"
	rm -rf $(BUILD_DIR)

.PHONY: all clean