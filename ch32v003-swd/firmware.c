#include "ch32v003fun.h"
#include "ch32v003_GPIO_branchless.h"
#include <stdio.h>
#include <stdbool.h>

/* Global define */
typedef struct __Status
{
	uint8_t gpio;
	char *name;
	uint8_t npins;
	uint8_t pins_no[8];
	uint16_t pins[8];
	uint8_t state[8];
} Status;

#define IO_NUM 3

Status statuses[IO_NUM] = {
	{
		GPIO_port_A,
		"A",
		2,
		{1, 2},
		{GPIOv_from_PORT_PIN(GPIO_port_A, 1), GPIOv_from_PORT_PIN(GPIO_port_A, 2)},
		{0, 0},
	},
	{
		GPIO_port_C,
		"C",
		8,
		{0, 1, 2, 3, 4, 5, 6, 7},
		{GPIOv_from_PORT_PIN(GPIO_port_C, 0), GPIOv_from_PORT_PIN(GPIO_port_C, 1), GPIOv_from_PORT_PIN(GPIO_port_C, 2), GPIOv_from_PORT_PIN(GPIO_port_C, 3), GPIOv_from_PORT_PIN(GPIO_port_C, 4), GPIOv_from_PORT_PIN(GPIO_port_C, 5), GPIOv_from_PORT_PIN(GPIO_port_C, 6), GPIOv_from_PORT_PIN(GPIO_port_C, 7)},
		{0, 0, 0, 0, 0, 0, 0, 0},
	},
	// D1: SWDIO, D7: NRST
	{
		GPIO_port_D,
		"D",
		6,
		{0, 2, 3, 4, 5, 6},
		{GPIOv_from_PORT_PIN(GPIO_port_D, 0), GPIOv_from_PORT_PIN(GPIO_port_D, 2), GPIOv_from_PORT_PIN(GPIO_port_D, 3), GPIOv_from_PORT_PIN(GPIO_port_D, 4), GPIOv_from_PORT_PIN(GPIO_port_D, 5), GPIOv_from_PORT_PIN(GPIO_port_D, 6)},
		{0, 0, 0, 0, 0, 0},
	},
};

void setup()
{
	GPIO_port_enable(GPIO_port_A);
	GPIO_port_enable(GPIO_port_C);
	GPIO_port_enable(GPIO_port_D);

	for (int i = 0; i < IO_NUM; i++)
	{
		Status *s = &statuses[i];

		for (int j = 0; j < s->npins; j++)
		{
			uint8_t pin = s->pins[j];
			GPIO_pinMode(pin, GPIO_pinMode_I_pullUp, GPIO_Speed_10MHz);
		}
	}

	Delay_Ms(1);

	for (int i = 0; i < IO_NUM; i++)
	{
		Status *s = &statuses[i];

		for (int j = 0; j < s->npins; j++)
		{
			uint8_t pin = s->pins[j];
			bool v = GPIO_digitalRead(pin);
			s->state[j] = v;
		}
	}
}

void main_loop()
{
	for (int i = 0; i < IO_NUM; i++)
	{
		Status *s = &statuses[i];

		for (int j = 0; j < 8; j++)
		{
			uint8_t pin = s->pins[j];
			uint8_t pin_no = s->pins_no[j];
			bool v = GPIO_digitalRead(pin);

			if (v != s->state[j])
			{
				if (v)
				{
					printf("%s%d: H\r\n", s->name, pin_no);
				}
				else
				{
					printf("%s%d: L\r\n", s->name, pin_no);
				}
			}
			s->state[j] = v;
		}
	}

	Delay_Ms(1);
}

int main()
{
	SystemInit();
	funGpioInitAll();

	setup();
	printf("init\r\n");

	while (1)
		main_loop();
}
