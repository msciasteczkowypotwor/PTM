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
void a0()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
}
void a1(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
}
void a2(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_5);
}
void a3(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5);
}
void a4(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4);
}
void a5(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_4);
}
void a6(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}
void a7(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
}
void a8(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
}
void a9(){

	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
}

int a=0,c=0,b=0,d=0;
int o = 0;
void liczba(int x){
	switch(x)
	{
	case 0:
		a0();
		break;
	case 1:
		a1();
		break;
	case 2:
		a2();
		break;
	case 3:
		a3();
		break;
	case 4:
		a4();
		break;
	case 5:
		a5();
		break;
	case 6:
		a6();
		break;
	case 7:
		a7();
		break;
	case 8:
		a8();
		break;
	case 9:
		a9();
		break;
	}

}
void TIM2_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		b++;
		if(b==10)b=0;
		// wyzerowanie flagi wyzwolonego przerwania
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
void TIM3_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		a++;
		if(a==10)a=0;
		// wyzerowanie flagi wyzwolonego przerwania
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}
void TIM5_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		c++;
		if(c==10)c=0;
		// wyzerowanie flagi wyzwolonego przerwania
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}
void TIM7_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
	{
		d++;
		if(d==10)d=0;
		// wyzerowanie flagi wyzwolonego przerwania
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	}
}

void TIM4_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		switch(o)
		{
		case 0:
			GPIO_ResetBits(GPIOC, GPIO_Pin_3);
			liczba(a);
			GPIO_SetBits(GPIOC, GPIO_Pin_0);
			o++;
			break;
		case 1:
			GPIO_ResetBits(GPIOC, GPIO_Pin_0);
			liczba(b);
			GPIO_SetBits(GPIOC, GPIO_Pin_1);
			o++;
			break;
		case 2:
			GPIO_ResetBits(GPIOC, GPIO_Pin_1);
			liczba(c);
			GPIO_SetBits(GPIOC, GPIO_Pin_2);
			o++;
			break;
		case 3:
			GPIO_ResetBits(GPIOC, GPIO_Pin_2);
			liczba(d);
			GPIO_SetBits(GPIOC, GPIO_Pin_3);
			o=0;
			break;

		}
		// wyzerowanie flagi wyzwolonego przerwania
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);


	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* Time base configuration */

	TIM_TimeBaseStructure.TIM_Period = 16799;
	TIM_TimeBaseStructure.TIM_Prescaler = 49999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Period = 8399;
	TIM_TimeBaseStructure.TIM_Prescaler = 9999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Period = 8399;
	TIM_TimeBaseStructure.TIM_Prescaler = 999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Period = 8399;
	TIM_TimeBaseStructure.TIM_Prescaler = 99;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Period = 209;
	TIM_TimeBaseStructure.TIM_Prescaler = 999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana³
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana³
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana³
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana³
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
	NVIC_Init(&NVIC_InitStructure);

	// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	// uruchom dany kana³
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);


	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM5, ENABLE);
	TIM_Cmd(TIM6, ENABLE);


	GPIO_SetBits(GPIOA, GPIO_Pin_7);



	for(;;);
}
