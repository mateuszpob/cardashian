#include "EMUSerial.h"

void gotoxy(int x,int y)
{
printf("%c[%d;%df",0x1B,y,x);
}

uint8_t decodeEmuFrame(struct emu_frame *frame) {
	int index = -1;

	//Find array index for channel and mapping
	for (int i = 0; i < sizeof(channels) / sizeof(channels[0]); i++) {
		if (channels[i] == (*frame).channel) {
			index = i;
			break;
		}
	}

	//Firmware on emu != Firmware in format file?
	if (index == -1) {
		return 0; 
	}

	//Map channel to struct "index"
	const void* p = channelMapping[index];

	int16_t div = divider[index];
	uint8_t stor = typeIncoming[index];

	//Integer values
	if (div == 1) {
		if (stor == EMU_TYPE_UBYTE) *((uint8_t*)p) = (*frame).valueL;
		else if (stor == EMU_TYPE_SBYTE) *((int8_t*)p) = (int8_t)(*frame).valueL;
		else if (stor == EMU_TYPE_WORD) *((uint16_t*)p) = ((uint16_t)((*frame).valueH) << 8) | (*frame).valueL;
		else if (stor == EMU_TYPE_SWORD) *((int16_t*)p) = ((int16_t)((*frame).valueH) << 8) | (*frame).valueL;
	}

	//Floats
	else {
		if (stor == EMU_TYPE_UBYTE) *((float*)p) = (float)((*frame).valueL) / div;
		else if (stor == EMU_TYPE_SBYTE) *((float*)p) = (float)((int8_t)(*frame).valueL) / div;
		else if (stor == EMU_TYPE_WORD) *((float*)p) = (float)(((uint16_t)((*frame).valueH) << 8) | (*frame).valueL) / div;
		else if (stor == EMU_TYPE_SWORD) *((float*)p) = (float)(((int16_t)((*frame).valueH) << 8) | (*frame).valueL) / div;
	}
	return 1;
}



uint8_t checksum_is_ok(uint8_t * buffer) { 
	uint8_t checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
    if(buffer[4] == checksum) {
        return 1;
    }
    return 0;
}



uint8_t prepareEmuFrame(uint8_t * buffer) {
    struct emu_frame frame;
    memcpy(&frame, buffer, FRAME_SIZE);
	return decodeEmuFrame(&frame);
}

void display_data_object() {
		system("clear");
		gotoxy(0,0);
		printf("dwellTime: %f \n", emu_data.dwellTime);
		printf("Batt:      %f \n", emu_data.Batt);
		printf("MAP:       %d \n", emu_data.MAP);
		printf("injDC:     %f \n", emu_data.injDC);
		printf("IgnAngle:  %lf \n", emu_data.IgnAngle);
		printf("gear:      %d \n", emu_data.gear);
		printf("TPS:       %d \n", emu_data.TPS);
		printf("vssSpeed:  %f \n", emu_data.vssSpeed);
		printf("afrTarget: %f \n", emu_data.afrTarget);
		printf("wboAFR:    %f \n", emu_data.wboAFR);
		printf("wboLambda: %f \n", emu_data.wboLambda);
// 		printf("MAP:       %d \n", emu_data.MAP);
// 		printf("MAP:       %d \n", emu_data.MAP);
// 		printf("MAP:       %d \n", emu_data.MAP);
// 		printf("MAP:       %d \n", emu_data.MAP);
// 		printf("MAP:       %d \n", emu_data.MAP);

	gotoxy(20,20);
}

void * start_reading(void * args) {

    run_serial_client(serial_device_patch, B19200);
    
    uint8_t read_buffer[255] = {0};
    int bytes_avaiable = 0;

    uint8_t read_bytes_total = 0;
    uint8_t response_found = 0;

    while(1) {
        ioctl(serial_descriptor, FIONREAD, &bytes_avaiable);
		bytes_avaiable = 30;
        // uint8_t read_bytes = read(serial_descriptor, &read_buffer[read_bytes_total], bytes_avaiable);
        uint8_t read_bytes = read(serial_descriptor, read_buffer, bytes_avaiable);

        // printf("[%d] raw bytes: ", read_bytes);
        // print_frame(read_buffer, read_bytes);

        while(--read_bytes) {
            if(read_buffer[1] == EMUSERIAL_MAGIC && checksum_is_ok(read_buffer) && prepareEmuFrame(read_buffer)) {
				display_data_object();
            }
            memmove(read_buffer, ((uint8_t*)&read_buffer) + 1, read_bytes - 1);
        }

        usleep(100000);
    }
}