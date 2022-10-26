#include <stdio.h>
#include "esp_timer.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void timer_callback(void *args)
{
  printf("callback\n");
}

void app_main(void)
{

  const esp_timer_create_args_t esp_timer_create_args = {
      .callback = timer_callback,
      .name = "My timer"};

  esp_timer_handle_t esp_timer_handle;
  esp_timer_create(&esp_timer_create_args, &esp_timer_handle);
  esp_timer_start_periodic(esp_timer_handle, 500000);

  int x = 0;
  while(true)
  {
      esp_timer_dump(stdout);
      vTaskDelay(pdMS_TO_TICKS(1000));
      if(x++ == 5)
      {
          esp_timer_stop(esp_timer_handle);
          esp_timer_delete(esp_timer_handle);
      }
  }
}