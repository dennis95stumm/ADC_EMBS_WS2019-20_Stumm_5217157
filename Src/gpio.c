/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2020 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "adc.h"
#include "tim.h"

/* Private variables ---------------------------------------------------------*/
/**
 *
 */
uint32_t button_press_time = NULL;

/**
 *
 */
uint32_t button_press_duration = NULL;

/**
 *
 */
uint8_t conversion_running = 0;

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  user_button_GPIO_clk_enable();
  success_led_GPIO_clk_enable();
  error_led_GPIO_clk_enable();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(success_led_GPIO_Port, success_led_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(error_led_GPIO_Port, error_led_Pin, GPIO_PIN_RESET);
  
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = user_button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(user_button_GPIO_Port, &GPIO_InitStruct);

  // Enable interrupt
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  /*Configure GPIO pins : PGPin PGPin */
  GPIO_InitStruct.Pin = success_led_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(success_led_GPIO_Port, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = error_led_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(error_led_GPIO_Port, &GPIO_InitStruct);
}

/**
 * TODO: Add documentation
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == user_button_Pin)
  {
    if (HAL_GPIO_ReadPin(user_button_GPIO_Port, user_button_Pin) == GPIO_PIN_SET && button_press_time == NULL)
    {
      button_press_time = HAL_GetTick();
      print_info("User Button pressed at %d", button_press_time);
    }
    else if (HAL_GPIO_ReadPin(user_button_GPIO_Port, user_button_Pin) == GPIO_PIN_RESET && button_press_time != NULL)
    {
      button_press_duration = HAL_GetTick() - button_press_time;
      button_press_time = NULL;
      print_info("User Button released after %d", button_press_duration);

      if (button_press_duration >= BUTTON_PRESSURE_START && conversion_running == 0)
      {
        conversion_running = 1;
        print_info("Starting conversion...\n############################################");
        HAL_GPIO_WritePin(success_led_GPIO_Port, success_led_Pin, GPIO_PIN_RESET);

        #ifdef DEBUG_INFO
        // Reset debugging vars
        adc1_last_eoc = HAL_GetTick();
        adc2_last_eoc = HAL_GetTick();
        adc3_last_eoc = HAL_GetTick();
        #endif

        // ADC1
        if(HAL_ADC_Start_IT(&hadc1) != HAL_OK)
        {
          /* Start Conversation Error */
          _Error_Handler(__FILE__, __LINE__);
        }
        if(HAL_TIM_Base_Start(&htim_adc1) != HAL_OK)
        {
          /* Counter Enable Error */
          _Error_Handler(__FILE__, __LINE__);
        }
        
        // ADC2
        if(HAL_ADC_Start_IT(&hadc2) != HAL_OK)
        {
          /* Start Conversation Error */
          _Error_Handler(__FILE__, __LINE__);
        }
        if(HAL_TIM_Base_Start(&htim_adc2) != HAL_OK)
        {
          /* Counter Enable Error */
          _Error_Handler(__FILE__, __LINE__);
        }
        
        // ADC3
        if(HAL_ADC_Start_IT(&hadc3) != HAL_OK)
        {
          /* Start Conversation Error */
          _Error_Handler(__FILE__, __LINE__);
        }
        if(HAL_TIM_Base_Start(&htim_adc3) != HAL_OK)
        {
          /* Counter Enable Error */
          _Error_Handler(__FILE__, __LINE__);
        }
      }
      else if (button_press_duration >= BUTTON_PRESSURE_STOP && conversion_running == 1)
      {
        conversion_running = 0;
        print_info("Stopping conversion...\n############################################");
        HAL_GPIO_WritePin(success_led_GPIO_Port, success_led_Pin, GPIO_PIN_SET);

        // ADC1
        if(HAL_TIM_Base_Stop(&htim_adc1) != HAL_OK)
        {
          /* Counter Disable Error */
          _Error_Handler(__FILE__, __LINE__);
        }
        if(HAL_ADC_Stop_IT(&hadc1) != HAL_OK)
        {
          /* Stop Conversation Error */
          _Error_Handler(__FILE__, __LINE__);
        }
        
        // ADC2
        if(HAL_TIM_Base_Stop(&htim_adc2) != HAL_OK)
        {
          /* Counter Disable Error */
          _Error_Handler(__FILE__, __LINE__);
        }
        if(HAL_ADC_Stop_IT(&hadc2) != HAL_OK)
        {
          /* Stop Conversation Error */
          _Error_Handler(__FILE__, __LINE__);
        }
        
        // ADC3
        if(HAL_TIM_Base_Stop(&htim_adc3) != HAL_OK)
        {
          /* Counter Disable Error */
          _Error_Handler(__FILE__, __LINE__);
        }
        if(HAL_ADC_Stop_IT(&hadc3) != HAL_OK)
        {
          /* Stop Conversation Error */
          _Error_Handler(__FILE__, __LINE__);
        }

        #ifdef DEBUG_INFO
        // Reset debugging vars
        adc1_conversion_time = 0;
        adc2_conversion_time = 0;
        adc3_conversion_time = 0;
        #endif
      }
    }
  }
}


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
