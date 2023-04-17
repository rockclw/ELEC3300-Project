/*
 * mpu6050.h
 *      Author: rockc
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

//including headers
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"

//defining MPU6050 devices registers
#define MPU6050_ADDR 0xD0
#define ACCER_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#define PWR_MGMT 0x6B
#define SMPLRT_DIV 0x19
#define ACCER_OUT 0x3B
#define GYRO_OUT 0x43

//defining MPU6050 structure
struct MPU6050_Data{
	double x;
	double y;
	double z;
};

//defining const for converting raw data to general units
#define CONV_ACCER 16384.0
#define CONV_GYRO 131.0


//defining offset of sensor
#define  ACCER_OFFSET_X 0.0
#define  ACCER_OFFSET_Y 0.0
#define  ACCER_OFFSET_Z 0.0

#define  GYRO_OFFSET_X 0.0
#define  GYRO_OFFSET_Y 0.0
#define  GYRO_OFFSET_Z 0.0

//displaying function configuration
#define LEFTCORNER_X 0 //x coordinate of top-left data
#define LEFTCORNER_Y 10 //y coordinate of top-left data
#define ELEM_WIDTH 60 //width between elements
#define ELEM_HEIGHT 70 //height between elements

//basic functions
void MPU5050_INIT(void); //initialization of MPU6050 and IC2
int16_t MPU6050_Get_Data(uint8_t HighAddr); // getting a 16 bits(int) data from the high register address
uint8_t MPU6050_Read(uint8_t addr); //read 8 bits data from a register

//advanced functions. Expected to only use this functions in main.c
struct MPU6050_Data getACCER(void); //obtaining acceleration data
struct MPU6050_Data getGYRO(void); //obtaining gyro data
void MPU6050_display(void);//display the data on the lcd screen using the configuration above


#endif /* INC_MPU6050_H_ */
