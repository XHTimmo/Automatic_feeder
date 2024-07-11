#include <stdio.h>
// #include <driver.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/ledc.h"

#define MOTOR GPIO_NUM_12

void MotorControl_Init(void)
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 4000,
        .clk_cfg = LEDC_AUTO_CLK};
    ledc_timer_config(&ledc_timer);
    ledc_channel_config_t ledc_channer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = MOTOR,
        .duty = 4096,
        .hpoint = 0};
    ledc_channel_config(&ledc_channer);
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
}

void set_pwm1(uint32_t pwm)
{
    // printf("set pwm1 %ld\n",pwm);
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, pwm);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

void app_main(void)
{
    MotorControl_Init();
    set_pwm1(1000);
    // gpio_reset_pin(MOTOR);
    // esp_rom_gpio_pad_select_gpio(MOTOR),
    // gpio_set_direction(MOTOR,GPIO_MODE_OUTPUT);
    uint8_t sec = 60;
    uint8_t min = 60;
    uint8_t hours = 4;
    while (1)
    {
        printf("%d,SET 1\n", MOTOR);
        // gpio_set_level(MOTOR,1);
        set_pwm1(2700);
        vTaskDelay(400 / portTICK_PERIOD_MS);
        printf("%d,SET 0\n", MOTOR);
        // gpio_set_level(MOTOR,0);
        set_pwm1(0);
        while (hours--)
        {
            while (min--)
            {
                while (sec--)
                {
                    vTaskDelay(1000 / portTICK_PERIOD_MS);
                }
                sec = 60;
            }
            min = 60;
        }
        hours = 4;
    }
}
