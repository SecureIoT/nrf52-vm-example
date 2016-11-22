//
// Created by lauril on 11/21/16.
//


#ifndef VM_H_
#define VM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_STACK_SIZE      1000
#define DEFAULT_CALL_STACK_SIZE 100
#define DEFAULT_NUM_LOCALS      10

typedef enum {
    NOOP    = 0,
    PERIOD  = 1,   // int add
    LED     = 2,
    DELAY   = 3,
	REPEAT	= 4,
    HALT    = 18
} VM_CODE;

typedef struct {
    int returnip;
    int locals[DEFAULT_NUM_LOCALS];
} Context;

typedef struct {
    int *code;
    int code_size;

    // Operand stack, grows upwards
    int stack[DEFAULT_STACK_SIZE];
} VM;

VM *vm_create(int *code, int code_size);
void vm_free(VM *vm);
void vm_init(VM *vm, int *code, int code_size);
int vm_exec(VM *vm, int startip);

#ifdef __cplusplus
}
#endif

#endif

