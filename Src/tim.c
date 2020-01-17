/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
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
#include "tim.h"

TIM_HandleTypeDef htim_adc1;
TIM_HandleTypeDef htim_adc2;
TIM_HandleTypeDef htim_adc3;

/* ADC1 TIM init function */
void MX_ADC1_TIM_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim_adc1.Instance = ADC1_TIMER_INSTANCE;
  htim_adc1.Init.Prescaler = ADC1_TIMER_PRESCALER;
  htim_adc1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim_adc1.Init.Period = ADC1_TIMER_PERIOD;
  htim_adc1.Init.ClockDivision = ADC1_TIMER_CLOCK_DIVISION;
  print_info("Initializing timer base for ADC1");
  if (HAL_TIM_Base_Init(&htim_adc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Initialization of timer base for ADC1 finished");

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  print_info("Configuring clock source of timer for ADC1");
  if (HAL_TIM_ConfigClockSource(&htim_adc1, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Configuration of clock source of timer for ADC1 finished");

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  print_info("Configuring timer for ADC1 in master mode");
  if (HAL_TIMEx_MasterConfigSynchronization(&htim_adc1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Configuration of timer for ADC1 in master mode finished");
}

/* ADC2 TIM init function */
void MX_ADC2_TIM_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim_adc2.Instance = ADC2_TIMER_INSTANCE;
  htim_adc2.Init.Prescaler = ADC2_TIMER_PRESCALER;
  htim_adc2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim_adc2.Init.Period = ADC2_TIMER_PERIOD;
  htim_adc2.Init.ClockDivision = ADC2_TIMER_CLOCK_DIVISION;
  print_info("Initializing timer base for ADC2");
  if (HAL_TIM_Base_Init(&htim_adc2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Initialization of timer base for ADC2 finished");

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  print_info("Configuring clock source of timer for ADC2");
  if (HAL_TIM_ConfigClockSource(&htim_adc2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Configuration of clock source of timer for ADC2 finished");

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  print_info("Configuring timer for ADC2 in master mode");
  if (HAL_TIMEx_MasterConfigSynchronization(&htim_adc2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Configuration of timer for ADC2 in master mode finished");
}

/* ADC3 TIM init function */
void MX_ADC3_TIM_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim_adc3.Instance = ADC3_TIMER_INSTANCE;
  htim_adc3.Init.Prescaler = ADC3_TIMER_PRESCALER;
  htim_adc3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim_adc3.Init.Period = ADC3_TIMER_PERIOD;
  htim_adc3.Init.ClockDivision = ADC3_TIMER_CLOCK_DIVISION;
  htim_adc3.Init.RepetitionCounter = 0;
  print_info("Initializing timer base for ADC3");
  if (HAL_TIM_Base_Init(&htim_adc3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Initialization of timer base for ADC3 finished");

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  print_info("Configuring clock source of timer for ADC3");
  if (HAL_TIM_ConfigClockSource(&htim_adc3, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Configuration of clock source of timer for ADC3 finished");

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  print_info("Configuring timer for ADC3 in master mode");
  if (HAL_TIMEx_MasterConfigSynchronization(&htim_adc3, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Configuration of timer for ADC3 in master mode finished");
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{
  if(tim_baseHandle->Instance==ADC1_TIMER_INSTANCE)
  {
    /* Peripheral clock enable */
    print_info("Enabling clock of timer for ADC1");
    ADC1_TIMER_CLK_ENABLE();
  }
  else if(tim_baseHandle->Instance==ADC2_TIMER_INSTANCE)
  {
    /* Peripheral clock enable */
    print_info("Enabling clock of timer for ADC2");
    ADC2_TIMER_CLK_ENABLE();
  }
  else if(tim_baseHandle->Instance==ADC3_TIMER_INSTANCE)
  {
    /* Peripheral clock enable */
    print_info("Enabling clock of timer for ADC3");
    ADC3_TIMER_CLK_ENABLE();
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{
  if(tim_baseHandle->Instance==ADC1_TIMER_INSTANCE)
  {
    /* Peripheral clock disable */
    print_info("Disabling clock of timer for ADC1");
    ADC1_TIMER_CLK_DISABLE();
  }
  else if(tim_baseHandle->Instance==ADC2_TIMER_INSTANCE)
  {
    /* Peripheral clock disable */
    print_info("Disabling clock of timer for ADC2");
    ADC2_TIMER_CLK_DISABLE();
  }
  else if(tim_baseHandle->Instance==ADC3_TIMER_INSTANCE)
  {
    /* Peripheral clock disable */
    print_info("Disabling clock of timer for ADC3");
    ADC3_TIMER_CLK_DISABLE();
  }
} 


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
