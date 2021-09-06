#include "stm32g4xx_hal.h"
#include "BC20.h"
#include "usart.h"
#include "gpio.h"
#include <string.h>
#include <stdio.h>

//#define BC20_ONENET_INFO	"AT+QIOPEN=1,0,\"TCP\",\"183.230.40.40\",1811,1234,0\r\n"		//TCP����
#define BC20_MQTT_INFO "AT+QMTOPEN=0,\"mqtts.heclouds.com\",1883\r\n"                                                                                                                           //��mqtt�ͻ���
#define BC20_CONNECT_INFO "AT+QMTCONN=0,\"wuhu1\",\"451120\",\"version=2018-10-31&res=products%2F451120%2Fdevices%2Fwuhu1&et=1703433600&method=md5&sign=LSVisLEm3%2F03R6bkkmYe%2FA%3D%3D\"\r\n" //����MQTT������

extern uint8_t usart1_rx_flag;
extern uint8_t usart1_dma_buffer[512];
extern uint8_t usart1_rx_buffer[1024];
extern uint16_t usart1_rx_len;
extern uint16_t usart1_dma_len;
extern uint8_t BC20flag;
extern gps_msg gpsmsg;
extern BC20_Data_TypeDef BC20_GPS_Data;
uint8_t wnb = 0;

/***************************************************\
* ��������: NMEA_Comma_Pos
*    �������ܣ���buf����õ���cx���������ڵ�λ��
*    ����ֵ��
*    ����ֵ��0~0xFE��������������λ�õı���
*                     0xFF�����������ڵ�cx������
***************************************************/

uint8_t NMEA_Comma_Pos(uint8_t *buf, uint8_t cx)
{
    uint8_t *p = buf;
    while (cx)
    {
        if (*buf == '*' || *buf < ' ' || *buf > 'z')
            return 0xFF;
        if (*buf == ',')
            cx--;
        buf++;
    }
    return buf - p;
}
/***************************************************\
* ��������: NMEA_Pow
*    �������ܣ�����m��n�η�ֵ
*    ����ֵ������m��ָ��n
*    ����ֵ��m^n
***************************************************/
uint32_t NMEA_Pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while (n--)
        result *= m;
    return result;
}
/***************************************************\
* ��������: NMEA_Str2num
*    �������ܣ�str����ת��Ϊ��int�����֣���','����'*'����
*    ����ֵ��buf�����ִ洢��
*                     dx��С����λ�������ظ����ú���
*    ����ֵ��ת�������ֵ
***************************************************/
int NMEA_Str2num(uint8_t *buf, uint8_t *dx)
{
    uint8_t *p = buf;
    uint32_t ires = 0, fres = 0;
    uint8_t ilen = 0, flen = 0, i;
    uint8_t mask = 0;
    int res;
    while (1)
    {
        if (*p == '-')
        {
            mask |= 0x02;
            p++;
        } //˵���и���
        if (*p == ',' || *p == '*')
            break; //����������
        if (*p == '.')
        {
            mask |= 0x01;
            p++;
        }                                //����С����
        else if (*p > '9' || (*p < '0')) //���ֲ���0��9֮�ڣ�˵���зǷ��ַ�
        {
            ilen = 0;
            flen = 0;
            break;
        }
        if (mask & 0x01)
            flen++; //С�����λ��
        else
            ilen++; //str���ȼ�һ
        p++;        //��һ���ַ�
    }
    if (mask & 0x02)
        buf++;                 //�Ƶ���һλ����ȥ����
    for (i = 0; i < ilen; i++) //�õ�������������
    {
        ires += NMEA_Pow(10, ilen - 1 - i) * (buf[i] - '0');
    }
    if (flen > 5)
        flen = 5; //���ȡ��λС��
    *dx = flen;
    for (i = 0; i < flen; i++) //�õ�С����������
    {
        fres += NMEA_Pow(10, flen - 1 - i) * (buf[ilen + 1 + i] - '0');
    }
    res = ires * NMEA_Pow(10, flen) + fres;
    if (mask & 0x02)
        res = -res;
    return res;
}
/***************************************************\
* ��������: NMEA_BDS_GPRMC_Analysis
*    �������ܣ�����GPRMC��Ϣ
*    ����ֵ��gpsx,NMEA��Ϣ�ṹ��
*                 buf�����յ���GPS���ݻ������׵�ַ
***************************************************/
void NMEA_BDS_GPRMC_Analysis(gps_msg *gpsmsg, uint8_t *buf)
{
    uint8_t *p4, dx;
    uint8_t posx;
    uint32_t temp;
    float rs;
    p4 = (uint8_t *)strstr((const char *)buf, "$GNGLL"); //"$GNGLL",������&��GPRMC�ֿ������,��ֻ�ж�GPRMC.
    posx = NMEA_Comma_Pos(p4, 1);                        //�õ�γ��
    if (posx != 0XFF)
    {
        temp = NMEA_Str2num(p4 + posx, &dx);
        gpsmsg->latitude_bd = temp / NMEA_Pow(10, dx + 2);                                              //�õ���
        rs = temp % NMEA_Pow(10, dx + 2);                                                               //�õ�'
        gpsmsg->latitude_bd = gpsmsg->latitude_bd * NMEA_Pow(10, 5) + (rs * NMEA_Pow(10, 5 - dx)) / 60; //ת��Ϊ��
    }
    posx = NMEA_Comma_Pos(p4, 2); //��γ���Ǳ�γ
    if (posx != 0XFF)
        gpsmsg->nshemi_bd = *(p4 + posx);
    posx = NMEA_Comma_Pos(p4, 3); //�õ�����
    if (posx != 0XFF)
    {
        temp = NMEA_Str2num(p4 + posx, &dx);
        gpsmsg->longitude_bd = temp / NMEA_Pow(10, dx + 2);                                               //�õ���
        rs = temp % NMEA_Pow(10, dx + 2);                                                                 //�õ�'
        gpsmsg->longitude_bd = gpsmsg->longitude_bd * NMEA_Pow(10, 5) + (rs * NMEA_Pow(10, 5 - dx)) / 60; //ת��Ϊ��
    }
    posx = NMEA_Comma_Pos(p4, 4); //������������
    if (posx != 0XFF)
        gpsmsg->ewhemi_bd = *(p4 + posx);
}

