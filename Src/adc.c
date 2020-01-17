/**
  ******************************************************************************
  * File Name          : ADC.c
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
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
#include "adc.h"
#include "gpio.h"
#include "configuration.h"

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;

uint32_t adc1_converted_value;
uint32_t adc2_converted_value;
uint32_t adc3_converted_value;

#ifdef DEBUG_INFO
uint32_t adc1_last_eoc = 0;
uint32_t adc1_conversion_time = 0;

uint32_t adc2_last_eoc = 0;
uint32_t adc2_conversion_time = 0;

uint32_t adc3_last_eoc = 0;
uint32_t adc3_conversion_time = 0;
#endif

/* ADC1 init function */
void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;

  /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC1_CLOCK_PRESCALER;
  hadc1.Init.Resolution = ADC1_RESOLUTION;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC1_EXTERNEL_TRIGGER_CONV_EDGE;
  hadc1.Init.ExternalTrigConv = ADC1_EXTERNEL_TRIGGER_CONV;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

  print_info("Configuring ADC1");
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Configuration of ADC1 finished");

  /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. */
  sConfig.Channel = ADC1_CHANNEL;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC1_SAMPLETIME;

  print_info("Configuring ADC1 channel");
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Configuration of ADC1 channel finished");
}

/* ADC2 init function */
void MX_ADC2_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;

  /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC2_CLOCK_PRESCALER;
  hadc2.Init.Resolution = ADC2_RESOLUTION;
  hadc2.Init.ScanConvMode = DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC2_EXTERNEL_TRIGGER_CONV_EDGE;
  hadc2.Init.ExternalTrigConv = ADC2_EXTERNEL_TRIGGER_CONV;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

  print_info("Configuring ADC2");
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Configuration of ADC2 finished");

  /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. */
  sConfig.Channel = ADC2_CHANNEL;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC2_SAMPLETIME;

  print_info("Configuring ADC2 channel");
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Configuration of ADC2 channel finished");
}

/* ADC3 init function */
void MX_ADC3_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;

  /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC3_CLOCK_PRESCALER;
  hadc3.Init.Resolution = ADC3_RESOLUTION;
  hadc3.Init.ScanConvMode = DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC3_EXTERNEL_TRIGGER_CONV_EDGE;
  hadc3.Init.ExternalTrigConv = ADC3_EXTERNEL_TRIGGER_CONV;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

  print_info("Configuring ADC3");
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Configuration of ADC3 finished");

  /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. */
  sConfig.Channel = ADC3_CHANNEL;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC3_SAMPLETIME;

  print_info("Configuring ADC3 channel");
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  print_info("Configuration of ADC3 channel finished");
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(adcHandle->Instance==ADC1)
  {
    /* ADC1 clock enable */
    print_info("Enabling ADC1 and correspoind GPIO clocks");
    __HAL_RCC_ADC1_CLK_ENABLE();
    ADC1_CHANNEL_GPIO_CLOCK_ENABLE();
  
    /** ADC1 GPIO Configuration */
    GPIO_InitStruct.Pin = adc1_input_channel_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    print_info("Initializing ADC1 GPIO");
    HAL_GPIO_Init(adc1_input_channel_GPIO_Port, &GPIO_InitStruct);

    print_info("Enabling ADC IRQ");
    HAL_NVIC_SetPriority(ADC_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
  }
  else if(adcHandle->Instance==ADC2)
  {
    /* ADC2 clock enable */
    print_info("Enabling ADC2 and correspoind GPIO clocks");
    __HAL_RCC_ADC2_CLK_ENABLE();
    ADC2_CHANNEL_GPIO_CLOCK_ENABLE();
  
    /** ADC2 GPIO Configuration */
    GPIO_InitStruct.Pin = adc2_input_channel_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    print_info("Initializing ADC2 GPIO");
    HAL_GPIO_Init(adc2_input_channel_GPIO_Port, &GPIO_InitStruct);
  }
  else if(adcHandle->Instance==ADC3)
  {
    /* ADC3 clock enable */
    print_info("Enabling ADC3 and correspoind GPIO clocks");
    __HAL_RCC_ADC3_CLK_ENABLE();
    ADC3_CHANNEL_GPIO_CLOCK_ENABLE();
  
    /** ADC3 GPIO Configuration */
    GPIO_InitStruct.Pin = adc3_input_channel_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    print_info("Initializing ADC3 GPIO");
    HAL_GPIO_Init(adc3_input_channel_GPIO_Port, &GPIO_InitStruct);
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
    print_info("Disabling ADC IRQ");
    HAL_NVIC_DisableIRQ(ADC_IRQn);

    /* Peripheral clock disable */
    print_info("Disabling ADC1 clock");
    __HAL_RCC_ADC1_CLK_DISABLE();
  
    /** ADC1 GPIO Configuration */
    print_info("Deinitializing ADC1 GPIO");
    HAL_GPIO_DeInit(adc1_input_channel_GPIO_Port, adc1_input_channel_Pin);
  }
  else if(adcHandle->Instance==ADC2)
  {
    /* Peripheral clock disable */
    print_info("Disabling ADC2 clock");
    __HAL_RCC_ADC2_CLK_DISABLE();
  
    /** ADC2 GPIO Configuration */
    print_info("Deinitializing ADC2 GPIO");
    HAL_GPIO_DeInit(adc2_input_channel_GPIO_Port, adc2_input_channel_Pin);
  }
  else if(adcHandle->Instance==ADC3)
  {
    /* Peripheral clock disable */
    print_info("Disabling ADC3 clock");
    __HAL_RCC_ADC3_CLK_DISABLE();
  
    /** ADC3 GPIO Configuration */
    print_info("Deinitializing ADC3 GPIO");
    HAL_GPIO_DeInit(adc3_input_channel_GPIO_Port, adc3_input_channel_Pin);
  }
}

/**
  * @brief  Regular conversion complete callback in non blocking mode 
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  if(hadc->Instance==ADC1)
  {
    #ifdef DEBUG_INFO
    adc1_conversion_time = HAL_GetTick() - adc1_last_eoc;
    adc1_last_eoc = HAL_GetTick();
    #endif
    adc1_converted_value = HAL_ADC_GetValue(hadc);
    print_info("ADC1 converted value: %d", adc1_converted_value);
  }
  else if(hadc->Instance==ADC2)
  {
    #ifdef DEBUG_INFO
    adc2_conversion_time = HAL_GetTick() - adc2_last_eoc;
    adc2_last_eoc = HAL_GetTick();
    #endif
    adc2_converted_value = HAL_ADC_GetValue(hadc);
    print_info("ADC2 converted value: %d", adc2_converted_value);
  }
  else if(hadc->Instance==ADC3)
  {
    #ifdef DEBUG_INFO
    adc3_conversion_time = HAL_GetTick() - adc3_last_eoc;
    adc3_last_eoc = HAL_GetTick();
    #endif
    adc3_converted_value = HAL_ADC_GetValue(hadc);
    print_info("ADC3 converted value: %d", adc3_converted_value);
  }
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
