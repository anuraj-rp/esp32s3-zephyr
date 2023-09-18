#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#include <stdio.h>

#define LED_BLU 2

static const struct device *gpio_ctrl_dev0 = DEVICE_DT_GET(DT_NODELABEL(gpio0));

// static const struct device *gpio_ctrl_dev1 = DEVICE_DT_GET(DT_NODELABEL(gpio1));


void main(void)
{
	if(!device_is_ready(gpio_ctrl_dev0))
	{
		printf("GPIO CTRL not ready!");
	}

	int ret;
	ret = gpio_pin_configure(gpio_ctrl_dev0, LED_BLU, GPIO_OUTPUT_ACTIVE);
	
	while(true)
	{
		ret = gpio_pin_set_raw(gpio_ctrl_dev0, LED_BLU, 1);

		k_msleep(500);
		ret = gpio_pin_set_raw(gpio_ctrl_dev0, LED_BLU, 0);

		k_msleep(500);
		printf("Hello World! %s\n", CONFIG_BOARD);
	}
}
