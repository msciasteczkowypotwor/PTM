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
int a=0,b,c;
int counter;
//GPIO=======================================================================================================
void GPIO_out(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
void GPIO_out_on_off(){
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	for (int i=0;i<10000000;i++);
	GPIO_SetBits(GPIOD, GPIO_Pin_13);
	for (int i=0;i<10000000;i++);
	GPIO_SetBits(GPIOD, GPIO_Pin_14);
	for (int i=0;i<10000000;i++);
	GPIO_SetBits(GPIOD, GPIO_Pin_15);
	for (int i=0;i<10000000;i++);


	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	for (int i=0;i<10000000;i++);
	GPIO_ResetBits(GPIOD, GPIO_Pin_13);
	for (int i=0;i<10000000;i++);
	GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	for (int i=0;i<10000000;i++);
	GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	for (int i=0;i<10000000;i++);
}
void GPIO_in_up(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //wejscie
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void GPIO_read_imput_data(){
	if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	}
	if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2))
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
	}
	else
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
	}
	if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
	}
	else
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	}
}
void GPIO_zapalenie_gaszenie_jednym_przyciskiem(){

	if(a==0 && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		a = 1;
		for(int i=0; i<5000000;i++);
	}

	if(a==1 && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		a = 0;
		for(int i=0; i<5000000;i++);
	}

	if(b==0 && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2))
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		b = 1;
		for(int i=0; i<5000000;i++);
	}

	if(b==1 && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2))
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		b = 0;
		for(int i=0; i<5000000;i++);
	}

	if(c==0 && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		c = 1;
		for(int i=0; i<5000000;i++);
	}

	if(c==1 && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		c = 0;
		for(int i=0; i<5000000;i++);
	}



}
void GPIO_zapalanie_kolejnych_jednym_przyciskiem(){
	if(a==0 && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		a = 1;
		for(int i=0; i<5000000;i++);
	}

	if(a==1 && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		a = 2;
		for(int i=0; i<5000000;i++);
	}

	if(a==2 && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		a = 3;
		for(int i=0; i<5000000;i++);
	}

	if(a==3 && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		a = 4;
		for(int i=0; i<5000000;i++);
	}

	if(a==4 && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		a = 0;
		for(int i=0; i<5000000;i++);
	}


}
void GPIO_przytrzymanie_zapala_kolejne(){

	if(a==0 &&  !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		for(int i=0; i<10000000;i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		a = 1;
		for(int i=0; i<10000000;i++);
	}
	if(a==1  &&!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		for(int i=0; i<10000000;i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		a = 2;
		for(int i=0; i<10000000;i++);
	}
	if(a==2  &&!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		for(int i=0; i<10000000;i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		a = 3;
		for(int i=0; i<10000000;i++);
	}
	if(a==3  && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		for(int i=0; i<10000000;i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		a = 4;
		for(int i=0; i<10000000;i++);
	}
	if(a!=0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1));

		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		a = 0;
		for(int i=0; i<5000000;i++);
	}
}
//TIM========================================================================================================
void TIM_set(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 9999;
	TIM_TimeBaseStructure.TIM_Prescaler = 4999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM3, ENABLE);
}
void TIM_spr_tim_in_if(){
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
void TIM_odczytanie_wartosci_period(){
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
//PWM========================================================================================================
void PWM_TIM_set_GPIO_out(){
	//nic w forze
	//diody do pwm
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 9999;
	TIM_TimeBaseStructure.TIM_Prescaler = 8399;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_OCInitTypeDef TIM_OCInitStructure;
	/* PWM1 Mode configuration: */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);


	TIM4->CCR1 = 5000;
	TIM4->CCR2 = 2000;

	TIM_Cmd(TIM4, ENABLE);

}
void PWM_TIM_set_GPIO_out_jasnosc_diod(){
	//w forze nast�pna funkcja
	//DIODY
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);



	//TIMER1
	/* GPIOD Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 99;
	TIM_TimeBaseStructure.TIM_Prescaler = 839;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_OCInitTypeDef TIM_OCInitStructure;
	/* PWM1 Mode configuration: */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);


	TIM4->CCR1 = 0;
	TIM4->CCR2 = 0;
	TIM4->CCR3 = 0;
	TIM4->CCR4 = 0;

	TIM_Cmd(TIM4, ENABLE);

}
void PWM_narastajaca_jasnosc_diod(){
	//w forze
	for(int i = 0;i<=100000;i++);

	if(TIM4->CCR1==99) TIM4->CCR1=0;
	TIM4->CCR1++;
	if(TIM4->CCR2==99) TIM4->CCR2=0;
	TIM4->CCR2++;
	if(TIM4->CCR3==99) TIM4->CCR3=0;
	TIM4->CCR3++;
	if(TIM4->CCR4==99) TIM4->CCR4=0;
	TIM4->CCR4++;
}
//PWM podzielone============================================================================================
void PWM_piny_wyjscie_set(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

		/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);

}
void PWM_set_tim_bez_diod(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

		TIM_TimeBaseStructure.TIM_Period = 99;
		TIM_TimeBaseStructure.TIM_Prescaler = 839;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

		TIM_OCInitTypeDef TIM_OCInitStructure;
		/* PWM1 Mode configuration: */
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

		TIM_OC1Init(TIM4, &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);


		TIM4->CCR1 = 10;
		TIM4->CCR2 = 40;
		TIM4->CCR3 = 60;     //jasnosc bo zegar szybko chodzi
		TIM4->CCR4 = 99;

		TIM_Cmd(TIM4, ENABLE);

}
//NVIC=========================================================================================================

int main(void)
{

	for(;;){

	}
}
