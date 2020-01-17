/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
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
  * @brief This application converts three different signals of three different
  * configureable channels with three Analog to Digital Converter (ADC). Each ADC
  * works independently from the other at the "Single-channel, single conversion
  * mode" triggered by a timer. The signal conversion is triggered by a own timer
  * for each ADC. Depending on the configuration of the three timers the values
  * are converted simultaneous or not. The sampling rate of each ADC can be
  * configured independently. The measurement is started by pressing the user
  * button (PA0) for a defined time and stopped by pressing it for defined time. On
  * rising and falling edge an interrupt gets generated. On rising edge the time
  * of pressure gets saved. On falling edge the time difference betweeng rising
  * and falling edge gets calculated. Depending on the result the measrument gets
  * started (if not already running) or stopped (if not already stopped). The
  * conversion gets started by starting the corresponding timers and adc and
  * stopped by stopping the corresponding timers and adc. During the
  * initialization all information and errors can be printed out via printf
  * depending on the configuration. If the application is ready to start the
  * measurements the defined success led will be turned on. On errors the defined
  * error led will be turned on. During measurements the success led will be
  * deactivated and on stopping the measurements the success led will be turned on.
  * All the configurations of the system can be found in the configuration.h.
  * @test To ensure that the error led is turned on if an error, e.g. wrong
  *   configuration, occurs, the configuration is setup incorrect.
  * @test To ensure that the success led is turned on when the measurement is ready
  *   to start, a flag is turned on that indicates that the system is ready,
  *   which is checked with the STMStudio.
  * @test To ensure that the switch functionallity works correctly the time
  *   of rising, falling edge and their difference is saved into variables, which
  *   displayed in the STMStudio. Also a counter var is declared, which is
  *   increased by each rising edge, so it can be checked how many times the
  *   user button was intended as pressed and it was really pressed.
  * @test The converted value of each ADC gets persisted to a own variable, that
  *   is checked with the STMStudio. To check the functionallity, the PIN is set
  *   to GND (0 V) and to 3 V.
  * @test The value of the SystemTick Timer gets persisted on each EOC interrupt
  *   so that the difference between the conversion of the signals of all three
  *   channels can be checked.
  * @test The printf configurability is checked with the ST-Link Utility by
  *    enabling or disabling the corresponding print informations.
  * @author Dennis Stumm
  * @date 2019-2020
  * @version 1.0
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "tim.h"
#include "gpio.h"
#include "debug.h"
#include "configuration.h"

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Initialize GPIOs */
  MX_GPIO_Init();

  /* Configure the system clock */
  SystemClock_Config();
  /* Print information messages starting from here,
   * because after this step only the clock gets the correct value
   */
  print_info("### Finished initialization of HAL Library, GPIOs and system clock ###");

  /* Initialize all configured peripherals */
  print_info("### Initializing ADC1 ###");
  MX_ADC1_Init();
  print_info("### Initialization of ADC1 finished ###");
  print_info("### Initializing ADC2 ###");
  MX_ADC2_Init();
  print_info("### Initialization of ADC2 finished ###");
  print_info("### Initializing ADC3 ###");
  MX_ADC3_Init();
  print_info("### Initialization of ADC3 finished ###");
  print_info("### Initializing timer for ADC1 ###");
  MX_ADC1_TIM_Init();
  print_info("### Initialization of timer for ADC1 finished ###");
  print_info("### Initializing timer for ADC2 ###");
  MX_ADC2_TIM_Init();
  print_info("### Initialization of timer for ADC2 finished ###");
  print_info("### Initializing timer for ADC3 ###");
  MX_ADC3_TIM_Init();
  print_info("### Initialization of timer for ADC3 finished ###");

  print_info("### System initialization finished successfully ###");
  print_info("### System is ready for conversion... ###\n############################################");

  HAL_GPIO_WritePin(success_led_GPIO_Port, success_led_Pin, GPIO_PIN_SET);

  /* Infinite loop */
  while (1)
  {
  }
}

/** System Clock Configuration */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  /**Configure the main internal regulator output voltage */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /**Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = SYSCLK_HSI_CALIBRATION_VAL;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = SYSCLK_PLLM;
  RCC_OscInitStruct.PLL.PLLN = SYSCLK_PLLN;
  RCC_OscInitStruct.PLL.PLLP = SYSCLK_PLLP;
  RCC_OscInitStruct.PLL.PLLQ = SYSCLK_PLLQ;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  /**Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = SYSCLK_AHBCLK_DIV;
  RCC_ClkInitStruct.APB1CLKDivider = SYSCLK_APB1CLK_DIV;
  RCC_ClkInitStruct.APB2CLKDivider = SYSCLK_APB2CLK_DIV;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, SYSCLK_FLASH_LATENCY) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  /**Configure the Systick interrupt time */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  /**Configure the Systick */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief  This function is executed in case of error occurrence. Reports the
  * name of the source file and the source line number where the error has
  * occurred.
  * @param file: pointer to the source file name
  * @param line: error line source number
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  print_error("Error occured in: file %s on line %d\r\n", file, line);
  HAL_GPIO_WritePin(error_led_GPIO_Port, error_led_Pin, GPIO_PIN_SET);
  while(1)
  {
  }
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  print_error("Wrong parameters value: file %s on line %d\r\n", file, line);
  HAL_GPIO_WritePin(error_led_GPIO_Port, error_led_Pin, GPIO_PIN_SET);
  while(1)
  {
  }
}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
