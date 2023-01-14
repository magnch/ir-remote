#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>


#define IR_FREQ 37900
#define PERIOD 0.0000263852242744
#define PERIOD_NS 26385
#define PULSE_50 13192

int burst(uint32_t dur_us, const struct pwm_dt_spec *ir_led);
int logic_1(const struct pwm_dt_spec *ir_led);
int logic_0(const struct pwm_dt_spec *ir_led);
int start_bit(const struct pwm_dt_spec *ir_led);
int stop_bit(const struct pwm_dt_spec *ir_led);
int ir_send(uint64_t hex_code, const struct pwm_dt_spec *ir_led);