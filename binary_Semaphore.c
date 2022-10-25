#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xSemaphoreHandle binSemaphore;

void task2(void *params)
{
  while (true)
  {
    printf("task2\n");
    xSemaphoreGive(binSemaphore);
    printf("done\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void task1(void *params)
{
  while (true)
  {
    xSemaphoreTake(binSemaphore, portMAX_DELAY);
    printf("doing something \n");
  }
}

void app_main(void)
{
  binSemaphore = xSemaphoreCreateBinary();
  xTaskCreate(&task1, "task1", 2048, NULL, 2, NULL);
  xTaskCreate(&task2, "task2", 2048, NULL, 1, NULL);
}