#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>

#include <stdio.h>

#include "pwmled.h"

#define MPU6050_AD0 5


#define MPU6050_REG_CHIP_ID		0x75
#define MPU6050_CHIP_ID			0x68
#define MPU9250_CHIP_ID			0x71

#define MPU6050_REG_GYRO_CFG		0x1B
#define MPU6050_GYRO_FS_SHIFT		3

#define MPU6050_REG_ACCEL_CFG		0x1C
#define MPU6050_ACCEL_FS_SHIFT		3

#define MPU6050_REG_INT_EN		0x38
#define MPU6050_DRDY_EN			BIT(0)

#define MPU6050_REG_DATA_START		0x3B

#define MPU6050_REG_PWR_MGMT1		0x6B
#define MPU6050_SLEEP_EN		BIT(6)

static const struct device *gpio_dev0 = 
  DEVICE_DT_GET(DT_NODELABEL(gpio0));


K_TIMER_DEFINE(led_delta_timer, led_delta_timer_handler, NULL);

void main(void)
{
	if(!device_is_ready(fading_led.dev))
	{
		printk("Error: PWM device not ready\n");
		while(true);
	}
  if(!device_is_ready(gpio_dev0))
  {
    printk("Error: GPIO not ready\n");
    while(true);
  }

  pulse_width_delta_nsec = fading_led.period / NUM_STEPS;

  int ret;
  ret = gpio_pin_configure(gpio_dev0, MPU6050_AD0, GPIO_OUTPUT_INACTIVE);

	k_timer_start(&led_delta_timer, 
					K_MSEC(SLEEP_DELTA_MSEC), 
					K_MSEC(SLEEP_DELTA_MSEC));

  //MPU6050 settings
  uint8_t chipId = 0;
  const struct device *i2c_dev0 = DEVICE_DT_GET(DT_NODELABEL(i2c0));
  int nack;
  uint8_t value;   

  nack = i2c_reg_read_byte(i2c_dev0,MPU6050_CHIP_ID,MPU6050_REG_CHIP_ID, &value);
  if(!nack)
  {
    printf("I2C WAMI Value %x\n", value);
  }
  else
  {
    printf("Error Read: I2C\n");
    while(true);
  }
  nack = i2c_reg_update_byte(i2c_dev0, MPU6050_CHIP_ID, MPU6050_REG_PWR_MGMT1, MPU6050_SLEEP_EN, 0);

  while (true)
  {
		k_msleep(1000);


    int16_t buf[7];
    nack = i2c_burst_read(i2c_dev0, MPU6050_CHIP_ID, MPU6050_REG_DATA_START, (uint8_t *)buf, 14);

    if(!nack)
    {
      for(int i = 0; i < 7; i++)
      {
        printf("SensorReading[%d] = %x\n", i, buf[i]);
      }
    }
    else
    {
      printf("Sensor Reading Error\n:");
    }
    
		printf("Hello World! %s\n", CONFIG_BOARD);
  }
  
}
