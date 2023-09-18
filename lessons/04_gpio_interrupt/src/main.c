#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#include <stdio.h>

static const struct gpio_dt_spec led = 
	GPIO_DT_SPEC_GET(DT_NODELABEL(blinking_led), gpios);

static const struct gpio_dt_spec button = 
	GPIO_DT_SPEC_GET(DT_NODELABEL(button), gpios);

static struct gpio_callback button_cb_data;

void button_pressed(const struct device* dev, 
					struct gpio_callback *cb,
					uint32_t pins)
{
	int ret;
	ret = gpio_pin_toggle_dt(&led);
	if(ret != 0){
		printk("Could not toggle LED\n");
	}
}

void main(void)
{
	if(!device_is_ready(led.port) || !device_is_ready(button.port))
	{
		printf("GPIO CTRL or Button not ready!");
		while(true);
	}

	int ret;
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);

	ret = gpio_pin_interrupt_configure_dt(&button, 
											GPIO_INT_EDGE_TO_ACTIVE);

	gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
	
	gpio_add_callback(button.port, &button_cb_data);

	while(true)
	{
		k_msleep(500);
		printf("Hello World! %s\n", CONFIG_BOARD);
	}
}
