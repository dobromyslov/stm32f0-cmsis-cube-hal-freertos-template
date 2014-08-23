#include "stm32f0xx.h"
#include "cmsis_os.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void StartThread(void const * argument);
static void CheckButtonThread(void const * argument);

int main(void) {

    // Reset of all peripherals, Initializes the Flash interface and the Systick
    HAL_Init();

    // Configure the system clock
    SystemClock_Config();

    // System interrupt init
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

    // Initialize all configured peripherals
    MX_GPIO_Init();

    osThreadDef(User_thread, StartThread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
    osThreadDef(CheckButton_thread, CheckButtonThread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
    osThreadCreate(osThread(User_thread), NULL);
    osThreadCreate(osThread(CheckButton_thread), NULL);
    osKernelStart(NULL, NULL);

    while (1) {

    }
}

/**
 *System Clock Configuration
 */
void SystemClock_Config(void) {
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  __SYSCFG_CLK_ENABLE();
}

/**
 * Configure pins as
 * Analog
 * Input
 * Output
 * EVENT_OUT
 * EXTI
 */
void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOA_CLK_ENABLE();
  __GPIOC_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC8 PC9 */
  /**
   * PC8 - LD4 [blue led]
   * PC9 - LD3 [green led]
   */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

static int ledState = 0;

static void StartThread(void const * argument) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, 1);
    for(;;) {
        vTaskDelay(200);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, ledState);
    }
}

static void CheckButtonThread(void const * argument) {
    uint8_t newstate, state = 1;
    for (;;) {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != state) {
            vTaskDelay(20);
            newstate = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
            if ( newstate != state ) {
                state = newstate;
                if (newstate) {
                    ledState = !ledState;
                }
            }
        }
        vTaskDelay(20);
    }
}

extern void xPortSysTickHandler(void);

void SysTick_Handler(void) {
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
        xPortSysTickHandler();
    }
    HAL_IncTick();
}
