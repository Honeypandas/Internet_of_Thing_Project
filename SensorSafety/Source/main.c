
#include "Basic.h"
#include "UART.h"


void main(void)
{
  uint8 SensorValue;
  //LED �ƣ�D8 D9���˿ڳ�ʼ��
  LEDPortInit();

  //UART0 ��ʼ��
  UART0_Init( BAUD_115200 );

  //�������˿�(P1_0)��ʼ��
  SetIOInput(1,0);

  for( ; ; )
  {
    //��ȡ������ֵ
    SensorValue = GetIOLevel( 1, 0 );
    //��ʾ���
    UART0_Send( "Safety Sensor:", sizeof("Safety Sensor:")-1 );
    UART0_Dis_uNum(SensorValue);
    if(0 == SensorValue)
      UART0_Send( "NoBody Nearby", sizeof("NoBody Nearby")-1 );
    else if(1 == SensorValue)
    {
      UART0_Send( "Someone Nearby!", sizeof("Someone Nearby!")-1 );
      for(int i=0;i<4;i++){
    SET_LED_D9;
    Delay(20);
    CLR_LED_D9;
    Delay(20);
      }
    }
    UART0_Send( "\r\n", sizeof("\r\n")-1 );

    //����ʱLED ָʾ����˸
    SET_LED_D8;
    Delay(5);
    CLR_LED_D8;
    Delay(120);
  }
}
