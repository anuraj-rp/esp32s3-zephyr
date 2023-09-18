#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#include <stdio.h>

static const struct gpio_dt_spec led = 
	GPIO_DT_SPEC_GET(DT_NODELABEL(blinking_led), gpios);


void main(void)
{
	if(!device_is_ready(led.port))
	{
		printf("GPIO CTRL not ready!");
	}

	int ret;
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

	
	while(true)
	{
		ret = gpio_pin_toggle_dt(&led);
		k_msleep(500);
		printf("Hello World! %s\n", CONFIG_BOARD);
	}
}
