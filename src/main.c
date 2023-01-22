////////////// PRE-PROCESSOR /////////////////////////////////////////////////////

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include "../inc/signal.h"

#define ADDRESS 0x0707

#define POWER 0xFD02
#define SOURCE 0xFE01
#define VOL_UP 0xF807
#define VOL_DOWN 0xF40B


////////////// SETUP ////////////////////////////////////////////////////////////

static const struct gpio_dt_spec leds[] = {GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios), 
                                           GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios), 
                                           GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios), 
                                           GPIO_DT_SPEC_GET(DT_ALIAS(led3), gpios)};


static const struct gpio_dt_spec buttons[] = {GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios),
                                              GPIO_DT_SPEC_GET(DT_ALIAS(sw1), gpios),
                                              GPIO_DT_SPEC_GET(DT_ALIAS(sw2), gpios),
                                              GPIO_DT_SPEC_GET(DT_ALIAS(sw3), gpios)};


static const struct pwm_dt_spec ir_led = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));

////////////// MAIN FUNCTION /////////////////////////////////////////////////////

void main(void) {

    int ret;
    uint64_t timer = k_uptime_get();

    for(int i = 0; i < 4; i++) {
        
        ret = gpio_pin_configure_dt(&leds[i], GPIO_OUTPUT_INACTIVE);
	    if (ret < 0) {
            printk("Failed to configure LED %i \n", i);
            return;
        }
        
        ret = gpio_pin_configure_dt(&buttons[i], GPIO_INPUT);
        if (ret < 0) {
            printk("Failed to configure button %i \n", i);
            return;
        }
    }

////////////// MAIN LOOP /////////////////////////////////////////////////////

    while(1) {
        
        // Status LED
        if(k_uptime_get() - timer >= MSEC_PER_SEC) {
            gpio_pin_toggle_dt(&leds[0]);
            timer = k_uptime_get();
        }

        // Button 1
        if(gpio_pin_get_dt(&buttons[0]) == 1) {
            while(gpio_pin_get_dt(&buttons[0]) == 1) {

            }
            ret = ir_send(ADDRESS, POWER, &ir_led);
            if(ret) {
                printk("IR_send failed \n");
            }
        }
        
        // Button 2
        if(gpio_pin_get_dt(&buttons[1]) == 1) {
            while(gpio_pin_get_dt(&buttons[1]) == 1) {

            }
            ret = ir_send(ADDRESS, SOURCE, &ir_led);
            if(ret) {
                printk("IR_send failed \n");
            }
        }

        // Button 3
        if(gpio_pin_get_dt(&buttons[2]) == 1) {
            while(gpio_pin_get_dt(&buttons[2]) == 1) {

            }
            ret = ir_send(ADDRESS, VOL_UP, &ir_led);
            if(ret) {
                printk("IR_send failed \n");
            }
        }

        // Button 4
        if(gpio_pin_get_dt(&buttons[3]) == 1) {
            while(gpio_pin_get_dt(&buttons[3]) == 1) {

            }
            ret = ir_send(ADDRESS, VOL_DOWN, &ir_led);
            if(ret) {
                printk("IR_send failed \n");
            }
        }
    }
}