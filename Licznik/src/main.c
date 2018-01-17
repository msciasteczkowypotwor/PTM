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
void swicz(int z){
	switch(z)
	{
	case 0: a0();
	break;
	case 1: a1();
	break;
	case 2: a2();
	break;
	case 3: a3();
	break;
	case 4: a4();
	break;
	case 5: a5();
	break;
	case 6: a6();
	break;
	case 7: a7();
	break;
	case 8: a8();
	break;
	case 9: a9();
	break;
	}
}

int main(void)
{

	//pc0-a,pc1-b...pc7-h,pa1-1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //pod³¹cza zegar do szyny zegarowej

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* Time base configuration */

	TIM_TimeBaseStructure.TIM_Period = 8399;
	TIM_TimeBaseStructure.TIM_Prescaler = 9999;
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
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	TIM_Cmd(TIM3, ENABLE);

	GPIO_SetBits(GPIOC, GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2|GPIO_Pin_3);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);

	int a=9,b=9,c=9,d=9;


	for(;;){
		if(TIM_GetFlagStatus(TIM3, TIM_FLAG_Update))
		{
			d--;
			if(d==-1){
				d=9;
				c--;
			}
			if(c==-1){
				c=9;
				b--;
			}
			if(b==-1){
				b=9;
				a--;
			}
			if(a==-1){
				a=9;
			}

			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		}

		swicz(a);
		GPIO_SetBits(GPIOC, GPIO_Pin_0);
		for(int i=0 ; i<1000 ;i++);
		GPIO_ResetBits(GPIOC, GPIO_Pin_0);

		//
		swicz(b);
		GPIO_SetBits(GPIOC, GPIO_Pin_1);
		for(int i=0 ; i<1000 ;i++);
		GPIO_ResetBits(GPIOC, GPIO_Pin_1);

		//for(int i=0 ; i<100 ;i++);
		swicz(c);
		GPIO_SetBits(GPIOC, GPIO_Pin_2);
		for(int i=0 ; i<1000 ;i++);
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);

		//for(int i=0 ; i<100 ;i++);
		swicz(d);
		GPIO_SetBits(GPIOC, GPIO_Pin_3);
		for(int i=0 ; i<1000 ;i++);
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);
		//for(int i=0 ; i<100 ;i++);



	}

}
