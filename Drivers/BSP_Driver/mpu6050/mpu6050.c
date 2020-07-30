#include "mpu6050.h"


void MPU6050_DELAY()
{
  uint32_t x;
  for(x=0;x<0XFFFFF;x++);
}


void MPU6050_Init(void)
{
    MPU6050_DELAY();
	MPU6050_WriteByte(MPU6050_RA_PWR_MGMT_1,0X00);  //解除休眠模式
	MPU6050_WriteByte(MPU6050_RA_SMPLRT_DIV,0x07);	//配置陀螺仪采样率
	MPU6050_WriteByte(MPU6050_RA_CONFIG,	0x06);
	MPU6050_WriteByte(MPU6050_RA_ACCEL_CONFIG,0x018);//配置工作在16G模式下
	MPU6050_WriteByte(MPU6050_RA_GYRO_CONFIG,0x18);	//陀螺仪自检测量范围
    MPU6050_DELAY();
}

/*
写数据到MPU6050里面
reg_add：寄存器地址
reg_dat：需要写入的数据
*/
void MPU6050_WriteByte(uint8_t reg_add,uint8_t reg_dat) 
{
	// I2C1_WriteByte(&reg_dat,MPU6050_ADDR,reg_add);
  I2C_WriteByte(MPU6050_ADDR,reg_add,&reg_dat);
}

/*
读MPU6050数据
reg_add：寄存器地址
reg_dat：需要写入的数据
*/
void MPU6050_Read(uint8_t reg_add,unsigned char* Read,uint8_t num)
{
	// I2C1_READ(Read,MPU6050_ADDR,reg_add,num);
  I2C_ReadBuffer(MPU6050_ADDR,reg_add,Read,num);
}

/***********************************************************************
*@Date: 2020-06-03 11:59:08
*@Function: 
*@Input: 
*@Return: 
*@Drscription: 
***********************************************************************/
uint8_t MPU6050_ReadID(void)
{
	//unsigned char Re = 0;
  
  MPU6050_ReadData MPU6050_DARA; 
  
	MPU6050_Read(MPU6050_ADDR_ID,&MPU6050_DARA.MPU6050_ID,1);
	if(MPU6050_DARA.MPU6050_ID != 0x68)
	{
		//printf("MPU6050 dectected error!\r\n");
		return 0;
	}
	else
	{
		//printf("MPU6050 ID = 0x%x\r\n",MPU6050_DARA.MPU6050_ID);
		return 1;
	}
}



/***********************************************************************
*@Function: MPU6050_ACC_Read
*@Input: *accData
*@Return: none
*@Author: sola
*@Date: 2020-02-22 18:33:06
*@Drscription: 加速度计原始数据获得
***********************************************************************/
void MPU6050_ACC_Read(short *accData)
{
	uint8_t buf[6];
    MPU6050_Read(MPU6050_ACC_OUT, buf, 6);
    accData[0] = (buf[0] << 8) | buf[1];
    accData[1] = (buf[2] << 8) | buf[3];
    accData[2] = (buf[4] << 8) | buf[5];
}

/***********************************************************************
*@Function: MPU6050_Gyro_Read
*@Input: *gyroData
*@Return: none
*@Author: sola
*@Date: 2020-02-22 18:33:29
*@Drscription: 陀螺仪原始数据获得
***********************************************************************/
void MPU6050_Gyro_Read(short *gyroData)
{
	 uint8_t buf[6];
    MPU6050_Read(MPU6050_GYRO_OUT,buf,6);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}

/***********************************************************************
*@Function: MPU6050_GET_Angle
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2020-02-22 18:33:53
*@Drscription: 获取不同方向的角度
***********************************************************************/
short MPU6050_GET_Angle(float x,float y,float z,uint8_t dir)
{
  float temp =0;
  float res = 0;
  switch(dir)
  {
    case 0:
      temp = sqrt((x*x + y*y))/z;
      res = atan(temp);
      break;
    case 1:
      temp = sqrt((y*y + z*z))/x;
      res = atan(temp);
      break;
    case 2:
      temp = sqrt((x*x + z*z))/y;
      res = atan(temp);
      break;
  }
    return (short)(res * (float)1800/(float)3.14);
}

/***********************************************************************
*@Function: Acce_angle
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2020-02-22 18:34:32
*@Drscription: 获取加速度计计算出的角度，包括Roll、Pitch
***********************************************************************/
void Acce_angle(short ax,short ay,short az,float *AccAngle)
{
  /*加速度求的 Roll*/
  AccAngle[0] = atan((float)ay/(float)az)*(float)57.3;                              //57.3 = 360°/2Π
  
  /*加速度求的 Pitch */
  AccAngle[1] = atan((float)ax/(float)az)*(float)57.3;                              //57.3 = 360°/2Π 
}

/***********************************************************************
*@Function: Gyro_angle
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2020-02-22 18:35:18
*@Drscription: 获取陀螺仪得到的角度，包括Roll、Pitch
***********************************************************************/
void Gyro_angle(short gx,short gy,short gz,float *GyroAngle)
{
    GyroAngle[0]=(float)gx/(float)7510.0;
    GyroAngle[1]=(float)gy/(float)7510.0;
    GyroAngle[2]=(float)gz/(float)7510.0;
}

float yijiehubu(float AccAngle,float Gyro,float dt,float k)
{
    static float angle;
    
    angle = k * AccAngle + (1-k) * (angle + Gyro * dt);
    
    return angle;
}


