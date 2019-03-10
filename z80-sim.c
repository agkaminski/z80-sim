#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "z80-sim.h"

typedef enum { reg_a, reg_b, reg_c, reg_d, reg_e, reg_h, reg_l,
	reg_af, reg_bc, reg_de, reg_hl, reg_sp,
	reg_ixl, reg_ixh, reg_iyl, reg_iyh, reg_ix, reg_iy } reg_t;

typedef struct _operand {
	enum { op_reg, op_imm, op_mem } type;
	union {
		reg_t reg;
		uint8_t imm;
		uint16_t addr;
	};
} operand_t;

cpu_callback_t bus;
cpu_state_t cpu;

struct {
	unsigned int rst:1;
	unsigned int irq:1;
	unsigned int nmi:1;
	unsigned int nmi_trig:1;
} pin;

void cpu_execute(void)
{

}

void cpu_setRst(pin_state_t state)
{
	pin.rst = (state == low) ? low : high;
}

void cpu_setIrq(pin_state_t state)
{
	pin.irq = (state == low) ? low : high;
}

void cpu_setNmi(pin_state_t state)
{
	if (state == low) {
		if (pin.nmi == high) {
			pin.nmi = low;
			pin.nmi_trig = low;
		}
	}
	else {
		pin.nmi = high;
	}
}

void cpu_getState(cpu_state_t *state)
{
	memcpy(state, &cpu, sizeof(cpu));
}

void cpu_init(cpu_callback_t *init)
{
	memcpy(&bus, init, sizeof(bus));

	cpu.pc = 0;
	cpu.r = 0;
	pin.rst = low;
	pin.irq = high;
	pin.nmi = high;
	pin.nmi_trig = high;
}
