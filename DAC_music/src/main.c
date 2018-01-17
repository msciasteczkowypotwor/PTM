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
#include "audioXmas.h"
			int i=0;
void TIM3_IRQHandler(void)
{
             if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
             {
            	 i++;
            	 if(i==475700)i=0;

            	 DAC_SetChannel1Data(DAC_Align_12b_R, rawAudio[i]);
                    // wyzerowanie flagi wyzwolonego przerwania
                    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
             }
}

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE); // zegar dla portu GPIO z którego wykorzystany zostanie pin jako wyjœcie DAC (PA4)
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE); // zegar dla modu³u DAC

	GPIO_InitTypeDef GPIO_InitStructure;
	//inicjalizacja wyjœcia DAC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	DAC_InitTypeDef DAC_InitStructure;
	//wy³¹czenie zewnêtrznego wyzwalania
	//konwersja mo¿e byæ wyzwalana timerem, stanem wejœcia itd. (szczegó³y w dokumentacji)
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	//nast. 2 linie - wy³¹czamy generator predefiniowanych przebiegów //wyjœciowych (wartoœci zadajemy sami, za pomoc¹ odpowiedniej funkcji)
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	//w³¹czamy buforowanie sygna³u wyjœciowego
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	DAC_Cmd(DAC_Channel_1, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 104;
	TIM_TimeBaseStructure.TIM_Prescaler = 49;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	// ustawienie trybu pracy priorytetów przerwañ
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure;
	// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana³
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
	NVIC_Init(&NVIC_InitStructure);


	// wyczyszczenie przerwania od timera 3 (wyst¹pi³o przy konfiguracji timera)
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	// zezwolenie na przerwania od przepe³nienia dla timera 3
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);



	TIM_Cmd(TIM3, ENABLE);


	for(;;);


}
