/**********************************************************************

    Luxor ABC-99 keyboard and mouse emulation

    Copyright MESS Team.
    Visit http://mamedev.org for licensing and usage restrictions.

*********************************************************************/

#pragma once

#ifndef __ABC99__
#define __ABC99__

#include "emu.h"
#include "cpu/mcs48/mcs48.h"
#include "machine/abckb.h"
#include "sound/speaker.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> abc99_device

class abc99_device :  public device_t,
						public abc_keyboard_interface
{
public:
	// construction/destruction
	abc99_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	// abc_keyboard_interface overrides
	virtual int rxd_r();
	virtual void txd_w(int state);

	DECLARE_INPUT_CHANGED_MEMBER( keyboard_reset );

	DECLARE_WRITE8_MEMBER( z2_led_w );
	DECLARE_WRITE8_MEMBER( z2_p1_w );
	DECLARE_READ8_MEMBER( z2_p2_r );
	DECLARE_READ8_MEMBER( z2_t0_r );
	DECLARE_READ8_MEMBER( z2_t1_r );
	DECLARE_READ8_MEMBER( z5_p1_r );
	DECLARE_WRITE8_MEMBER( z5_p2_w );
	DECLARE_READ8_MEMBER( z5_t1_r );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

private:
	enum
	{
		TIMER_SERIAL,
		TIMER_MOUSE
	};

	enum
	{
		LED_1 = 0,
		LED_2,
		LED_3,
		LED_4,
		LED_5,
		LED_6,
		LED_7,
		LED_8,
		LED_INS,
		LED_ALT,
		LED_CAPS_LOCK
	};

	inline void serial_input();
	inline void serial_clock();
	inline void key_down(int state);
	inline void scan_mouse();

	devcb_resolved_write_line   m_out_clock_func;
	devcb_resolved_write_line   m_out_keydown_func;

	emu_timer *m_serial_timer;
	emu_timer *m_mouse_timer;

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_mousecpu;
	required_device<speaker_sound_device> m_speaker;
	required_ioport m_z14;
	required_ioport m_mouseb;

	int m_si;
	int m_si_en;
	int m_so_z2;
	int m_so_z5;
	int m_keydown;
	int m_t1_z2;
	int m_t1_z5;
	int m_led_en;
	int m_reset;
};


// device type definition
extern const device_type ABC99;



#endif
