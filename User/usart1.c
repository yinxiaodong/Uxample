/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * 文件名  ：usart1.c
 * 描述    ：将printf函数重定向到USART1。这样就可以用printf函数将单片机的数据
 *           打印到PC上的超级终端或串口调试助手。         
 * 实验平台：野火STM32开发板
 * 硬件连接：------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * 库版本  ：ST3.5.0
 * 作者    ：wildfire team 
**********************************************************************************/
#include "stm32f10x.h"
#include <stdio.h>
/* 结构体声明 */
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
/*
 * 函数名：RCC_Config
 * 描述  ：RCC 时钟 配置。
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void RCC_Config(void)
{
	
	/* Enable GPIOA clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/* Enable GPIOB clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/* Enable DMA1 and GPIOC clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	/* Enable AF APB clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	/* Enable USART3 APB clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	/* ADCCLK = PCLK2/6 */
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);//设置ADC时钟（ADCCLK）
	/* Enable ADC1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	/* TIM1 clock enable */
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

}
/*
 * 函数名：GPIO_Config
 * 描述  ：GPIO 配置,工作模式配置。
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void GPIO_Config(void)
{

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	//电源
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	//LED
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_2);
}
/*
 * 函数名：LED_Spark
 * 描述  ：LED_Spark 翻转,工作模式配置。
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void LED_Spark(void)
{

	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_ResetBits(GPIOB, GPIO_Pin_2);
	Delay_1ms(5);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOB, GPIO_Pin_2);
	Delay_1ms(5);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_ResetBits(GPIOB, GPIO_Pin_2);
	Delay_1ms(1);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOB, GPIO_Pin_2);
	Delay_1ms(1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_ResetBits(GPIOB, GPIO_Pin_2);
	Delay_1ms(1);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOB, GPIO_Pin_2);
	
}
/*
 * 函数名：EXTI1_Config
 * 描述  ：EXTI1 GPIO 配置,工作模式配置。
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void EXTI1_Config(void)
{
	//KEY
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Connect EXTI Line0 to PA1 pin */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
	/* Configure EXTI Line0 and its interrupt to the lowest priority*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/*
 * 函数名：USART3_Config
 * 描述  ：USART3 GPIO 配置,工作模式配置。115200 8-N-1
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void USART3_Config(void)
{	
	/* USART1 GPIO config */
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);
}


/*
 * 函数名：fputc
 * 描述  ：重定向c库函数printf到USART1
 * 输入  ：无
 * 输出  ：无
 * 调用  ：由printf调用
 */
int fputc(int ch, FILE *f)
{
	/* 将Printf内容发往串口 */
	USART_SendData(USART3, (unsigned char) ch);
    //while (!(USART3->SR & USART_FLAG_TXE));
	while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);	
	return (ch);
}

