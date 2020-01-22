/**
  ******************************************************************************
  * @file configuration.h
  * @author Dennis Stumm
  * @date 2019-2020
  * @version 1.0
  * @brief This file contains the configuration of the application. Here the
  *   logging, the gpio pins, sampling rate and the start and stop press
  *   duration can be configured. The system configuration in the lower part
  *   shouldn't be touched, in order to get a functioning application.
  ******************************************************************************
  */
  
#ifndef __CONFIGURATION_H
#define __CONFIGURATION_H


/* Debug configuration ------------------------------------------------------*/
/**
 * @brief To disable the info or error debug messages comment out the
 *   corresponding lines below. To enable logs comment in the lines.
 */
/* #define DEBUG_INFO */
/* #define DEBUG_ERROR */

/* Configuration of button pressing time ------------------------------------*/

/**
 * @brief Definition of the time in milliseconds that the user button on the
 *   user_button_Pin should be pressed, to start or to stop a measurement. The
 *   starting time should be at least one second and maximum one second lower
 *   than the stopping time.
 */
#define BUTTON_PRESSURE_START (uint32_t) 1000
#define BUTTON_PRESSURE_STOP  (uint32_t) 5000

/* Configuration of sampling rate -------------------------------------------*/

/**
 * @brief Sample rate of each of the three ADCs. They can be configured between
 *   1 Hz and 36585 Hz, which is limited by the resolution, sampling time and
 *   clock frequency that is configured by the program.
 */
#define ADC1_SAMPLE_RATE 10
#define ADC2_SAMPLE_RATE 10
#define ADC3_SAMPLE_RATE 10

/* Configuration of GPIO ports and pins -------------------------------------*/
/**
 * @brief Configuration for the user button.
 */
#define user_button_Pin GPIO_PIN_0
#define user_button_GPIO_Port GPIOA
#define user_button_GPIO_clk_enable() __HAL_RCC_GPIOA_CLK_ENABLE()

/**
 * @brief Configuration for the adc1 input channel. The channel can be one
 *   of the ADC_channels between 1 and 15. The 0 channel can't be used, if the 
 *   user button is activated. Also a channel used by this adc shouldn't be used
 *   by another adc.
 */
#define adc1_input_channel_Pin GPIO_PIN_1
#define adc1_input_channel_GPIO_Port GPIOA
#define ADC1_CHANNEL ADC_CHANNEL_1
#define ADC1_CHANNEL_GPIO_CLOCK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

/**
 * @brief Configuration for the adc2 input channel. The channel can be one
 *   of the ADC_channels between 1 and 15. The 0 channel can't be used, if the 
 *   user button is activated. Also a channel used by this adc shouldn't be used
 *   by another adc.
 */
#define adc2_input_channel_Pin GPIO_PIN_2
#define adc2_input_channel_GPIO_Port GPIOA
#define ADC2_CHANNEL ADC_CHANNEL_2
#define ADC2_CHANNEL_GPIO_CLOCK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

/**
 * @brief Configuration for the adc3 input channel. The channel can be one
 *   of the ADC_channels between 1 and 15. The 0 channel can't be used, if the 
 *   user button is activated. Also a channel used by this adc shouldn't be used
 *   by another adc.
 */
#define adc3_input_channel_Pin GPIO_PIN_3
#define adc3_input_channel_GPIO_Port GPIOA
#define ADC3_CHANNEL ADC_CHANNEL_3
#define ADC3_CHANNEL_GPIO_CLOCK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

/**
 * @brief Configuration for the success status led. Default it is the led at
 *   PG13 (green).
 */
#define success_led_Pin GPIO_PIN_13
#define success_led_GPIO_Port GPIOG
#define success_led_GPIO_clk_enable() __HAL_RCC_GPIOG_CLK_ENABLE()

/**
 * @brief Configuration for the error status led. Default it is the led at
 *   PG14 (red).
 */
