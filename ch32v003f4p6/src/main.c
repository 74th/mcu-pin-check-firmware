/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 GPIO routine:
 PD0 push-pull output.

*/

#include "debug.h"

/* Global define */
typedef struct __Status
{
    GPIO_TypeDef *gpio;
    uint16_t pins;
    char *name;
    uint16_t state;
} Status;

#define IO_NUM 3

/* Global Variable */
Status statuses[IO_NUM] = {
    {GPIOA, GPIO_Pin_1 | GPIO_Pin_2, "A", 0},
    {GPIOC, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, "C", 0},
    {GPIOD, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7, "D", 0},
};

void GPIO_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    GPIO_INIT();

    Delay_Ms(100);

    for (int i = 0; i < IO_NUM; i++)
    {
        Status *s = &statuses[i];

        s->state = GPIO_ReadInputData(s->gpio);
    }

    printf("init\n");

    while (1)
    {
        Delay_Ms(100);

        for (int i = 0; i < IO_NUM; i++)
        {
            Status *s = &statuses[i];

            uint8_t v = GPIO_ReadInputData(s->gpio);
            // printf("@@1 %s: %x %x %x\n", s->name, s->pins, v, s->state);

            for (int j = 0; j < 16; j++)
            {
                uint16_t pin = 1 << j;
                if (!(pin & s->pins))
                {
                    continue;
                }
                // printf("@@2 %d: %x %x %x %d\n", j, pin, v & pin, s->state & pin, (v & pin) != (s->state & pin));

                if ((v & pin) != (s->state & pin))
                {
                    if (v & pin)
                    {
                        printf("%s%d: H\n", s->name, j);
                    }
                    else
                    {
                        printf("%s%d: L\n", s->name, j);
                    }
                }
            }

            s->state = v;
        }
    }
}
