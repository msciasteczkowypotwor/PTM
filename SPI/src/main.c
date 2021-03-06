#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "tm_stm32f4_lis302dl_lis3dsh.h"

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

	TIM_TimeBaseStructure.TIM_Period = 18000;
	TIM_TimeBaseStructure.TIM_Prescaler = 2;
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
	TIM4->CCR4 = 0;
	TIM_Cmd(TIM4, ENABLE);

}

int x,y,z;
int main(void)
{
	PWM_piny_wyjscie_set();
	PWM_set_tim_bez_diod();
	typedef enum {
		TM_LIS302DL_LIS3DSH_Device_Error,
		TM_LIS302DL_LIS3DSH_Device_LIS302DL,
		TM_LIS302DL_LIS3DSH_Device_LIS3DSH
	} TM_LIS302DL_LIS3DSH_Device_t;



	TM_LIS302DL_LIS3DSH_Device_t IMU_Type;
	IMU_Type = TM_LIS302DL_LIS3DSH_Detect();


	TM_LIS302DL_LIS3DSH_t Axes_Data;


	TM_LIS302DL_LIS3DSH_Init(TM_LIS3DSH_Sensitivity_2G, TM_LIS3DSH_Filter_800Hz);



	for(;;){

		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);
		x = Axes_Data.X;
		y = Axes_Data.Y;
		z = Axes_Data.Z;

		if(x>=18000){
			TIM4->CCR1 = 20000;
		}else if(x<=0){
			TIM4->CCR1 = 0;
		}else{
			TIM4->CCR1 = x;
		}
		if(y>=18000){
			TIM4->CCR2 = 20000;
		}else if(y<=0){
			TIM4->CCR2 = 0;
		}else{
			TIM4->CCR2 = y;
		}
		if(z>=18000){
			TIM4->CCR3 = 20000;
		}else if(z<=0){
			TIM4->CCR3 = 0;
		}else{
			TIM4->CCR3 = z;
		}


	}
}
