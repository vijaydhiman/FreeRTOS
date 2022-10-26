#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_system.h"

void timer(TimerHandle_t xTimer)
{
  printf("hit at %lld\n", esp_timer_get_time() /1000);
}
void app_main(void)
{
  TimerHandle_t xTimer = xTimerCreate("timer", pdMS_TO_TICKS(2000),true,NULL, timer);
  xTimerStart(xTimer,0);
}

