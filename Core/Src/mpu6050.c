/*
 * mpu6050.c
 *
 *      Author: rockc
 */

#include "mpu6050.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c2;

//initialization of MPU6050 and IC2
void MPU5050_INIT(void){

	uint8_t Data = 0x00;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, PWR_MGMT, 1, &Data, 1, 1000);

	Data = 0x07;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, SMPLRT_DIV, 1, &Data, 1, 1000);

	Data = 0x00;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, ACCER_CONFIG, 1, &Data, 1, 1000);

	Data = 0x00;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, ACCER_CONFIG, 1, &Data, 1, 1000);
}

int16_t MPU6050_GetData(uint8_t HighAddr){
	uint8_t regData[2];

	regData[0] = MPU6050_Read(HighAddr);
	regData[1] = MPU6050_Read(HighAddr+1);

	return (int16_t)((regData[0] << 8) | regData[1]);
}

uint8_t MPU6050_Read(uint8_t addr){
	uint8_t Data;
	HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADDR, addr,1,  &Data, 1, 1000);
	return Data;
}

//obtaining acceleration data
struct MPU6050_Data getACCER(void){
	struct MPU6050_Data tmp = {0,0,0};
	tmp.x = (MPU6050_GetData(ACCER_OUT) + ACCER_OFFSET_X)/CONV_ACCER;
	tmp.y = (MPU6050_GetData(ACCER_OUT+2) + ACCER_OFFSET_Y)/CONV_ACCER;
	tmp.z = (MPU6050_GetData(ACCER_OUT+4) + ACCER_OFFSET_Z)/CONV_ACCER;
	return tmp;
}

//obtaining gyro data
struct MPU6050_Data getGYRO(void){
	struct MPU6050_Data tmp = {0,0,0};
	tmp.x = (MPU6050_GetData(GYRO_OUT) + GYRO_OFFSET_X)/CONV_GYRO;
	tmp.y = (MPU6050_GetData(GYRO_OUT+2) + GYRO_OFFSET_Y)/CONV_GYRO;
	tmp.z = (MPU6050_GetData(GYRO_OUT+4) + GYRO_OFFSET_Z)/CONV_GYRO;
	return tmp;
}

//display the data on the lcd screen using the configuration above
void MPU6050_display(void){
	  	 struct MPU6050_Data accer, gyro;
	  	 char line[9];

		 LCD_Clear(60, 120, 170, 20, BACKGROUND);

		 accer = getACCER();
		 gyro = getGYRO();

		 LCD_DrawString(LEFTCORNER_X + ELEM_WIDTH, LEFTCORNER_Y, "x");
		 LCD_DrawString(LEFTCORNER_X + 2*ELEM_WIDTH, LEFTCORNER_Y, "y");
		 LCD_DrawString(LEFTCORNER_X + 3*ELEM_WIDTH, LEFTCORNER_Y, "z");
		 LCD_DrawString(LEFTCORNER_X, LEFTCORNER_Y + ELEM_HEIGHT, "accer");
		 LCD_DrawString(LEFTCORNER_X, LEFTCORNER_Y + 2*ELEM_HEIGHT, "gyro");


		 sprintf(line, "%.2f", accer.x);
		 LCD_DrawString(LEFTCORNER_X + ELEM_WIDTH, LEFTCORNER_Y + ELEM_HEIGHT, line);
		 sprintf(line, "%.2f", accer.y);
		 LCD_DrawString(LEFTCORNER_X + 2*ELEM_WIDTH, LEFTCORNER_Y + ELEM_HEIGHT, line);
		 sprintf(line, "%.2f", accer.z);
		 LCD_DrawString(LEFTCORNER_X + 3*ELEM_WIDTH, LEFTCORNER_Y + ELEM_HEIGHT, line);

		 sprintf(line, "%.2f", gyro.x);
		 LCD_DrawString(LEFTCORNER_X + ELEM_WIDTH, LEFTCORNER_Y + 2*ELEM_HEIGHT, line);
		 sprintf(line, "%.2f", gyro.y);
		 LCD_DrawString(LEFTCORNER_X + 2*ELEM_WIDTH, LEFTCORNER_Y + 2*ELEM_HEIGHT, line);
		 sprintf(line, "%.2f", gyro.z);
		 LCD_DrawString(LEFTCORNER_X + 3*ELEM_WIDTH, LEFTCORNER_Y + 2*ELEM_HEIGHT, line);
}

