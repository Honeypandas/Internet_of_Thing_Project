#include "UART.h"

/***********************************************************
**  ��������: UART0_Init
**  ʵ�ֹ���: ��ʼ�� UART0
**  ��ڲ���: baud:����������;
**  ���ؽ��: None
***********************************************************/
void UART0_Init(BaudSel baud)
{
  CLKCONCMD &= ~0X40;             //����
  while(!(SLEEPSTA & 0X40))
    ;                             //�ȴ������ȶ�
  CLKCONCMD &= ~0X47;             //TICHSPD128��Ƶ��CLKSPD����Ƶ
  SLEEPCMD |= 0X04; 		  //�رղ��õ�RC����

  PERCFG = 0X00;		  //λ��1 P0��
  P0SEL |= 0X0C;		  //P0��������

  U0CSR |= 0X80;		  //UART��ʽ
  switch(baud)
  {
    case BAUD_2400:      U0GCR |= 6;     U0BAUD |= 59;    break;
    case BAUD_4800:      U0GCR |= 7;     U0BAUD |= 59;    break;
    case BAUD_9600:      U0GCR |= 8;     U0BAUD |= 59;    break;
    case BAUD_14400:     U0GCR |= 8;     U0BAUD |= 216;   break;
    case BAUD_19200:     U0GCR |= 9;     U0BAUD |= 59;    break;
    case BAUD_28800:     U0GCR |= 9;     U0BAUD |= 216;   break;
    case BAUD_38400:     U0GCR |= 10;    U0BAUD |= 59;    break;
    case BAUD_57600:     U0GCR |= 10;    U0BAUD |= 216;   break;
    case BAUD_76800:     U0GCR |= 11;    U0BAUD |= 59;    break;
    case BAUD_115200:    U0GCR |= 11;    U0BAUD |= 216;   break;
    case BAUD_230400:    U0GCR |= 12;    U0BAUD |= 216;   break;
    default         :    U0GCR |= 11;    U0BAUD |= 216;   break; //BAUD_115200;
  }

  UTX0IF = 0;
  U0CSR |= 0X40;		  //�������
  IEN0 |= 0X84;			  //�����жϣ������ж�

}

/***********************************************************
**  ��������: UART0_Send
**  ʵ�ֹ���: UART0 ��������
**  ��ڲ���: Data:�������������׵�ַ
**            len:���������ݵ��ֽ���
**  ���ؽ��: None
***********************************************************/
void UART0_Send(char *Data,int len)
{
  int i;
  for(i=0;i<len;i++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0)
      ;
    UTX0IF = 0;
  }
}
/***********************************************************
**  ��������: UART0_Dis_uNum
**  ʵ�ֹ���: UART0 ��ʮ���Ʒ�ʽ��ʾ uint16 ������
**  ��ڲ���: uValue:��Ҫ��ʾ���޷���������
**  ���ؽ��: None
***********************************************************/
void UART0_Dis_uNum(uint16 uValue )
{
  uint8 i;
  char cData[5] = {'0','0','0','0','0'};

  cData[0] = uValue % 100000 / 10000 + '0';
  cData[1] = uValue % 10000 / 1000 + '0';
  cData[2] = uValue % 1000 / 100 + '0';
  cData[3] = uValue % 100 / 10 + '0';
  cData[4] = uValue % 10 / 1 + '0';
  if(0 != uValue )
  {
    for( i=0; i<5; i++)
    {
      if('0' != cData[i] )
        break;
      if('0' == cData[i] )
        cData[i] = ' ';
    }
  }
  else if(0 == uValue )
  {
    for( i=0; i<4; i++)
    {
        cData[i] = ' ';
    }
  }
  //���ֺ������������ǰ����һ���ո���
  UART0_Send(" ", 1);
  UART0_Send(cData, 5);
  UART0_Send(" ", 1);
}

/***********************************************************
**  ��������: UART0_Dis_fNum
**  ʵ�ֹ���: UART0 ��ʮ���Ʒ�ʽ��ʾ float ������
**  ��ڲ���: fValue:��Ҫ��ʾ�ĸ���������
**  ���ؽ��: None
***********************************************************/
void UART0_Dis_fNum(float fValue )
{
  uint16 uValue = (uint16)( 100 * fValue );
  char cData[5] = {'0','0','.','0','0'};

  cData[0] = uValue % 10000 / 1000 + '0';
  cData[1] = uValue % 1000 / 100 + '0';
  cData[2] = '.';
  cData[3] = uValue % 100 / 10 + '0';
  cData[4] = uValue % 10 / 1 + '0';

  //���ֺ������������ǰ����һ���ո���
  UART0_Send(" ", 1);
  UART0_Send(cData, 5);
  UART0_Send(" ", 1);
}

/***********************************************************
**  ��������: UART0_ISR
**  ʵ�ֹ���: UART0 �����жϴ�����
**  ��ڲ���: None
**  ���ؽ��: None
***********************************************************/
#pragma vector = URX0_VECTOR
 __interrupt void UART0_ISR(void)
 {
//    static char temp[1];
//    temp[0] = U0DBUF;
//    UART0_Send(temp, 1);
    URX0IF = 0;				//���жϱ�־
 }
