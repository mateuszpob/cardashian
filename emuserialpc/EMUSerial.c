#include "EMUSerial.h"
#include "globals.h"

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
    // struct emu_frame frame;
    memcpy(&decoded_frame, buffer, FRAME_SIZE);
	return decodeEmuFrame(&decoded_frame);
}

void display_data_object() {
	
	printf("TPS: %d, Batt: %f, RPM: %d \n", emu_data.TPS, emu_data.Batt, emu_data.RPM);
	
	// gotoxy(0,0);
	// system("clear");
	// printf("dwellTime: %f \n", emu_data.dwellTime);
	// printf("RPM:		%d \n", emu_data.RPM);
	// printf("gear:      	%d \n", emu_data.gear);
	// printf("vssSpeed:  	%f \n", emu_data.vssSpeed);
	// printf("CLT: 		%d \n", emu_data.CLT);
	// printf("MAP:       	%d \n", emu_data.MAP);
	// printf("TPS: 		%d \n", emu_data.TPS);
	// printf("IAT: 		%d \n", emu_data.IAT);
	// printf("IgnAngle:  	%lf \n", emu_data.IgnAngle);
	
	// printf("Batt:      	%f \n", emu_data.Batt);
	// printf("emuTemp: 	%d \n", emu_data.emuTemp);

	// printf("1 Pulse: 	%f \n", emu_data.pulseWidth);
	// printf("2 Pulse:	%f \n", emu_data.scondarypulseWidth);
	// printf("injDC:     	%f \n", emu_data.injDC);

	// printf("afrTarget: 	%f \n", emu_data.afrTarget);
	// printf("wboAFR: 	%f \n", emu_data.wboAFR);

// gotoxy(20,20); pulseWidth","scondarypulseWidth emuTemp

	// fflush(stdout);
	// fflush(stderr);
}

// char * get_filename(void) {
// time_t rawtime;
// 	struct tm * timeinfo;
// 	char *filename = malloc(128);
// 	time ( &rawtime );
// 	timeinfo = localtime ( &rawtime );
// 	sprintf(filename, "emudata_%d_%d_%d_%d:%d:%d", timeinfo->tm_mday,
//             timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
//             timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

// 			return filename;
// }

void store_frame(uint8_t *frame, int frame_length) {
	
	


	if(fptr == NULL) {
		// char *data_logger_filename = get_filename();
		printf("Filename: %s\n", data_logger_filename);
		fptr = fopen(data_logger_filename,"wb");
	}

	if(fptr == NULL) {
		printf("Error open data logger file\n");
		usleep(FRAME_WAIT_UTIME);
	}

	fwrite(frame, frame_length, 1, fptr);
}

void run_serial_reader(void) {
    printf("Connectiong to %s\n", serial_device_patch);
    

    pthread_create(&(serial_reader_thread), NULL, &start_reading, NULL);
    pthread_detach(serial_reader_thread);
}

void run_data_reader(void) {

    pthread_create(&(data_reader_thread), NULL, &start_reading_log, NULL);
    pthread_detach(data_reader_thread);
}

void * start_reading(void * args) {

    run_serial_client(serial_device_patch, B19200);
    
    uint8_t read_buffer[255] = {0};
    int bytes_avaiable = 0;

    uint8_t read_bytes_total = 0;

    while(1) {
        ioctl(serial_descriptor, FIONREAD, &bytes_avaiable);
		bytes_avaiable = 30;
        // uint8_t read_bytes = read(serial_descriptor, &read_buffer[read_bytes_total], bytes_avaiable);
        uint8_t read_bytes = read(serial_descriptor, read_buffer, bytes_avaiable);

		if(show_raw_frames_option == 1) {
			printf("[%d] raw bytes: ", read_bytes);
			print_frame(read_buffer, read_bytes);
		}
		
		if(store_frame_option) {
			store_frame(read_buffer, read_bytes);
		}

        while(--read_bytes) {
            if(read_buffer[1] == EMUSERIAL_MAGIC && checksum_is_ok(read_buffer) && prepareEmuFrame(read_buffer)) {
				if(show_live_params_option == 1) {
					display_data_object();
				}
            }
            memmove(read_buffer, ((uint8_t*)&read_buffer) + 1, read_bytes - 1);
        }
        usleep(FRAME_WAIT_UTIME);
    }
}

void * start_reading_log(void * args) {
	printf("Start emuserial reading log.\n");
	fptr = fopen(data_patch, "rb");
    
    int bytes_avaiable = 0;
	long filelen;
	uint8_t read_bytes;

	fseek(fptr, 0, SEEK_END);          // Jump to the end of the file
	filelen = ftell(fptr); 
	rewind(fptr); 

    uint8_t * read_buffer = (char *)malloc(filelen * sizeof(char));
	uint8_t read_bytrs_tmp = 0;

	while(read_bytes = fread(read_buffer, 1, 30, fptr)) {
		read_bytrs_tmp = read_bytes;

		if(show_raw_frames_option == 1) {
			printf("[%d] raw bytes: ", read_bytes);
			print_frame(read_buffer, read_bytes);
			fflush(stdout);
		}

		while(--read_bytrs_tmp) {
            if(read_buffer[1] == EMUSERIAL_MAGIC && checksum_is_ok(read_buffer) && prepareEmuFrame(read_buffer)) {
				if(show_live_params_option == 1) {
					display_data_object();
				}
            }
            memmove(read_buffer, (read_buffer) + 1, read_bytrs_tmp - 1);
        }
		usleep(FRAME_WAIT_UTIME);
	}
	fclose(fptr); 
	printf("Bytes read: %d\n\n", read_bytes);

	exit(0);
}