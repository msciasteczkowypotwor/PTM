/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
int o=0;
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		TIM_Cmd(TIM3, ENABLE);

		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
void TIM3_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
		{
			if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1))
			{
				GPIO_ResetBits(GPIOC, GPIO_Pin_1);
				GPIO_SetBits(GPIOC, GPIO_Pin_0);
			}
			else{
				GPIO_ResetBits(GPIOC, GPIO_Pin_0);
				GPIO_SetBits(GPIOC, GPIO_Pin_1);
			}


		}
		TIM_Cmd(TIM3, DISABLE);
		TIM_SetCounter(TIM3, 0);
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	}
}
int main(void)
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* Time base configuration */

	TIM_TimeBaseStructure.TIM_Period = 8399;
	TIM_TimeBaseStructure.TIM_Prescaler = 1999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	// uruchom dany kana³
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
	NVIC_Init(&NVIC_InitStructure);


	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);


	// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana³
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
	NVIC_Init(&NVIC_InitStructure);

	EXTI_InitTypeDef EXTI_InitStructure;
	// wybór numeru aktualnie konfigurowanej linii przerwañ
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	// wybór trybu - przerwanie b¹dŸ zdarzenie
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	// wybór zbocza, na które zareaguje przerwanie
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	// uruchom dan¹ liniê przerwañ
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	// zapisz strukturê konfiguracyjn¹ przerwañ zewnêtrznych do rejestrów
	EXTI_Init(&EXTI_InitStructure);

	// pod³¹czenie danego pinu portu do kontrolera przerwañ
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM3, DISABLE);

	GPIO_ResetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_13);
	GPIO_SetBits(GPIOE, GPIO_Pin_14);
	GPIO_ResetBits(GPIOC, GPIO_Pin_1);

	GPIO_SetBits(GPIOC, GPIO_Pin_0);

	for(;;);
}
