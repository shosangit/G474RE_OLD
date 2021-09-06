#ifndef _BC20_H_
#define _BC20_H_

#define REV_OK 0   //接收完成标志
#define REV_WAIT 1 //接收未完成标志

#include "main.h"

/***************************************************
*GPS NMEA-0183协议重要参数结构体定义
*卫星信息
***************************************************/
__packed typedef struct
{
    uint32_t latitude_bd;  //纬度   分扩大100000倍，实际要除以100000
    uint8_t nshemi_bd;     //北纬/南纬,N:北纬;S:南纬
    uint32_t longitude_bd; //经度 分扩大100000倍,实际要除以100000
    uint8_t ewhemi_bd;     //东经/西经,E:东经;W:西经
} gps_msg;

/* E53_ST1传感器数据类型定义 ------------------------------------------------------------*/
typedef struct
{
    float Longitude; //经度
    float Latitude;  //纬度
} BC20_Data_TypeDef;

void BC20_Init(void);

void BC20_Clear(void);

void BC20_SendData(unsigned char *data);

unsigned char *BC20_GetIPD(unsigned short timeOut);

void BC20_SendMes(char *mes);

void BC20_SendGPS(void);

void BC20_GNSS_INIT(void); //初始化gps

unsigned char BC20_GNSS_GET(void); //获取gps数据

int NMEA_Str2num(uint8_t *buf, uint8_t *dx);

uint32_t NMEA_Pow(uint8_t m, uint8_t n);

uint8_t NMEA_Comma_Pos(uint8_t *buf, uint8_t cx);

void NMEA_BDS_GPRMC_Analysis(gps_msg *gpsmsg, uint8_t *buf);

void BC20_RESTART(void);

void BC20_RESET(void);
#endif
