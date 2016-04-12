/* Includes ------------------------------------------------------------------*/
#include "delay.h"
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;

/*
 * ��������void SysTick_Configuration(void)
 * ����  ���δ�ʱ����������
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void SysTick_Configuration(void)
{
    /* Setup SysTick Timer for 1000Hz interrupts */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */
        while (1);
    }
    /* Configure the SysTick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00);
}

/**
* @brief  Insert a delay time.
* @param  nTime: specifies the delay time length, in milliseconds.
* @retval None
*/
void Delay_1ms(uint32_t nTime)
{
    TimingDelay = nTime;
    while(TimingDelay != 0);
}

/**
* @brief  Decrement the TimingDelay variable.
* @param  None.
* @retval None
*/
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}


