#pragma once

#ifndef __Z80_H__
#define __Z80_H__

enum
{
	NSC800_RSTA = INPUT_LINE_IRQ0 + 1,
	NSC800_RSTB,
	NSC800_RSTC,
	Z80_INPUT_LINE_WAIT,
	Z80_INPUT_LINE_BUSRQ
};

enum
{
	Z80_PC, Z80_SP,
	Z80_A, Z80_B, Z80_C, Z80_D, Z80_E, Z80_H, Z80_L,
	Z80_AF, Z80_BC, Z80_DE, Z80_HL,
	Z80_IX, Z80_IY, Z80_AF2, Z80_BC2, Z80_DE2, Z80_HL2,
	Z80_R, Z80_I, Z80_IM, Z80_IFF1, Z80_IFF2, Z80_HALT,
	Z80_DC0, Z80_DC1, Z80_DC2, Z80_DC3, Z80_WZ,

	Z80_GENPC = STATE_GENPC,
	Z80_GENSP = STATE_GENSP,
	Z80_GENPCBASE = STATE_GENPCBASE
};

class z80_device : public legacy_cpu_device
{
public:
	z80_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_WRITE_LINE_MEMBER( irq_line );

protected:
	z80_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, UINT32 clock, cpu_get_info_func info);
};

extern const device_type Z80;

class nsc800_device : public z80_device
{
public:
	nsc800_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, UINT32 clock);
};

extern const device_type NSC800;

CPU_GET_INFO( z80 );
CPU_GET_INFO( nsc800 );
CPU_DISASSEMBLE( z80 );

void z80_set_cycle_tables(device_t *device, const UINT8 *op, const UINT8 *cb, const UINT8 *ed, const UINT8 *xy, const UINT8 *xycb, const UINT8 *ex);

#endif /* __Z80_H__ */
