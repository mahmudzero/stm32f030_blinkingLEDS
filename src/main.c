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
 *	To turn on the port we have to ENABLE GPIO/GPIO CLOCK FOR PORT C USING AHB & RCC
 *
 *
 *
 */

#include "stm32f0xx.h"

//LOOK AT THE TUTORIAL TO KNOW WHATS GOING ON

void waitToBlink(int timeToWait) {
	volatile int i;
	volatile int j;
	for(i = 0; i < timeToWait; i++) {
		j++;
	}
}

int main(void) {

	RCC -> AHBENR |= RCC_AHBENR_GPIOCEN; //same as setting 19th bit high in RCC


	GPIOC -> MODER |= GPIO_MODER_MODER6_0;
	GPIOC -> MODER &= ~(GPIO_MODER_MODER6_1);

	GPIOC -> OTYPER &= ~(GPIO_OTYPER_OT_6);

	GPIOC -> OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;


	GPIOC -> PUPDR &= !(GPIO_PUPDR_PUPDR6);


	for(;;) {
		/*
		 * TURNING ON LED USING BSRR REGISTER
		 * THIS IS FOR TURNING PORT C PIN 6
		 */
		GPIOC -> BSRR |= GPIO_BSRR_BS_6;

		//wait before turning off
		waitToBlink(100000);

		//reset the turned on pin
		GPIOC -> BRR |= GPIO_BRR_BR_6;

		waitToBlink(100000);



	}
}
