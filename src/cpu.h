#include <stdint.h>

typedef struct cpu_type *CPU;
typedef void (*Instruction)(CPU cpu,
                             void *,
                             void *,
                             uint16_t op);

CPU cpu_create();

void cpu_destroy();

void cpu_inc_pc_byte(CPU cpu);

void cpu_inc_pc_word(CPU cpu);

void cpu_ld_reg(CPU cpu,
                uint8_t src,
                uint8_t dst);

void cpu_or_reg(CPU cpu,
                uint8_t src,
                uint8_t dst);                

void cpu_set_pc(CPU cpu,
                uint16_t pc);

void cpu_set_reg(CPU cpu,
                 uint8_t n,
                 uint8_t value);

void cpu_set_reg_delay(CPU cpu,
                       uint8_t value);

void cpu_set_reg_timer(CPU cpu,
                       uint8_t value);

void cpu_set_reg_I(CPU cpu,
                   uint16_t value);

Instruction *cpu_get_instruction(CPU cpu,
                                  uint16_t instr);

uint8_t cpu_get_reg(CPU cpu,
                    uint8_t n);

uint8_t cpu_get_reg_delay(CPU cpu);

uint8_t cpu_get_reg_timer(CPU cpu);

uint16_t cpu_get_reg_I(CPU cpu);

uint16_t cpu_get_pc(CPU cpu);

uint16_t cpu_get_sp(CPU cpu);

uint16_t cpu_stack_pop(CPU cpu);

void cpu_stack_push(CPU cpu,
                    uint16_t value);

void cpu_stack_print(CPU cpu);
