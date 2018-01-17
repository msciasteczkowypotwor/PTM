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
unsigned int counter;
void zad2(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //pod³¹cza zegar do szyny zegarowej

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* Time base configuration */

	TIM_TimeBaseStructure.TIM_Period = 4999;
	TIM_TimeBaseStructure.TIM_Prescaler = 9999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	TIM_Cmd(TIM3, ENABLE);





	for(;;){
		if(TIM_GetFlagStatus(TIM3, TIM_FLAG_Update))
		{
			if(GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_12)==1)
			{
				GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
			}else{
				GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
			}
			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		}

	}
}
void zad3(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //pod³¹cza zegar do szyny zegarowej

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* Time base configuration */

	TIM_TimeBaseStructure.TIM_Period = 4999;
	TIM_TimeBaseStructure.TIM_Prescaler = 9999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_Cmd(TIM3, ENABLE);


	GPIO_SetBits(GPIOA, GPIO_Pin_1);


	for(;;){
		if(TIM_GetFlagStatus(TIM3, TIM_FLAG_Update))
		{
			if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2)==1)
			{
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
			}else{
				GPIO_SetBits(GPIOA, GPIO_Pin_2);
			}
			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		}

	}
}
void zad4(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //pod³¹cza zegar do szyny zegarowej

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* Time base configuration */

	TIM_TimeBaseStructure.TIM_Period = 9999;
	TIM_TimeBaseStructure.TIM_Prescaler = 4999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	TIM_Cmd(TIM3, ENABLE);





	for(;;){
		counter = TIM3->CNT;

		if(counter>=5000){
			GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
		}
		if(counter>=8000){
			GPIO_SetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_15);
		}

		if(TIM_GetFlagStatus(TIM3, TIM_FLAG_Update))
		{

			GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		}

	}
}
void zad5(){
	//pc0-a,pc1-b...pc7-h,pa1-1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //pod³¹cza zegar do szyny zegarowej

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* Time base configuration */

	TIM_TimeBaseStructure.TIM_Period = 4999;
	TIM_TimeBaseStructure.TIM_Prescaler = 4999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2|
			GPIO_Pin_3| GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	TIM_Cmd(TIM3, ENABLE);

	GPIO_SetBits(GPIOC, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);

	int aa=0;

	for(;;){
		if(TIM_GetFlagStatus(TIM3, TIM_FLAG_Update))
		{
			switch(aa)
			{
			case 0:
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
				GPIO_SetBits(GPIOA, GPIO_Pin_6);
				aa++;
				break;
			case 1:
				GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
				aa++;
				break;
			case 2:
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6);
				GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_5);
				aa++;
				break;
			case 3:
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6);
				GPIO_SetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5);
				aa++;
				break;
			case 4:
				GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6);
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4);
				aa++;
				break;
			case 5:
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6);
				GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_4);
				aa++;
				break;
			case 6:
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
				GPIO_SetBits(GPIOA, GPIO_Pin_1);
				aa++;
				break;
			case 7:
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
				GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
				aa++;
				break;
			case 8:
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
				aa++;
				break;
			case 9:
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6);
				GPIO_SetBits(GPIOA, GPIO_Pin_4);
				aa=0;
				break;
			}

			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		}



	}
}

int main(void)
{
zad5();

}
