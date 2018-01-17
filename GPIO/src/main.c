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

void zad1(){
	int i;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);





	for(;;){
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		for (i=0;i<10000000;i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		for (i=0;i<10000000;i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		for (i=0;i<10000000;i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		for (i=0;i<10000000;i++);


		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		for (i=0;i<10000000;i++);
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		for (i=0;i<10000000;i++);
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		for (i=0;i<10000000;i++);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		for (i=0;i<10000000;i++);


	}
}
void zad2(){
	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //wejscie
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);



	for(;;){
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
}
void zad3(){
	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //wejscie
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	int a=0,b=0,c=0;


	for(;;){


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
}
void zad4(){
	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //wejscie
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	int a=0;

	for(;;){


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
}
void zad5(){
	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //wejscie
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	int a=0;

	for(;;){


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
}
int main(void)
{
	zad1();
	//zad2();
	//zad3();
	//zad4();
	//zad5();

}