void BC20_GPS_Read_Data(void)
{
    /* �������������ַ���������GPS���� */
    NMEA_BDS_GPRMC_Analysis(&gpsmsg, (uint8_t *)usart1_rx_buffer);

    /* ���������ľ�γ�����ݴ�ŵ��ṹ���У�������������ʹ�� */
    BC20_GPS_Data.Longitude = (float)((float)gpsmsg.longitude_bd / 100000);
    BC20_GPS_Data.Latitude = (float)((float)gpsmsg.latitude_bd / 100000);
}

void BC20_Clear(void)
{

    memset(usart1_rx_buffer, 0, sizeof(usart1_rx_buffer));
}

int BC20_SendCmd(char *cmd, char *reply, int wait)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)cmd, strlen(cmd), 0xffff);
    printf("[BC20_SendCmd] %s\r\n", cmd);

    HAL_Delay(wait);

    if (usart1_rx_flag == 1) //�յ��ж�
    {
        if (strstr((char *)usart1_rx_buffer, reply)) //�Ƿ��������
        {
            printf("CMD->%s\r\n+++YES\r\n", usart1_rx_buffer);
            usart1_rx_flag = 0;
            BC20_Clear();
            return 1;
        }
        else if (strstr((char *)usart1_rx_buffer, "ERROR"))
        {
            printf("CMD->%s\r\n+++ERROR\r\n", usart1_rx_buffer);
            usart1_rx_flag = 0;
            BC20_Clear();
            return 0;
        }
        else
        {
            printf("CMD->%s\r\n+++NO\r\n", usart1_rx_buffer);
            usart1_rx_flag = 0;
            return 0;
        }
    }
    else
    {   //δ���ж�
        printf("\r\n+++null\r\n");
        usart1_rx_flag = 0;
        return 0;
    };
}

void BC20_SendMes(char *mes)
{

    char mesbody[200];
    sprintf(mesbody, "AT+QMTPUB=0,0,0,0,\"$sys/451120/wuhu1/dp/post/json\",\"{\"id\": 123,\"dp\": {\"state\": [{\"v\": \"%s\",}]}}\r\n", *(&mes));

    HAL_UART_Receive_DMA(&huart1, usart1_rx_buffer, sizeof(usart1_rx_buffer));
    if (HAL_UART_Transmit(&huart1, (unsigned char *)mesbody, (uint8_t)strlen(mesbody), 500) == HAL_OK)
        printf("%s\n", usart1_rx_buffer);
}