#define error_led_Pin GPIO_PIN_14
#define error_led_GPIO_Port GPIOG
#define error_led_GPIO_clk_enable() __HAL_RCC_GPIOG_CLK_ENABLE()



/*----------------------------------------------------------------------------*/
/* System configuration. WARNING: Don't change this configurations.           */
/*----------------------------------------------------------------------------*/

/* System clock configuration -----------------------------------------------*/
/* The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 144000000
  *            HCLK(Hz)                       = 144000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 4
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 8
  *            PLL_N                          = 144
  *            PLL_P                          = 2
  *            PLL_Q                          = 4
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 4
  */
#define SYSCLK_HSI_CALIBRATION_VAL 16
#define SYSCLK_PLLM 8
#define SYSCLK_PLLN 144
#define SYSCLK_PLLP RCC_PLLP_DIV2
#define SYSCLK_PLLQ 4
#define SYSCLK_AHBCLK_DIV RCC_SYSCLK_DIV1
#define SYSCLK_APB1CLK_DIV RCC_HCLK_DIV4
#define SYSCLK_APB2CLK_DIV RCC_HCLK_DIV4
#define SYSCLK_FLASH_LATENCY FLASH_LATENCY_4
#define TIMER_CLK_FREQUENCY 72000000

/* ADC1 timer configuration -------------------------------------------------*/

/**
 * @brief Configuration of the timer for the adc1. The timer is set to TIM2.
 *   Depending on the configured sample rate the prescaler and period gets
 *   calculated.
 */
#define ADC1_TIMER_INSTANCE TIM2
#if (TIMER_CLK_FREQUENCY/ADC1_SAMPLE_RATE) > 10000
#define ADC1_TIMER_PRESCALER 10000-1
#define ADC1_TIMER_PERIOD ((TIMER_CLK_FREQUENCY/ADC1_SAMPLE_RATE)/10000) - 1
#else
#define ADC1_TIMER_PRESCALER 0
#define ADC1_TIMER_PERIOD (TIMER_CLK_FREQUENCY/ADC1_SAMPLE_RATE) - 1
#endif
#define ADC1_TIMER_CLOCK_DIVISION TIM_CLOCKDIVISION_DIV1
#define ADC1_TIMER_CLK_ENABLE() __HAL_RCC_TIM2_CLK_ENABLE()
#define ADC1_TIMER_CLK_DISABLE() __HAL_RCC_TIM2_CLK_DISABLE()

/* ADC2 timer configuration -------------------------------------------------*/

/**
 * @brief Configuration of the timer for the adc2. The timer is set to TIM3.
 *   Depending on the configured sample rate the prescaler and period gets
 *   calculated.
 */
#define ADC2_TIMER_INSTANCE TIM3
#if (TIMER_CLK_FREQUENCY/ADC2_SAMPLE_RATE) > 10000
#define ADC2_TIMER_PRESCALER 10000-1
#define ADC2_TIMER_PERIOD ((TIMER_CLK_FREQUENCY/ADC2_SAMPLE_RATE)/10000) - 1
#else
#define ADC2_TIMER_PRESCALER 0
#define ADC2_TIMER_PERIOD (TIMER_CLK_FREQUENCY/ADC2_SAMPLE_RATE) - 1
#endif
#define ADC2_TIMER_CLOCK_DIVISION TIM_CLOCKDIVISION_DIV1
#define ADC2_TIMER_CLK_ENABLE() __HAL_RCC_TIM3_CLK_ENABLE()
#define ADC2_TIMER_CLK_DISABLE() __HAL_RCC_TIM3_CLK_DISABLE()

/* ADC3 timer configuration -------------------------------------------------*/

/**
 * @brief Configuration of the timer for the adc3. The timer is set to TIM8.
 *   Depending on the configured sample rate the prescaler and period gets
 *   calculated.
 */
