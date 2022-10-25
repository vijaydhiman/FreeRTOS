#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

EventGroupHandle_t event_Grp;
const uint32_t both_bits = (BIT0 | BIT1);

void task1(void *params)
{
  while (true)
  {
    xEventGroupSetBits(event_Grp, BIT0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task2(void *params)
{
  int a = 0;
  while (true)
  {
    if(a%2 == 0){
      xEventGroupSetBits(event_Grp, BIT1);
      vTaskDelay(2000 / portTICK_PERIOD_MS);  
    }
    a++;
  }
}

void task3(void *params)
{
  while (true)
  {
    uint32_t result = xEventGroupWaitBits(event_Grp, BIT0 | BIT1, pdTRUE, pdTRUE, 1000 / portTICK_PERIOD_MS);
    if((result & both_bits) == both_bits){
      printf("received task1 & task2 bit\n");  
    }
    else{
      if(!(result & BIT0)){
        printf("task1 not working\n"); 
      }
      if(!(result & BIT1)){
        printf("task2 not working\n");   
      }
    }
  }
}

void app_main(void)
{
  event_Grp = xEventGroupCreate();
  xTaskCreate(&task1, "task1", 2048, NULL, 1, NULL);
  xTaskCreate(&task2, "task2", 2048, NULL, 1, NULL);
  xTaskCreate(&task3, "task3", 2048, NULL, 2, NULL);
}

