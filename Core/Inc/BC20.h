#ifndef _BC20_H_
#define _BC20_H_

#define REV_OK 0   //������ɱ�־
#define REV_WAIT 1 //����δ��ɱ�־

#include "main.h"

/***************************************************
*GPS NMEA-0183Э����Ҫ�����ṹ�嶨��
*������Ϣ
***************************************************/
__packed typedef struct
{
    uint32_t latitude_bd;  //γ��   ������100000����ʵ��Ҫ����100000
    uint8_t nshemi_bd;     //��γ/��γ,N:��γ;S:��γ
    uint32_t longitude_bd; //���� ������100000��,ʵ��Ҫ����100000
    uint8_t ewhemi_bd;     //����/����,E:����;W:����
} gps_msg;

/* E53_ST1�������������Ͷ��� ------------------------------------------------------------*/
typedef struct
{
    float Longitude; //����
    float Latitude;  //γ��
} BC20_Data_TypeDef;

void BC20_Init(void);

void BC20_Clear(void);

void BC20_SendData(unsigned char *data);

unsigned char *BC20_GetIPD(unsigned short timeOut);

void BC20_SendMes(char *mes);

void BC20_SendGPS(void);

void BC20_GNSS_INIT(void); //��ʼ��gps

unsigned char BC20_GNSS_GET(void); //��ȡgps����

int NMEA_Str2num(uint8_t *buf, uint8_t *dx);

uint32_t NMEA_Pow(uint8_t m, uint8_t n);

uint8_t NMEA_Comma_Pos(uint8_t *buf, uint8_t cx);

void NMEA_BDS_GPRMC_Analysis(gps_msg *gpsmsg, uint8_t *buf);

void BC20_RESTART(void);

void BC20_RESET(void);
#endif
