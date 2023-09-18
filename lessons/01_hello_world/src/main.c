#include <zephyr/kernel.h>
#include <stdio.h>

void main(void)
{
	while(true)
	{
		k_msleep(1000);
		printf("Hello World! %s\n", CONFIG_BOARD);
	}
}
