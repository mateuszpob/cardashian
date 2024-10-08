#ifndef EMU_STRUCT_H
#define EMU_STRUCT_H
#define EMU_VERSION1_200

struct emu_data_t {
	uint16_t RPM;  //RPM
	uint16_t MAP;  //kPa
	uint8_t TPS;  //%
	int8_t IAT;  //C
	float Batt;  //V
	float IgnAngle;  //deg
	float pulseWidth;  //ms
	float scondarypulseWidth;  //ms
	uint16_t Egt1;  //C
	uint16_t Egt2;  //C
	float knockLevel;  //V
	float dwellTime;  //ms
	float wboAFR;  //AFR
	int8_t gear;  //
	uint8_t Baro;  //kPa   40
	float analogIn1;  //V
	float analogIn2;  //V
	float analogIn3;  //V
	float analogIn4;  //V
	float injDC;  //%			60
	int8_t emuTemp;  //C
	float oilPressure;  //Bar
	uint8_t oilTemperature;  //C
	float fuelPressure;  //Bar		70
	int16_t CLT;  //C
	float flexFuelEthanolContent;  //%
	int8_t ffTemp;  //C			77
	float wboLambda;  //λ		81
	float vssSpeed;  //km/h
	uint16_t deltaFPR;  //kPa
	uint8_t fuelLevel;  //%
	uint8_t tablesSet;  //		91
	float lambdaTarget;  //λ   
	float afrTarget;  //AFR		99
	uint16_t cel;  //			101
};
#endif