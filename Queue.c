#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xQueueHandle queue;

void task2(void *params)
{
  int count = 0;
  while (true)
  {
    count++;
    long value = xQueueSend(queue, &count, 1000 / portTICK_PERIOD_MS);
    if(value) 
    {
      printf("sent \n");
    } 
    else 
    {
       printf("failed to send\n");
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task1(void *params)
{
  while (true)
  { 
    int rxInt;
    if(xQueueReceive(queue, &rxInt , 5000 / portTICK_PERIOD_MS))
    {
      printf("received %d\n", rxInt);
    }
  }
}

void app_main(void)
{
  queue = xQueueCreate(3, sizeof(int));
  xTaskCreate(&task1, "task1", 2048, NULL, 2, NULL);
  xTaskCreate(&task2, "task2", 2048, NULL, 1, NULL);
}