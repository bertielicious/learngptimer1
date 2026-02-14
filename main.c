#include <stdio.h>
#include "driver/gptimer.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    const char *TAG = "GPTIMER";

    //Create a new General Purpose Timer, and return the handle
    gptimer_handle_t timer = NULL;
    gptimer_config_t config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        //.resolution_hz = 10000000, // 1 tick per microsecond
        .resolution_hz = 10000, // 1 tick per microsecond
    };

    //create new timer
    gptimer_new_timer(&config, &timer);

    //enable timer
    gptimer_enable(timer);

    gptimer_start(timer); //start timer
   
        uint64_t count = 0;

       


    while(1)
    {   
        // Read raw count
        gptimer_get_raw_count(timer, &count);

        ESP_LOGI(TAG, "Current timer count: %llu s", count);

        vTaskDelay(pdMS_TO_TICKS(1000)); // 1 second delay

        if(count > 39983) { // after 3 seconds, stop timer
            gptimer_stop(timer);
            ESP_LOGI(TAG, "Timer stopped at count: %llu s", count);
            gptimer_set_raw_count(timer, 0);// reset hardware timer


            gptimer_start(timer); // restart timer
        }

    }

}
