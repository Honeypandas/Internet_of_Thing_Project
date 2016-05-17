
#include "Basic.h"
#include "UART.h"


void main(void)
{
  uint8 SensorValue;
  //LED 灯（D8 D9）端口初始化
  LEDPortInit();

  //UART0 初始化
  UART0_Init( BAUD_115200 );

  //传感器端口(P1_0)初始化
  SetIOInput(1,0);

  for( ; ; )
  {
    //读取传感器值
    SensorValue = GetIOLevel( 1, 0 );
    //显示结果
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

    //运行时LED 指示灯闪烁
    SET_LED_D8;
    Delay(5);
    CLR_LED_D8;
    Delay(120);
  }
}
