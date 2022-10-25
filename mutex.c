#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xSemaphoreHandle mutexBus;

void writeToBus(char *message)
{
  printf(message);
}

void task1(void *params)
{
  while (true)
  {
    if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
    {
      writeToBus("message from task 1\n");
      xSemaphoreGive(mutexBus);
    }
    else
    {
      printf("task 1 timed out \n");
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task2(void *params)
{
  while (true)
  {
    if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
    {
      writeToBus("message from task 2\n");
      xSemaphoreGive(mutexBus);
    }
    else
    {
      printf("task 2 timed out \n");
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void app_main(void)
{
  mutexBus = xSemaphoreCreateMutex();
  xTaskCreate(&task1, "task 1", 2048, NULL, 2, NULL);
  xTaskCreate(&task2, "task 2", 2048, NULL, 2, NULL);
}