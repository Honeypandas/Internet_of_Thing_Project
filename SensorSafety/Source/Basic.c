
#include "Basic.h"

/***********************************************************
**  ��������: delay
**  ʵ�ֹ���: ΢�뼶������ʱ����
**  ��ڲ���: n:��ʱֵ;
**  ���ؽ��: None
***********************************************************/
void delay(uint n)
{
  uint i;
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
}

/***********************************************************
**  ��������: Delay
**  ʵ�ֹ���: Լ 10_ms ��ʱ����
**  ��ڲ���: n:��Ҫ��ʱ�� 10ms ��;
**  ���ؽ��: None
***********************************************************/
void Delay(uint n)
{
  uint i,j,k;
  for(i=0;i<n;i++)
    for(j=0;j<100;j++)
      for(k=0;k<100;k++)
        ;
}

/***********************************************************
**  ��������: LEDPortInit
**  ʵ�ֹ���: ��ʼ�� LED_D8_D9(P2_0.P1_1)
**  ��ڲ���: None
**  ���ؽ��: None
***********************************************************/
void LEDPortInit(void)
{
  P1SEL &= ~0X02;
  P2SEL &= ~0X01;

  P1DIR |= 0X02;
  P2DIR |= 0X01;

  CLR_LED_D8;
  CLR_LED_D9;
}

/***********************************************************
**  ��������: GetCh08bitADC
**  ʵ�ֹ���: ��ȡ ADC ͨ��0 ��8λ ADC ����ֵ
**  ��ڲ���: None
**  ���ؽ��: 1 Byte ADCֵ
***********************************************************/
uint8 GetCh08bitADC(void)
{
    uint8 v = 0;
    ADCCFG = 0x01;
    ADCCON1 = 0x33;
    ADCCON2 = 0xB0;
    ADCCON1 |= 0x40;
    while(!(ADCCON1 & 0x80));
    v = ADCL;
    v = ADCH;
    return(v);
}

/***********************************************************
**  ��������: SetIOInput
**  ʵ�ֹ���: ���ö˿�Ϊ��̬����(�������ڲ�����������)
**  ��ڲ���: group:Port
**            bit:Bit in Port
**  ���ؽ��: None
***********************************************************/
// pull: 0 - disable, 1 - pulldown, 2 - pullup
void SetIOInput(uint8 group, uint8 bit)
{
   switch(group)
   {
   case 0: P0DIR &= ~(1 << bit); P0SEL &= ~(1 << bit); P0INP |=(1 << bit); break;
   case 1: P1DIR &= ~(1 << bit); P1SEL &= ~(1 << bit); P1INP |=(1 << bit); break;
   case 2: P2DIR &= ~(1 << bit); P2SEL &= ~(1 << bit); P2INP |=(1 << bit); break;
   }
}

/***********************************************************
**  ��������: SetIOOutput
**  ʵ�ֹ���: ���ö˿�Ϊͨ�����IO��
**  ��ڲ���: group:Port
**            bit:Bit in Port
**  ���ؽ��: None
***********************************************************/
void SetIOOutput(uint8 group, uint8 bit)
{
   switch(group)
   {
   case 0: P0DIR |= (1 << bit); P0SEL &= ~(1 << bit); break;
   case 1: P1DIR |= (1 << bit); P1SEL &= ~(1 << bit); break;
   case 2: P2DIR |= (1 << bit); P2SEL &= ~(1 << bit); break;
   }
}

/***********************************************************
**  ��������: GetIOLevel
**  ʵ�ֹ���: ��ȡ��Ӧ�˿��ϵ������ƽ
**  ��ڲ���: group:Port
**            bit:Bit in Port
**  ���ؽ��:  1 Byte(1 :����Ϊ�ߵ�ƽ; 0 :����Ϊ�͵�ƽ;)
***********************************************************/
uint8 GetIOLevel(uint8 group, uint8 bit)
{
    switch(group)
    {
    case 0: return !!(P0 & (1 << bit));
    case 1: return !!(P1 & (1 << bit));
    case 2: return !!(P2 & (1 << bit));
    }
    return 0;
}

/***********************************************************
**  ��������: SetIOLevel
**  ʵ�ֹ���: ����IO�������ƽ
**  ��ڲ���: group:Port
**            bit:Bit in Port
**            value:(1 :����ߵ�ƽ; 0 :����͵�ƽ;)
**  ���ؽ��: None
***********************************************************/
void SetIOLevel(uint8 group, uint8 bit, uint8 value)
{
    switch(group)
    {
    case 0:
        if(value)
          P0 |= (1 << bit);
        else
          P0 &=~(1 << bit);
        break;
    case 1:
        if(value)
          P1 |= (1 << bit);
        else
          P1 &=~(1 << bit);
        break;
    case 2:
        if(value)
          P2 |= (1 << bit);
        else
          P2 &=~(1 << bit);
        break;
    }
}