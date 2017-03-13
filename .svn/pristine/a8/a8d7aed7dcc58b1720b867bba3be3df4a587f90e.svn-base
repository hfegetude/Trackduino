#include "sensors.h"
#include "Wire.h"



//  ____ _____ ____
// |  _ \_   _/ ___|
// | |_) || || |
// |  _ < | || |___
// |_| \_\|_| \____|
//

void setDateRTC( TIME_FORMAT current)
{
        Wire.beginTransmission(DS1307_I2C_ADDRESS);
        Wire.write(0);
        Wire.write(decToBcd(current.second));
        Wire.write(decToBcd(current.minute));
        Wire.write(decToBcd(current.hour));
        Wire.write(decToBcd(current.dayOfWeek));
        Wire.write(decToBcd(current.dayOfMonth));
        Wire.write(decToBcd(current.month));
        Wire.write(decToBcd(current.year));
        Wire.endTransmission();

}

// Gets the date and time from the ds1307
TIME_FORMAT getDateRTC()
{
        TIME_FORMAT current;
        Wire.beginTransmission(DS1307_I2C_ADDRESS);
        // Reset the register pointer
        //Reading from bit 0
// http://www.8051projects.net/wiki/DS1307_I2C_RTC_Interfacing_Tutorial
        Wire.write(0);
        Wire.endTransmission();
        Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

        // A few of these need masks because certain bits are control bits
        current.second     = bcdToDec(Wire.read() & 0x7f);
        current.minute     = bcdToDec(Wire.read());
        current.hour       = bcdToDec(Wire.read() & 0x3f);// Need to change this if 12 hour am/pm
        current.dayOfWeek  = bcdToDec(Wire.read());
        current.dayOfMonth = bcdToDec(Wire.read());
        current.month      = bcdToDec(Wire.read());
        current.year       = bcdToDec(Wire.read());
        return current;
}




//  __  __ ____  _   _  __    ___  ____   ___
// |  \/  |  _ \| | | |/ /_  / _ \| ___| / _ \
// | |\/| | |_) | | | | '_ \| | | |___ \| | | |
// | |  | |  __/| |_| | (_) | |_| |___) | |_| |
// |_|  |_|_|    \___/ \___/ \___/|____/ \___/
//


void mpuStart(){
        Wire.beginTransmission(MPU_6050_I2C_ADDRESS);
        Wire.write(0x6B); // PWR_MGMT_1 register
        Wire.write(0); // set to zero (wakes up the MPU-6050)
        Wire.endTransmission(true);
}

void mpuSleep(){
        Wire.beginTransmission(MPU_6050_I2C_ADDRESS);
        Wire.write(0x6B); // PWR_MGMT_1 register
        Wire.write( (uint8_t) 1<<6 ); // set to 1 (sleep the MPU-6050)
        Wire.endTransmission(true);
}

S3DVEC getRotation(){
        S3DVEC rotation;
        Wire.beginTransmission(MPU_6050_I2C_ADDRESS);
        Wire.write(0x43); // starting with register 0x43 (ACCEL_XOUT_H)
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_6050_I2C_ADDRESS,6,true); // request a total of 14 registers
        rotation.x=Wire.read()<<8|Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
        rotation.y=Wire.read()<<8|Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
        rotation.z=Wire.read()<<8|Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
        return rotation;
}

S3DVEC getAcceleration(){
        S3DVEC acceleration;
        Wire.beginTransmission(MPU_6050_I2C_ADDRESS);
        Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_6050_I2C_ADDRESS,6,true); // request a total of 14 registers
        acceleration.x=Wire.read()<<8|Wire.read();
        acceleration.y=Wire.read()<<8|Wire.read();
        acceleration.z=Wire.read()<<8|Wire.read();
        return acceleration;
}

uint16_t getTemperature(){
        Wire.beginTransmission(MPU_6050_I2C_ADDRESS);
        Wire.write(0x41); // starting with register 0x3B (ACCEL_XOUT_H)
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_6050_I2C_ADDRESS, 2, true); // request a total of 14 registers
        return Wire.read()<<8|Wire.read();
}


//  _     ____  __  __ _____  ___ _____
// | |   / ___||  \/  |___ / / _ \___ /
// | |   \___ \| |\/| | |_ \| | | ||_ \
// | |___ ___) | |  | |___) | |_| |__) |
// |_____|____/|_|  |_|____/ \___/____/


void measureMagnet(){
        Wire.beginTransmission(LSM303_I2C_ADDRES);
        Wire.write(1); //Make 1 measurement and place it on register
        Wire.endTransmission(true);
}

S3DVEC getMagnet(){
        S3DVEC magnetic_field;
        Wire.write(0x03);
        Wire.endTransmission(false);
        Wire.requestFrom(LSM303_I2C_ADDRES,6,true);
        magnetic_field.x=Wire.read()<<8|Wire.read();
        magnetic_field.y=Wire.read()<<8|Wire.read();
        magnetic_field.z=Wire.read()<<8|Wire.read();

}
