#include <stdio.h>
#include <string.h>
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "Memory"

void aTask(void *param)
{
  char buffer [6000];
  memset(&buffer,1,sizeof(buffer));
  int stackmem = uxTaskGetStackHighWaterMark(NULL);
  ESP_LOGI(TAG, "stack space = %d", stackmem);
  while(true) vTaskDelay(1000);
}

void app_main()
{
  int stackmem = uxTaskGetStackHighWaterMark(NULL);
  ESP_LOGI(TAG, "stack space = %d", stackmem);
  
  xTaskCreate(&aTask,"a task",8000,NULL,1, NULL);
}