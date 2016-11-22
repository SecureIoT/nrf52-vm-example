//
// Created by lauril on 11/21/16.
//

#include <stdio.h>
#include <stdbool.h>
#include "vm.h"

#include "nrf_delay.h"
#include "bsp.h"

int blink[] = {
		DELAY, 500,
        LED,
		REPEAT
};



int main(void)
{
    VM *vm = vm_create(blink, sizeof(blink));

    /* Configure LED-pins as outputs. */
    LEDS_CONFIGURE(LEDS_MASK);

    /* Toggle LEDs. */
    vm_exec(vm, 0);
    vm_free(vm);
}




