#include "debug.h"

/* Global define */
#define IO_NUM 3
#define TARGET_GPIOA GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_16 | GPIO_Pin_17 | GPIO_Pin_18 | GPIO_Pin_19 | GPIO_Pin_20 | GPIO_Pin_21 | GPIO_Pin_22 | GPIO_Pin_23
#define TARGET_GPIOB GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_16 | GPIO_Pin_17 | GPIO_Pin_18 | GPIO_Pin_19 | GPIO_Pin_20 | GPIO_Pin_21
#define TARGET_GPIOC GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_16 | GPIO_Pin_17

typedef struct __Status
{
    GPIO_TypeDef *gpio;
    uint16_t pins;
    char *name;
    uint16_t state;
} Status;

/* Global Variable */

void init_gpio(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = TARGET_GPIOA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = TARGET_GPIOB;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = TARGET_GPIOB;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

int main(void)
{
    u8 i = 0;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
    init_gpio();

    Status statuses[IO_NUM] = {
        {GPIOA, TARGET_GPIOA, "A", 0},
        {GPIOB, TARGET_GPIOB, "B", 0},
        {GPIOC, TARGET_GPIOC, "C", 0},
    };

    Delay_Ms(100);

    for (int i = 0; i < IO_NUM; i++)
    {
        Status *s = &statuses[i];
        uint32_t v = s->gpio->INDR;
        s->state = v;
    }

    printf("init\r\n");

    while (1)
    {
        for (int i = 0; i < IO_NUM; i++)
        {
            Status *s = &statuses[i];
            uint32_t v = s->gpio->INDR;
            if (v == s->state)
            {
                continue;
            }

            for (int j = 0; j < 16; j++)
            {
                uint16_t pin = 1 << j;
                if (!(pin & s->pins))
                {
                    continue;
                }

                if ((v & pin) == (s->state & pin))
                {
                    continue;
                }

                if ((v & pin) == 0)
                {
                    printf("%s%d: L\r\n", s->name, j);
                }
                else
                {
                    printf("%s%d: H\r\n", s->name, j);
                }
            }
            s->state = v;
        }
        Delay_Ms(100);
    }
}
