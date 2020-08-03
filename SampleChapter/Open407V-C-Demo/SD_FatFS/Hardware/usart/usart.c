#include "usart.h"
/*******************************************************************************************************************************
 * ��������USART1_Conf()
 * ��������
 *����ֵ����
 * ���ܣ�����USART1������ʼ��
********************************************************************************************************************************/																		
void USART1_Conf(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;                                          //����GPIO��ʼ���ṹ��
	USART_InitTypeDef USART_InitStructure;                                        //����USART��ʼ���ṹ��
	   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOB, ENABLE);		
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART3);						  //����PA2�������ӵ�USART2
	/*���ø��ùܽ�TXD(PA2)��RXD(PA3)���ӵ�USART1*/
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART3);					  //����PA3�������ӵ�USART2
		/*����USART1��Ӧ��ʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);                          //ʹ��GPIOA��AHB1ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);                        //ʹ��USART2��APB2ʱ��
	/*����USART1�ķ��͹ܽ�TXD(PA2)Ϊ�����������*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;                                       //���ó�ʼ��GPIOΪPIN2
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;                               //����GPIO���ٶ�Ϊ50MHz
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;                                    //����GPIOģʽΪ����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;								  //����GPIO�������Ϊ�������
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;						          //����GPIOΪ������������
	GPIO_Init(GPIOA,&GPIO_InitStructure);                                         //��ʼ��GPIOA��PIN2
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;                                      //���ó�ʼ��GPIOΪPIN3
	/*����USART1�Ľ��չܽ�RXD(PA3)Ϊ��������*/
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;                                    //����GPIO��ģʽΪ����ģʽ
	GPIO_Init(GPIOA,&GPIO_InitStructure);                                         //��ʼ��GPIOA��PIN3

	/*����USART1��ģʽ*/
    USART_InitStructure.USART_BaudRate=115200;                                    //����USART�Ĳ�����Ϊ115200
    USART_InitStructure.USART_Parity=USART_Parity_No;                             //����USART��У��λΪNone
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;                     //����USART������λΪ8bit
    USART_InitStructure.USART_StopBits=USART_StopBits_1;                          //����USART��ֹͣλΪ1
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //ʧ��Ӳ��������
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;                   //����USART��ģʽΪ���ͽ���ģʽ
    USART_Init(USART2,&USART_InitStructure);                                      //��ʼ��USART1
    USART_Cmd(USART2,ENABLE);                                                     //ʹ��USART1
}


/********************************************************************************************************************************
*��������fputc()
* ������int ch��FILE *f
* ����ֵ��int
* ���ܣ����¶���stdio.h�е�fputc()������ʹprintf()�����USART1
*********************************************************************************************************************************/
int fputc(int ch,FILE *f)
{
  USART_SendData(USART2,(u8)ch);	                                                   //��ch��USART1���ͳ�ȥ
  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)				       //�ȴ��������
  {
  }											  
  return ch;																	   //���� ch
}																		           








