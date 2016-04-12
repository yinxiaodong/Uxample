#ifndef __USART1_H
#define	__USART1_H
/* Exported functions ------------------------------------------------------- */
void RCC_Config(void);
void GPIO_Config(void);
void EXTI1_Config(void);
void EXTI5_7_Config(void);
void ADC_Config(void);
void LED_Spark(void);
void USART3_Config(void);
int fputc(int ch, FILE *f);
#endif /* __USART1_H */
