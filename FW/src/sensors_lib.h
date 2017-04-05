//arduino sensor test
#ifndef sensors_lib_h
#define sensors_lib_h


#define DS1307_I2C_ADDRESS 0x68

//wtf seriusly dude
#define MPU_6050_I2C_ADDRESS 0x68  // I2C address of the MPU-6050

#define LSM303_I2C_ADDRES 0x1E
#define LSM303_I2C_ADDRES_ACCEL 0x19
#define BMP_I2C_ADDRES 0x77
#include <Wire.h>


typedef struct TIME_FORMAT_t {
        uint8_t second;  // 0-59
        uint8_t minute;  // 0-59
        uint8_t hour;                       // 1-23
        uint8_t dayOfWeek;                  // 1-7
        uint8_t dayOfMonth;                 // 1-28/29/30/31
        uint8_t month;                      // 1-12
        uint8_t year;
} TIME_FORMAT;

typedef struct S3DVEC_t{
  int16_t x;
  int16_t y;
  int16_t z;
} S3DVEC;



inline void sensor_start(){
    Wire.begin();
}

 //  ____ _____ ____
 // |  _ \_   _/ ___|
 // | |_) || || |
 // |  _ < | || |___
 // |_| \_\|_| \____|
 //

//Currently not working, Ijust get garbage on the board (code works, it's the electrical connection)
void setDateRTC(TIME_FORMAT current);
TIME_FORMAT getDateRTC();

inline uint8_t decToBcd(uint8_t val)
{
        return ( (val/10*16) + (val%10) );
}

inline uint8_t bcdToDec(uint8_t val)
{
        return ( (val/16*10) + (val%16) );
}



//  __  __ ____  _   _  __    ___  ____   ___
// |  \/  |  _ \| | | |/ /_  / _ \| ___| / _ \
// | |\/| | |_) | | | | '_ \| | | |___ \| | | |
// | |  | |  __/| |_| | (_) | |_| |___) | |_| |
// |_|  |_|_|    \___/ \___/ \___/|____/ \___/
//


void mpuStart();
void mpuSleep();
S3DVEC getRotation();
S3DVEC getAcceleration();
uint16_t getTemperature();

//  _     ____  __  __ _____  ___ _____
// | |   / ___||  \/  |___ / / _ \___ /
// | |   \___ \| |\/| | |_ \| | | ||_ \
// | |___ ___) | |  | |___) | |_| |__) |
// |_____|____/|_|  |_|____/ \___/____/
void measureMagnet();
void initLSMAccel();
S3DVEC getMagnet();
S3DVEC getLSMAccel();


void inline writeLSM303reg(uint8_t reg, uint8_t data){
	Wire.beginTransmission(LSM303_I2C_ADDRES_ACCEL);
	Wire.write(reg);
	Wire.write(data);
	Wire.endTransmission(true);

}
//  ____  __  __ ____  _  ___   ___
// | __ )|  \/  |  _ \/ |( _ ) / _ \
// |  _ \| |\/| | |_) | |/ _ \| | | |
// | |_) | |  | |  __/| | (_) | |_| |
// |____/|_|  |_|_|   |_|\___/ \___/

uint16_t getPreassure(){
void measurePressure(){

#endif
