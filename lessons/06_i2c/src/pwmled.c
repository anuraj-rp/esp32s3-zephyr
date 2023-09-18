
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>

#include "pwmled.h"

const struct pwm_dt_spec fading_led =
  PWM_DT_SPEC_GET(DT_NODELABEL(fading_led));

uint32_t pulse_width_nsec = 0U;
uint32_t pulse_width_delta_nsec = 0U;
uint32_t steps_taken = 0U;
bool increasing_intensity = true;

void led_delta_timer_handler(struct k_timer *timer_info)
{
    int ret;
    if (increasing_intensity) {
    if (steps_taken < NUM_STEPS) {
      ret = pwm_set_pulse_dt(&fading_led, pulse_width_nsec);
      steps_taken++;
      pulse_width_nsec += pulse_width_delta_nsec;
    } else {
      increasing_intensity = false;
      steps_taken--;
      pulse_width_nsec -= pulse_width_delta_nsec;
    }
  } else {
    if (steps_taken > 0) {
      ret = pwm_set_pulse_dt(&fading_led, pulse_width_nsec);
      steps_taken--;
      pulse_width_nsec -= pulse_width_delta_nsec;
    } else {
      increasing_intensity = true;
      steps_taken++;
      pulse_width_nsec += pulse_width_delta_nsec;
    }
  }
}
