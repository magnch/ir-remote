#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include "../inc/signal.h"


#define POWER 0xE0E040BF


static const struct gpio_dt_spec leds[] = {GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios), 
                                           GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios), 
                                           GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios), 
                                           GPIO_DT_SPEC_GET(DT_ALIAS(led3), gpios)};


static const struct gpio_dt_spec buttons[] = {GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios),
                                              GPIO_DT_SPEC_GET(DT_ALIAS(sw1), gpios),
                                              GPIO_DT_SPEC_GET(DT_ALIAS(sw2), gpios),
                                              GPIO_DT_SPEC_GET(DT_ALIAS(sw3), gpios)};


static const struct pwm_dt_spec ir_led = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));


void main(void) {

    int ret;

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

    while(1) {

        if(gpio_pin_get_dt(&buttons[0]) == 1) {
            while(gpio_pin_get_dt(&buttons[0]) == 1) {

            }
           ret = ir_send(POWER, &ir_led);
           if(ret) {
            printk("IR_send failed \n");
           }
        }
        
        if(gpio_pin_get_dt(&buttons[1]) == 1) {

            // TEST
            ret = pwm_set_dt(&ir_led, NSEC_PER_SEC, NSEC_PER_SEC);
            if(ret) {
                printk("Failed to set PWM in test \n");
            }

            k_msleep(MSEC_PER_SEC);

            ret = pwm_set_dt(&ir_led, 0, 0);
            if(ret) {
                printk("Failed to set PWM to 0 in test \n");
            }
        }

        if(gpio_pin_get_dt(&buttons[2]) == 1) {
            // VOLUME UP BUTTON
        }

        if(gpio_pin_get_dt(&buttons[3]) == 1) {
            // VOLUME DOWN BUTTON
        }
    }
}