#define ADC3_TIMER_INSTANCE TIM8
#if (TIMER_CLK_FREQUENCY/ADC3_SAMPLE_RATE) > 10000
#define ADC3_TIMER_PRESCALER 10000-1
#define ADC3_TIMER_PERIOD ((TIMER_CLK_FREQUENCY/ADC3_SAMPLE_RATE)/10000) - 1
#else
#define ADC3_TIMER_PRESCALER 0
#define ADC3_TIMER_PERIOD (TIMER_CLK_FREQUENCY/ADC3_SAMPLE_RATE) - 1
#endif
#define ADC3_TIMER_CLOCK_DIVISION TIM_CLOCKDIVISION_DIV1
#define ADC3_TIMER_CLK_ENABLE() __HAL_RCC_TIM8_CLK_ENABLE()
#define ADC3_TIMER_CLK_DISABLE() __HAL_RCC_TIM8_CLK_DISABLE()

/* ADC1 configuration -------------------------------------------------------*/

/**
 * @brief Configuration of adc. The clock is configred with a prescaler of 2
 *   (APB1/2, 18 MHz). The resolution is set to 12 Bit and the sample time to
 *   480 adc clock cycles (about 27,3 microseconds). The adc is configured to
 *   start a conversion triggered by external source (TIM2 trigger out) on
 *   rising edge.
 */
#define ADC1_CLOCK_PRESCALER ADC_CLOCK_SYNC_PCLK_DIV2
#define ADC1_RESOLUTION ADC_RESOLUTION_12B
#define ADC1_SAMPLETIME ADC_SAMPLETIME_480CYCLES
#define ADC1_EXTERNEL_TRIGGER_CONV_EDGE ADC_EXTERNALTRIGCONVEDGE_RISING
#define ADC1_EXTERNEL_TRIGGER_CONV ADC_EXTERNALTRIGCONV_T2_TRGO

/* ADC2 configuration -------------------------------------------------------*/

/**
 * @brief Configuration of adc. The clock is configred with a prescaler of 2
 *   (APB1/2, 18 MHz). The resolution is set to 12 Bit and the sample time to
 *   480 adc clock cycles (about 27,3 microseconds). The adc is configured to
 *   start a conversion triggered by external source (TIM3 trigger out) on
 *   rising edge.
 */
#define ADC2_CLOCK_PRESCALER ADC_CLOCK_SYNC_PCLK_DIV2
#define ADC2_RESOLUTION ADC_RESOLUTION_12B
#define ADC2_SAMPLETIME ADC_SAMPLETIME_480CYCLES
#define ADC2_EXTERNEL_TRIGGER_CONV_EDGE ADC_EXTERNALTRIGCONVEDGE_RISING
#define ADC2_EXTERNEL_TRIGGER_CONV ADC_EXTERNALTRIGCONV_T3_TRGO

/* ADC3 configuration -------------------------------------------------------*/


/**
 * @brief Configuration of adc. The clock is configred with a prescaler of 2
 *   (APB1/2, 18 MHz). The resolution is set to 12 Bit and the sample time to
 *   480 adc clock cycles (about 27,3 microseconds). The adc is configured to
 *   start a conversion triggered by external source (TIM8 trigger out) on
 *   rising edge.
 */
#define ADC3_CLOCK_PRESCALER ADC_CLOCK_SYNC_PCLK_DIV2
#define ADC3_RESOLUTION ADC_RESOLUTION_12B
#define ADC3_SAMPLETIME ADC_SAMPLETIME_480CYCLES
#define ADC3_EXTERNEL_TRIGGER_CONV_EDGE ADC_EXTERNALTRIGCONVEDGE_RISING
#define ADC3_EXTERNEL_TRIGGER_CONV ADC_EXTERNALTRIGCONV_T8_TRGO

/* Assert -------------------------------------------------------------------*/

/**
 * @brief Enabled full assert to prevent wrong configuration.
 */
#define USE_FULL_ASSERT    1U

#endif
