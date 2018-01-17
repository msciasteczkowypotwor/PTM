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
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

char a;
char b[2];
int d,e;
int licznik=0;
void USART3_IRQHandler(void)
{
	// sprawdzenie flagi zwiazanej z odebraniem danych przez USART
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		if(licznik==0){
			d=USART3->DR-48;
			licznik++;
		}
		else if(licznik==1){
			a=USART3->DR;
			licznik++;
		}
		else if(licznik==2){
			e=USART3->DR-48;
			licznik=0;
			if(a=='+') d=d+e;
			if(a=='-') d=d-e;
			if(a=='*') d=d*e;




			if(d<10){
				a=d+'0';
				while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
				// wyslanie danych
				USART_SendData(USART3, a);
				// czekaj az dane zostana wyslane
				while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
			}else{
				//b=d;
				itoa(d, b, 10);
				while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
				// wyslanie danych
				USART_SendData(USART3, b[0]);
				// czekaj az dane zostana wyslane
				while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
				while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
				// wyslanie danych
				USART_SendData(USART3, b[1]);
				// czekaj az dane zostana wyslane
				while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
			}



		}

	}


}


int main(void)
{

	// wlaczenie taktowania wybranego portu
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	// wlaczenie taktowania wybranego uk³adu USART
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	// zezwolenie na przerwania od przepe³nienia dla timera 3
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM5, ENABLE);

	// konfiguracja linii Rx i Tx
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// ustawienie funkcji alternatywnej dla pinów (USART)
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

	USART_InitTypeDef USART_InitStructure;
	// predkosc transmisji (mozliwe standardowe opcje: 9600, 19200, 38400, 57600, 115200, ...)
	USART_InitStructure.USART_BaudRate = 9600;
	// d³ugoœæ s³owa (USART_WordLength_8b lub USART_WordLength_9b)
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// liczba bitów stopu (USART_StopBits_1, USART_StopBits_0_5, USART_StopBits_2, USART_StopBits_1_5)
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// sprawdzanie parzystoœci (USART_Parity_No, USART_Parity_Even, USART_Parity_Odd)
	USART_InitStructure.USART_Parity = USART_Parity_No;
	// sprzêtowa kontrola przep³ywu (USART_HardwareFlowControl_None, USART_HardwareFlowControl_RTS, USART_HardwareFlowControl_CTS, USART_HardwareFlowControl_RTS_CTS)
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// tryb nadawania/odbierania (USART_Mode_Rx, USART_Mode_Rx )
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	// konfiguracja
	USART_Init(USART3, &USART_InitStructure);

	// wlaczenie ukladu USART
	USART_Cmd(USART3, ENABLE);


	//struktura do konfiguracji kontrolera NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	// wlaczenie przerwania zwi¹zanego z odebraniem danych (pozostale zrodla przerwan zdefiniowane sa w pliku stm32f4xx_usart.h)
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// konfiguracja kontrolera przerwan
	NVIC_Init(&NVIC_InitStructure);
	// wlaczenie przerwan od ukladu USART
	NVIC_EnableIRQ(USART3_IRQn);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOC, GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2);


	for(;;){




	}
}