void BC20_SendGPS(void)
{

    BC20_Clear();
    char gpsbody[200];

    if (BC20_SendCmd("AT+CSQ\r\n", "99", 2000) != 1)
    {

        if (BC20_GNSS_GET() == 0)
            return;

        HAL_Delay(200);

        BC20_GPS_Read_Data();
        printf("%f,%f", BC20_GPS_Data.Longitude, BC20_GPS_Data.Latitude);
        sprintf(gpsbody, "AT+QMTPUB=0,0,0,0,\"$sys/451120/wuhu1/dp/post/json\",\"{\"id\": 123,\"dp\":{\"location\":[{\"v\":{\"lon\":%f,\"lat\":%f}}]}}\r\n", BC20_GPS_Data.Longitude, BC20_GPS_Data.Latitude);

        BC20_Clear();
    }
    else
        printf("û���źţ��뵽��������ʹ��");
}

unsigned char BC20_GNSS_GET(void) //��ȡgps����
{

    char cmd1[] = {"AT+QGNSSRD=\"NMEA/GLL\"\r\n"};
    BC20_Clear();

    if (BC20_SendCmd("AT+QGNSSC?\r\n", "1", 1000) != 1)
    {
        while (!BC20_SendCmd("AT+QGNSSC=1\r\n", "OK", 2000))
            ;
    }
    HAL_Delay(500);
    if (BC20_SendCmd("AT+QGNSSRD?\r\n", "99,99", 2000) != 1)
        return 0;
    HAL_UART_Receive_DMA(&huart1, usart1_rx_buffer, sizeof(usart1_rx_buffer));

    HAL_UART_Transmit(&huart1, (uint8_t *)cmd1, strlen(cmd1), 0xffff);
    printf("GPS GET OVER��\r\n");
    return *usart1_rx_buffer;
}

void BC20_GNSS_INIT(void) //��ʼ��gps
{
    BC20_Clear();

    if (!BC20_SendCmd("AT+QGNSSAGPS?\r\n", "1", 500)) //�ж��Ƿ�����AGPS�����û��������
    {
        while (!BC20_SendCmd("AT+QGNSSAGPS=1\r\n", "OK", 250)) //����AGPS����
            printf("�Ѿ�����AGPS���ܣ�\r\n");
    }

    if (!BC20_SendCmd("AT+QGNSSC?\r\n", "1", 250)) //�ж��Ƿ�����gnss�����û��������
    {
        while (!BC20_SendCmd("AT+QGNSSC=1\r\n", "OK", 500))
            printf("GPS��ʼ����ϣ�\r\n");
    }
}

void BC20_RESTART(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_Delay(60);
    printf("Restart Over!\r\n");
}

void BC20_RESET(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_Delay(40);
    printf("Reset Over!\r\n");
}
void BC20_Init(void) //��ʼ��BC20ģ��
{
    printf("BC20��ʼ����...\r\n");

	  printf("BC20����...\r\n");
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_Delay(600);
    printf("BC20�������\r\n");
	
    BC20_RESET();

    while (!BC20_SendCmd("AT\r\n", "OK", 200))
    {
        wnb++;
        if (wnb >= 3)
        {
            wnb = 0;
            BC20_Init();
        }
    }

    while (!BC20_SendCmd("AT+CPSMS=0\r\n", "OK", 150))
        HAL_Delay(50);
    printf("AT+CPSMS Over!\r\n");
    HAL_Delay(50);

    while (!BC20_SendCmd("AT+QMTCFG=\"version\",0,4\r\n", "OK", 200)) //����mqtt�汾Ϊ3.1.1
        HAL_Delay(50);
    printf("Version OVER!\r\n");
    HAL_Delay(50);

    while (!BC20_SendCmd(BC20_MQTT_INFO, "0,0", 3000))
    {
        wnb++;
        if (wnb >= 8)
        {
            wnb = 0;
            BC20_Init();
        }
    }

    printf("MQTT OVER!\r\n");

    while (!BC20_SendCmd(BC20_CONNECT_INFO, "0,0,0", 2000))
    {
        wnb = 0;
        wnb++;
        if (wnb >= 5)
        {
            wnb = 0;
            BC20_Init();
        }
    }

    printf("CONNECT OVER!\r\n");

    BC20flag = 1;
}