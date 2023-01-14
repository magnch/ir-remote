

/* SAMSUNG PROTOCOL:

    Start bit - Address - Address - Data - Inverse Data - Stop bit
    1 bit - 8 bit - 8 bit - 8 bit - 8 bit - 1 bit

    Start bit goes HIGH for 4.5 ms and LOW for 4.5 ms
    Stop bit goes HIGH for 590 μs and LOW for 590 μs

    Frequency of transmission is 37.9 kHz

    Logical 1: 560 μs pulse - 1690 μs pause
    Logical 0: 560 μs pulse - 560 μs pause

*/

#include "../inc/signal.h"



int burst(uint32_t dur_us, const struct pwm_dt_spec *ir_led) {

    int ret = pwm_set_dt(ir_led, PERIOD_NS, PULSE_50);
    if(ret) {
        return -1;
    }
    k_usleep(dur_us);
    ret = pwm_set_dt(ir_led, 0, 0);
    if(ret) {
        return -1;
    }
    return 0;
    
}

int logic_1(const struct pwm_dt_spec *ir_led) {
    int ret = burst(560, ir_led);
    if(ret) {
        return -1;
    }
    k_usleep(1690);
    return 0;
}

int logic_0(const struct pwm_dt_spec *ir_led) {
    int ret = burst(560, ir_led);
    if(ret) {
        return -1;
    }
    k_usleep(560);
    return 0;
}

int start_bit(const struct pwm_dt_spec *ir_led) {
    int ret = burst(4500, ir_led);
    if(ret) {
        return -1;
    }
    k_usleep(4500);
    return 0;
}

int stop_bit(const struct pwm_dt_spec *ir_led) {
    int ret = burst(590, ir_led);
    if(ret) {
        return -1;
    }
    k_usleep(590);
    return 0;
}

int ir_send(uint64_t hex_code, const struct pwm_dt_spec *ir_led) {
    int ret = start_bit(ir_led);
    if(ret) {
        return -1;
    }
    for (int i = 0; i < 32; i++) {
        if (hex_code & (1<<i)) {
            ret = logic_1(ir_led);
            if(ret) {
                return -1;
            }
        }
        else {
            ret = logic_0(ir_led);
            if(ret){
                return -1;
            }
        }
    }
    ret = stop_bit(ir_led);
    if(ret){
        return -1;
    }
    return 0;
}