//
// Created by lauril on 11/21/16.
//


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vm.h"

#include "nrf_delay.h"
#include "bsp.h"

static const uint8_t leds_list[LEDS_NUMBER] = LEDS_LIST;

void vm_init(VM *vm, int *code, int code_size)
{
    vm->code = code;
    vm->code_size = code_size;
}

void vm_free(VM *vm)
{
    free(vm);
}

VM *vm_create(int *code, int code_size)
{
    VM *vm = calloc(1, sizeof(VM));
    vm_init(vm, code, code_size);
    return vm;
}

int vm_exec(VM *vm, int startip)
{

    int ip;         // instruction pointer register
    int sp;         // stack pointer register
    int addr = 0;

    ip = startip;
    sp = -1;
    int opcode = vm->code[ip];

    while (opcode != HALT && ip < vm->code_size) {
        ip++; //jump to next instruction or to operand
        switch (opcode) {
            case DELAY:
            	vm->stack[++sp] = vm->code[ip++];
                break;
            case LED:
            	addr = vm->stack[sp--];
            	for (int i = 0; i < LEDS_NUMBER; i++)
            	        {
            	            LEDS_INVERT(1 << leds_list[i]);
            	            nrf_delay_ms(addr);
            	        }
                break;
            case REPEAT:
            	ip = startip;
            	break;
            default:
                return -1;
        }
        opcode = vm->code[ip];
    }
    return 1;

}


