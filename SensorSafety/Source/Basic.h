
#ifndef __BASIC_H__
#define __BASIC_H__

#include <iocc2530.h>

//��������������
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned int uint16;
typedef unsigned char uint8;

//LED_D8_D9 ����
#define SET_LED_D8 (P2 &= 0XFE)  //����LED_D8
#define SET_LED_D9 (P1 &= 0XFD)  //����LED_D9
#define CLR_LED_D8 (P2 |= 0X01)  //Ϩ��LED_D8
#define CLR_LED_D9 (P1 |= 0X02)  //Ϩ��LED_D9

#define LED_D8_TURN (P2 ^= 0X01)  //�ı�LED_D8״̬���������������
#define LED_D9_TURN (P1 ^= 0X02)  //�ı�LED_D9״̬���������������

//΢�뼶������ʱ����
void delay(uint);
//Լ10ms��ʱ����
void Delay(uint n);

//LED_D8_D9 �˿ڳ�ʼ������
void LEDPortInit(void);

//ADCͨ��0��8����λ��ȡ����
uint8 GetCh08bitADC(void);

//���ö˿�Ϊ��̬����
void SetIOInput(uint8 group, uint8 bit);
//���ö˿�Ϊͨ�����IO��
void SetIOOutput(uint8 group, uint8 bit);
//��ȡIO�������ƽ״̬
uint8 GetIOLevel(uint8 group, uint8 bit);
//����IO�˿������ƽ״̬
void SetIOLevel(uint8 group, uint8 bit, uint8 value);


#endif//__BASIC_H__