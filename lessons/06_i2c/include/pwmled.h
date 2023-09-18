
#define NUM_STEPS 100U
#define SLEEP_DELTA_MSEC 5U

extern const struct pwm_dt_spec fading_led ;

extern uint32_t pulse_width_nsec;
extern uint32_t pulse_width_delta_nsec;
extern uint32_t steps_taken;
extern bool increasing_intensity;

void led_delta_timer_handler(struct k_timer *timer_info);