#include <stdio.h>
#include "pico/stdlib.h"

#define GPIO_NUM 30

int main()
{
    stdio_init_all();
    bool led_state[GPIO_NUM] = {0};

    for (uint i = 0; i < GPIO_NUM; i++)
    {
        gpio_init(i);
        gpio_set_dir(i, GPIO_IN);
        gpio_pull_up(i);
    }

    sleep_ms(10);

    for (uint i = 0; i < GPIO_NUM; i++)
    {
        led_state[i] = gpio_get(i);
    }

    printf("init\n");

    while (true)
    {
        sleep_ms(100);
        for (uint i = 0; i < GPIO_NUM; i++)
        {
            if (led_state[i] != gpio_get(i))
            {
                led_state[i] = !led_state[i];
                printf("GPIO %d: %s\n", i, led_state[i] ? "H" : "L");
            }
        }
    }
}
