/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

/*
 * To turn on the port we have to ENABLE GPIO/GPIO CLOCK FOR PORT C USING AHB & RCC
 *
 *
 *
 */

#include "stm32f0xx.h"

//LOOK AT THE TUTORIAL TO KNOW WHATS GOING ON


uint32_t g_ADCValue;
//int g_MeasurementNumber;

void waitToBlink(int timeToWait) {
    volatile int i;
    volatile int j;
    for(i = 0; i < timeToWait; i++) {
        j++;
    }
}

void ADC_Config(){
    GPIO_InitTypeDef gpioInit;


    //enable ADC clock
    __ADC1_CLK_ENABLE();


    //enable GPIO clock
    __GPIO_CLK_ENABLE();


    //configure GPIO as analog input
    gpioInit.GPIO_Pin = GPIO_Pin_1; // Needs to be changed for specific channel
    gpioInit.GPIO_Mode = GPIO_Mode_AN;//"ANALOG";
    gpioInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
    HAL_GPIO_Init(GPIOC, &gpioInit); //Sets gpioInit clock

    //Set priotity of ADC interrupt

    //HAL_NVIC_SetPriority(ADC_IER_EOSMPIE, 0, 0);
    HAL_NVIC_SetPriority(ADC_IER_EOSMPIE, 0, 0);

    HAL_NVIC_EnableIRQ(ADC_IER_EOSMPIE);

    //Setup channel settings
    ADC_ChannelConfTypeDef adcChannel;
    g_AdcHandle.Instance = ADC1;   //change to appropriate channel
    ADC

    g_AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
    g_AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
    g_AdcHandle.Init.ScanConvMode = DISABLE;
    g_AdcHandle.Init.ContinuousConvMode = ENABLE;
    g_AdcHandle.Init.DiscontinuousConvMode = DISABLE;
    g_AdcHandle.Init.NbrOfDiscConversion = 0;
    g_AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    g_AdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
    g_AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    g_AdcHandle.Init.NbrOfConversion = 1;
    g_AdcHandle.Init.DMAContinuousRequests = ENABLE;
    g_AdcHandle.Init.EOCSelection = DISABLE;

    HAL_ADC_Init(&g_AdcHandle);

    adcChannel.Channel = ADC_CHANNEL_11;
    adcChannel.Rank = 1;
    adcChannel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    adcChannel.Offset = 0;

    if (HAL_ADC_ConfigChannel(&g_AdcHandle, &adcChannel) != HAL_OK)
    {
		asm("bkpt 255");
    }
}


int main(void) {
    //---------------------------make external func-----------------------------//
    RCC -> AHBENR |= RCC_AHBENR_GPIOCEN; //same as setting 19th bit high in RCC
    GPIOC -> MODER |= GPIO_MODER_MODER6_0;
    GPIOC -> MODER &= ~(GPIO_MODER_MODER6_1);
    GPIOC -> OTYPER &= ~(GPIO_OTYPER_OT_6);
    GPIOC -> OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;
    GPIOC -> PUPDR &= !(GPIO_PUPDR_PUPDR6);
    //--------------------------------------------------------------------------//
    System_clock_config();
    ADC_Config();
    HAL_ADC_Start(&G_ADCHandhle);
	for(;;) {
		if (HAL_ADC_PollForConversion(&g_AdcHandle, 1000000) == HAL_OK) {
			g_ADCValue = HAL_ADC_GetValue(&g_AdcHandle);
			//g_MeasurementNumber++;

			/*
			* TURNING ON LED USING BSRR REGISTER
			* TOGGLES PORT C PIN 6
			*/
			GPIOC -> BSRR |= GPIO_BSRR_BS_6;

			//wait before turning off
			waitToBlink(100000);

			//reset the turned on pin
			GPIOC -> BRR |= GPIO_BRR_BR_6;

			waitToBlink(100000);
		}
	}
}


void System_clock_config() {
	//used to configure clock signal for ADC
}



void mic_input() {


}


void Speaker_output() {


}


void fft() {


}


