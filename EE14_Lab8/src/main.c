#include <stm32l432xx.h>
#include "ee14lib.h"
#include <stdio.h>
#include <string.h>

#define PWR_MGMG_1 0x6B // bit the "wakes up" the sensor
#define ACCEL_XOUT_H 0x3B // top bit of accelerometer
#define GYRO_XOUT_H 0x43 // top bit of gyroscope

int _write(int file, char *data, int len) {
    serial_write(USART2, data, len);
    return len;
}

int main() 
{
   host_serial_init();

   i2c_init(I2C1, D1, D0);
   unsigned char device_address = 0b1101000;
   unsigned char data[] = {PWR_MGMG_1, 0};
   i2c_write(I2C1, device_address, data, 2);
   unsigned char accel_data[6];
   unsigned char gyro_data[6];

   volatile unsigned int i;
   volatile unsigned int sample = 0;

   //Delaying before the sampling
   for(i = 0; i < 10; i++) {}

   //Header for the CSV file
   printf("Measurement,Accel_X,Accel_Y,Accel_Z,Gyro_X,Gyro_Y,Gyro_Z\n");

    while(1) {

        // unsigned char addr = 
        // i2c_write(I2C1, b)

        // for (unsigned char i = 0; i < 128; i++) {
        //     unsigned char *data = &arr[0];
        //     unsigned char len = sizeof(arr);
        //     i2c_read(I2C1, i, data, len);
        //     i2c_write(I2C1, i, data, len);
        // }

        unsigned char accel[] = {ACCEL_XOUT_H};
        i2c_write(I2C1, device_address, accel, 1);
        i2c_read(I2C1, device_address, accel_data, 6);

        unsigned char gyro[] = {GYRO_XOUT_H};
        i2c_write(I2C1, device_address, gyro, 1);
        i2c_read(I2C1, device_address, gyro_data, 6);

        // for accelerometer
        short accel_x = ((short)accel_data[0] << 8) | accel_data[1];
        float actual_accel_x = (accel_x/16384.0f)*9.8;

        short accel_y = ((short)accel_data[2] << 8) | accel_data[3];
        float actual_accel_y = (accel_y/16384.0f)*9.8;

        short accel_z = ((short)accel_data[4] << 8) | accel_data[5];
        float actual_accel_z = (accel_z/16384.0f)*9.8;

        // for gyroscope

        short gyro_x = ((short)gyro_data[0] << 8) | gyro_data[1];
        float actual_gyro_x = (gyro_x/131.0f);

        short gyro_y = ((short)gyro_data[2] << 8) | gyro_data[3];
        float actual_gyro_y = (gyro_y/131.0f);

        short gyro_z = ((short)gyro_data[4] << 8) | gyro_data[5];
        float actual_gyro_z = (gyro_z/131);

        // printf("Acceleration (x direction): %d\n", (int)actual_accel_x);
        // printf("Acceleration (y direction): %d\n", (int)actual_accel_y);
        // printf("Acceleration (z direction): %d\n", (int)actual_accel_z);

        // printf("Angular Velocity (x direction): %d\n", (int)actual_gyro_x);
        // printf("Angular Velocity (y direction): %d\n", (int)actual_gyro_y);
        // printf("Angular Velocity (z direction): %d\n", (int)actual_gyro_z);

        // printing out all the values in CSV format
        printf("%d,%f,%f,%f,%f,%f,%f\n",
            sample + 1,
            actual_accel_x,actual_accel_y,actual_accel_z,
            (float)gyro_x/131,(float)gyro_y/131,(float)gyro_z/131);
        

        // increment the sampling count
        sample++;

        // Delay again
        for(i = 0; i < 10000; i++) {}



    }

    return 0;
}
