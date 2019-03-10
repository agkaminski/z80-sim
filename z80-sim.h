#ifndef Z80-SIM_H_
#define Z80-SIM_H_

#include <stdint.h>

typedef void (*cpu_bus_write_t)(uint16_t address, uint8_t data);
typedef uint8_t (*cpu_bus_read_t)(uint16_t address);
typedef enum { low = 0, high } pin_state_t;

typedef struct _cpu_register_bank {
	uint8_t a, f;
	uint8_t b, c;
	uint8_t d, e;
	uint8_t h, l;
} cpu_register_bank_t;

typedef struct _cpu_state {
	_cpu_register_bank bank[2];
	uint8_t i, r;
	uint16_t ix;
	uint16_t iy;
	uint16_t pc;
	uint16_t sp;
} cpu_state_t;

typedef struct _cpu_callback {
	cpu_bus_read_t mem_read;
	cpu_bus_write_t mem_write;
	cpu_bus_read_t io_read;
	cpu_bus_write_t io_write;
} cpu_callback_t;

void cpu_setRst(pin_state_t state);
void cpu_setIrq(pin_state_t state);
void cpu_setNmi(pin_state_t state);

void cpu_getState(cpu_state_t *state);

void cpu_execute(void);

void cpu_init(cpu_callback_t *init);

#endif
