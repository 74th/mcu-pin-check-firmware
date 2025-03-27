#include "debug.h"

typedef struct __Status
{
    GPIO_TypeDef *gpio;
    uint16_t pins;
    char *name;
    uint16_t state;
} Status;

#define IO_NUM 3

Status statuses[IO_NUM] = {
    {GPIOA, GPIO_Pin_1 | GPIO_Pin_2, "A", 0},
    {GPIOC, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, "C", 0},
#if SDI_PRINT == 1
    {GPIOD, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, "D", 0},
#else
    {GPIOD, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7, "D", 0},
#endif
};

void init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOA | RCC_PB2Periph_GPIOB | RCC_PB2Periph_GPIOD | RCC_PB2Periph_USART1, ENABLE);

    for(int i=0;i<3;i++){
        GPIO_InitStructure.GPIO_Pin = statuses[i].pins;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
        GPIO_Init(statuses[i].gpio, &GPIO_InitStructure);
    }
}

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
#if (SDI_PRINT == SDI_PR_OPEN)
    SDI_Printf_Enable();
#else
    USART_Printf_Init(115200);
#endif
    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

    printf( "init\r\n" );

    init();

    Delay_Ms(100);

    for (int i = 0; i < IO_NUM; i++)
    {
        Status *s = &statuses[i];

        s->state = GPIO_ReadInputData(s->gpio);
    }
    
    printf( "start\r\n" );

    while(1)
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
                        printf("%s%d: H\r\n", s->name, j);
                    }
                    else
                    {
                        printf("%s%d: L\r\n", s->name, j);
                    }
                }
            }

            s->state = v;
        }
    }
}
