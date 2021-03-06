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
#include <math.h>
#include "sin.h"

double ADC_Result;
double wartosc;
int sinus=0;
double dodatkowa;
double volt;


void TIM3_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		sinus++;
		sinus++;
		if(sinus>=3601)sinus=0;

		dodatkowa = sineWave[sinus];
		wartosc = dodatkowa*2047+2047;

		DAC_SetChannel1Data(DAC_Align_12b_R, wartosc);
		// wyzerowanie flagi wyzwolonego przerwania
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}
int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE); // zegar dla portu GPIO z kt�rego wykorzystany zostanie pin jako wyj�cie DAC (PA4)
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	//inicjalizacja wyj�cia DAC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	DAC_InitTypeDef DAC_InitStructure;
	//wy��czenie zewn�trznego wyzwalania
	//konwersja mo�e by� wyzwalana timerem, stanem wej�cia itd. (szczeg�y w dokumentacji)
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	//nast. 2 linie - wy��czamy generator predefiniowanych przebieg�w //wyj�ciowych (warto�ci zadajemy sami, za pomoc� odpowiedniej funkcji)
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	//w��czamy buforowanie sygna�u wyj�ciowego
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);



	ADC_InitTypeDef ADC_InitStructure;
	//ustawienie rozdzielczo�ci przetwornika na maksymaln� (12 bit�w)
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	//wy��czenie trybu skanowania (odczytywa� b�dziemy jedno wej�cie ADC
	//w trybie skanowania automatycznie wykonywana jest konwersja na wielu //wej�ciach/kana�ach)
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	//w��czenie ci�g�ego trybu pracy
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	//wy��czenie zewn�trznego wyzwalania
	//konwersja mo�e by� wyzwalana timerem, stanem wej�cia itd. (szczeg�y w //dokumentacji)
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//warto�� binarna wyniku b�dzie podawana z wyr�wnaniem do prawej
	//funkcja do odczytu stanu przetwornika ADC zwraca warto�� 16-bitow�
	//dla przyk�adu, warto�� 0xFF wyr�wnana w prawo to 0x00FF, w lewo 0x0FF0
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//liczba konwersji r�wna 1, bo 1 kana�
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	// zapisz wype�nion� struktur� do rejestr�w przetwornika numer 1
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* Time base configuration */

	TIM_TimeBaseStructure.TIM_Period = 200;
	TIM_TimeBaseStructure.TIM_Prescaler = 800;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	// priorytet g��wny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype�nion� struktur� do rejestr�w
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM3, ENABLE);


	DAC_Cmd(DAC_Channel_1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);



	for(;;){
		ADC_SoftwareStartConv(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
		ADC_Result = ADC_GetConversionValue(ADC1);
		volt=ADC_Result*2.95/4095;

		if(ADC_Result>=500){
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
		}else{
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		}
		if(ADC_Result>=1500){
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
		}else{
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		}
		if(ADC_Result>=2500){
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
		}else{
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		}
		if(ADC_Result>=3500){
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
		}else{
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		}
	}
}
