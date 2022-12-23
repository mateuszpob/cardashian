#ifndef _EMUSerial_h
#define _EMUSerial_h

#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include "serial.h"
#include "format/emuStruct.h"
#include "format/emuFormat.h"

#define EMU_TYPE_UBYTE 0
#define EMU_TYPE_SBYTE 1
#define EMU_TYPE_WORD 2
#define EMU_TYPE_SWORD 3

struct emu_frame {
	union {
		struct {
			uint8_t channel;
			uint8_t magic;
			uint8_t valueH;
			uint8_t valueL;
			uint8_t checksum;
		};
		uint8_t bytes[5];
	};
};



uint8_t decodeEmuFrame(struct emu_frame *frame);
uint8_t checksum_is_ok(uint8_t * buffer);
void * start_reading(void * args);
void display_data_object();

#define FRAME_SIZE 5
#define EMUSERIAL_MAGIC 0xA3

#endif

