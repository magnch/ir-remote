#ifndef SIGNAL_H
#define SIGNAL_H

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>


#define IR_FREQ 37900
#define PERIOD 0.0000263852242744
#define PERIOD_NS 26385

#define PULSE_50 13192
#define PULSE_40 10554
#define PULSE_30 7915

#define PERIOD_TEST 26316
#define PULSE_TEST 13158

int burst(uint32_t dur_us, const struct pwm_dt_spec *ir_led);
int logic_1(const struct pwm_dt_spec *ir_led);
int logic_0(const struct pwm_dt_spec *ir_led);
int start_bit(const struct pwm_dt_spec *ir_led);
int stop_bit(const struct pwm_dt_spec *ir_led);
int ir_send(uint16_t address, uint16_t code, const struct pwm_dt_spec *ir_led);

#endif


/*
    PRØV 30% DUTY CYCLE
    PRØV INVERTED POLARITY
    SEND REN PWM OG MÅL MED AD2
    SKRIV OM BURST OG BRUK k_usleep()
*/