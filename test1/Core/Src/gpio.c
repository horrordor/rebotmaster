/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, GPIO_PIN_RESET);

    /*Configure GPIO pins : PE3 PE4 */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /*Configure GPIO pins : PF6 PF7 PF8 PF9 */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    /*Configure GPIO pin : PG9 */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 2 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    
}

void LED_Flip(int LED_Id, GPIO_PinState PinState) {
    switch(LED_Id) {
    case 0:
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, PinState);
        break;
    case 1:
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, PinState);
        break;
    case 2:
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, PinState);
        break;
    case 3:
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3|GPIO_PIN_4, PinState);
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, PinState);
        break;
    default:
        break;
    }
}

void LED_Sequence_Show() {
    int i = 0;
    while (LED_type == 0) {
        LED_Flip(0, GPIO_PIN_RESET);
        LED_Flip(2, GPIO_PIN_SET);
        Delay(300);
        LED_Flip(1, GPIO_PIN_RESET);
        LED_Flip(0, GPIO_PIN_SET);
        Delay(300);
        LED_Flip(2, GPIO_PIN_RESET);
        LED_Flip(1, GPIO_PIN_SET);
        Delay(300);
        LED_Flip(3, GPIO_PIN_SET);
        if (i++ == 5) LED_type = (LED_type + 1) % 3;
    }
    i = 0;
    while (LED_type == 1) {
        LED_Flip(3, GPIO_PIN_RESET);
        LED_Flip(0, GPIO_PIN_SET);
        Delay(300);
        LED_Flip(1, GPIO_PIN_SET);
        LED_Flip(0, GPIO_PIN_RESET);
        Delay(300);
        LED_Flip(2, GPIO_PIN_SET);
        LED_Flip(1, GPIO_PIN_RESET);
        Delay(300);
        LED_Flip(3, GPIO_PIN_SET);
        if (i++ == 5) LED_type = (LED_type + 1) % 3;
    }
    i = 0;
    while (LED_type == 2) {
        LED_Flip(3, GPIO_PIN_RESET);
        Delay(300);
        LED_Flip(3, GPIO_PIN_SET);
        Delay(300);
        LED_Flip(3, GPIO_PIN_SET);
        if (i++ == 5) LED_type = (LED_type + 1) % 3;
    }

    LED_Flip(3, GPIO_PIN_SET);
}

void Delay(uint32_t Delay) {
    Delay *= 100000;
    while (Delay--);
}
/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
