
#include "CK_GPIO.h"
#include "CK_TIME_HAL.h"

#include "CK_LED.h"

// This pin is now used for ODS TX later decide another pin and use led functions.
#define CK_RCC_APB1ENR_TIM2_ENABLE  1u<<0
#define ONBOARD_LED1_GPIOx          GPIOA
#define ONBOARD_LED1_PINx           2


TIM_TypeDef* TIMx;

uint32_t frequency_pclk2;
uint32_t frequency;

/*
 * Blink effect sets the frequency so it works without and delay and
 * better indicator of process notification.
 * Shine effect is just there i did not delete it.
 *
 */
void CK_LED_Init(void){
    //Onboard inidicator led
    // PA2 is TIM2 Channel 3

    frequency = 1; // Default is set to 10Hz.
    TIMx = TIM2;

    RCC->APB1ENR |= CK_RCC_APB1ENR_TIM2_ENABLE;

    CK_GPIOx_ClockEnable(ONBOARD_LED1_GPIOx);

    CK_GPIOx_Init(ONBOARD_LED1_GPIOx, ONBOARD_LED1_PINx, CK_GPIO_AF, CK_GPIO_AF1, CK_GPIO_PUSHPULL, CK_GPIO_VERYHIGH, CK_GPIO_NOPUPD);

    frequency_pclk2 = HAL_RCC_GetPCLK2Freq(); // 84MHz

    // Main clock prescalar
    TIMx->PSC = 7;

    // Freq. is fix for each ch on same timer
    TIMx->ARR = ( (frequency_pclk2 / (TIMx->PSC+1) ) / frequency ) - 1;

    int percentage = 50;  // Duty cycle 0 to 100
    TIMx->CCR3 = (TIMx->ARR * percentage) / 100 ;

    //TIMx CH3
    TIMx->CCMR2 |= (6u << 4) | (1u << 3); // CH3 PWM Mode 1 upcounting, CH3 Preload Enable Bit 3,
    TIMx->CCER  |= (1u << 8);             //CH3 Enable

    // CR1 default Edge Alligned, Upcounting
    TIMx->CR1 |= 1u << 7; // Auto-reload preload enable

    TIMx->EGR |= 1u << 0; // Update generation enabled

    TIMx->CR1 |= 1u << 0; // Counter enable

    //CK_LED_BlinkEffect(BLINK_EFFECT3Hz);

}

void CK_LED_ChangeFrequency(int freq){

    TIMx->ARR = ((frequency_pclk2/(TIMx->PSC+1))/freq)-1;//Freq. is fix for each ch on same timer

}

void CK_LED_SetDutyCycle(int dty){

    TIMx->CCR3 = ((dty * TIMx->ARR) / 2500);

}

void CK_LED_ShineEffect(int cycle){

    for(int i = 0; i < cycle; i++){
        CK_LED_SetDutyCycle(i);
        CK_TIME_DelayMicroSec(500);
    }
    for(int i = cycle; i > 0; i--){
        CK_LED_SetDutyCycle(i);
        CK_TIME_DelayMicroSec(500);
    }
}

void CK_LED_BlinkEffect(int freq){

    CK_LED_ChangeFrequency(freq);
    CK_LED_SetDutyCycle(1000);
}











