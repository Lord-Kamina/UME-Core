

#include "includes/kaypro.h"




/***********************************************************

    PIO

    Port B is unused on both PIOs

************************************************************/

WRITE_LINE_MEMBER(kaypro_state::kaypro_interrupt)
{
	m_maincpu->set_input_line(0, state);
}

READ8_MEMBER( kaypro_state::pio_system_r )
{
	UINT8 data = 0;

	/* centronics busy */
	data |= m_centronics->not_busy_r() << 3;

	/* PA7 is pulled high */
	data |= 0x80;

	return data;
}

WRITE8_MEMBER( kaypro_state::common_pio_system_w )
{
/*  d7 bank select
    d6 disk drive motors - (0=on)
    d5 double-density enable (0=double density)
    d4 Centronics strobe
    d2 side select (1=side 1)
    d1 drive B
    d0 drive A */

	/* get address space */
	address_space &mem = m_maincpu->space(AS_PROGRAM);

	if (data & 0x80)
	{
		mem.unmap_readwrite (0x0000, 0x3fff);
		mem.install_read_bank (0x0000, 0x0fff, "bank1");
		membank("bank1")->set_base(memregion("maincpu")->base());
		mem.install_readwrite_handler (0x3000, 0x3fff, read8_delegate(FUNC(kaypro_state::kaypro_videoram_r), this), write8_delegate(FUNC(kaypro_state::kaypro_videoram_w), this));
	}
	else
	{
		mem.unmap_readwrite(0x0000, 0x3fff);
		mem.install_read_bank (0x0000, 0x3fff, "bank2");
		mem.install_write_bank (0x0000, 0x3fff, "bank3");
		membank("bank2")->set_base(memregion("rambank")->base());
		membank("bank3")->set_base(memregion("rambank")->base());
	}

	wd17xx_dden_w(m_fdc, BIT(data, 5));

	m_centronics->strobe_w(BIT(data, 4));

	if (BIT(data, 0))
		wd17xx_set_drive(m_fdc, 0);

	if (BIT(data, 1))
		wd17xx_set_drive(m_fdc, 1);

	output_set_value("ledA", BIT(data, 0));     /* LEDs in artwork */
	output_set_value("ledB", BIT(data, 1));

	/* CLEAR_LINE means to turn motors on */
	floppy_mon_w(floppy_get_device(machine(), 0), BIT(data, 6) ? ASSERT_LINE : CLEAR_LINE);
	floppy_mon_w(floppy_get_device(machine(), 1), BIT(data, 6) ? ASSERT_LINE : CLEAR_LINE);

	m_system_port = data;
}

WRITE8_MEMBER( kaypro_state::kayproii_pio_system_w )
{
	common_pio_system_w(space, offset, data);

	/* side select */
	wd17xx_set_side(m_fdc, !BIT(data, 2));
}

WRITE8_MEMBER( kaypro_state::kaypro4_pio_system_w )
{
	common_pio_system_w(space, offset, data);

	/* side select */
	wd17xx_set_side(m_fdc, BIT(data, 2));
}

const z80pio_interface kayproii_pio_g_intf =
{
	DEVCB_CPU_INPUT_LINE("maincpu", INPUT_LINE_IRQ0),
	DEVCB_NULL,
	DEVCB_DEVICE_MEMBER("centronics", centronics_device, write),
	DEVCB_NULL,         /* portA ready active callback */
	DEVCB_NULL,
	DEVCB_NULL,
	DEVCB_NULL          /* portB ready active callback */
};

const z80pio_interface kayproii_pio_s_intf =
{
	DEVCB_CPU_INPUT_LINE("maincpu", INPUT_LINE_IRQ0),
	DEVCB_DRIVER_MEMBER(kaypro_state, pio_system_r),    /* read printer status */
	DEVCB_DRIVER_MEMBER(kaypro_state, kayproii_pio_system_w),   /* activate various internal devices */
	DEVCB_NULL,         /* portA ready active callback */
	DEVCB_NULL,
	DEVCB_NULL,
	DEVCB_NULL          /* portB ready active callback */
};

const z80pio_interface kaypro4_pio_s_intf =
{
	DEVCB_CPU_INPUT_LINE("maincpu", INPUT_LINE_IRQ0),
	DEVCB_DRIVER_MEMBER(kaypro_state, pio_system_r),    /* read printer status */
	DEVCB_DRIVER_MEMBER(kaypro_state, kaypro4_pio_system_w),    /* activate various internal devices */
	DEVCB_NULL,         /* portA ready active callback */
	DEVCB_NULL,
	DEVCB_NULL,
	DEVCB_NULL          /* portB ready active callback */
};

/***********************************************************

    KAYPRO2X SYSTEM PORT

    The PIOs were replaced by a few standard 74xx chips

************************************************************/

READ8_MEMBER( kaypro_state::kaypro2x_system_port_r )
{
	UINT8 data = m_centronics->busy_r() << 6;
	return (m_system_port & 0xbf) | data;
}

WRITE8_MEMBER( kaypro_state::kaypro2x_system_port_w )
{
/*  d7 bank select
    d6 alternate character set (write only)
    d5 double-density enable
    d4 disk drive motors (1=on)
    d3 Centronics strobe
    d2 side select (appears that 0=side 1?)
    d1 drive B
    d0 drive A */

	/* get address space */
	address_space &mem = m_maincpu->space(AS_PROGRAM);

	if (BIT(data, 7))
	{
		mem.unmap_readwrite (0x0000, 0x3fff);
		mem.install_read_bank (0x0000, 0x1fff, "bank1");
		membank("bank1")->set_base(memregion("maincpu")->base());
	}
	else
	{
		mem.unmap_readwrite (0x0000, 0x3fff);
		mem.install_read_bank (0x0000, 0x3fff, "bank2");
		mem.install_write_bank (0x0000, 0x3fff, "bank3");
		membank("bank2")->set_base(memregion("rambank")->base());
		membank("bank3")->set_base(memregion("rambank")->base());
	}

	wd17xx_dden_w(m_fdc, BIT(data, 5));

	m_centronics->strobe_w(BIT(data, 3));

	if (BIT(data, 0))
		wd17xx_set_drive(m_fdc, 0);
	else
	if (BIT(data, 1))
		wd17xx_set_drive(m_fdc, 1);

	wd17xx_set_side(m_fdc, BIT(data, 2) ? 0 : 1);

	output_set_value("ledA", BIT(data, 0));     /* LEDs in artwork */
	output_set_value("ledB", BIT(data, 1));

	/* CLEAR_LINE means to turn motors on */
	floppy_mon_w(floppy_get_device(machine(), 0), BIT(data, 4) ? CLEAR_LINE : ASSERT_LINE);
	floppy_mon_w(floppy_get_device(machine(), 1), BIT(data, 4) ? CLEAR_LINE : ASSERT_LINE);

	m_system_port = data;
}



/***********************************************************************

    SIO

    On Kaypro2x, Channel B on both SIOs is hardwired to 300 baud.

    Both devices on sio2 (printer and modem) are not emulated.

************************************************************************/

/* Set baud rate. bits 0..3 Rx and Tx are tied together. Baud Rate Generator is a AY-5-8116, SMC8116, WD1943, etc.
    00h    50
    11h    75
    22h    110
    33h    134.5
    44h    150
    55h    300
    66h    600
    77h    1200
    88h    1800
    99h    2000
    AAh    2400
    BBh    3600
    CCh    4800
    DDh    7200
    EEh    9600
    FFh    19200 */


const z80sio_interface kaypro_sio_intf =
{
	DEVCB_DRIVER_LINE_MEMBER(kaypro_state,kaypro_interrupt),    /* interrupt handler */
	DEVCB_NULL,         /* DTR changed handler */
	DEVCB_NULL,         /* RTS changed handler */
	DEVCB_NULL,         /* BREAK changed handler */
	DEVCB_NULL,         /* transmit handler - which channel is this for? */
	DEVCB_NULL          /* receive handler - which channel is this for? */
};

READ8_MEMBER(kaypro_state::kaypro_sio_r)
{
	if (!offset)
		return dynamic_cast<z80sio_device*>(machine().device("z80sio"))->data_read(0);
	else
	if (offset == 1)
//      return z80sio_d_r(machine().device("z80sio"), 1);
		return kay_kbd_d_r(machine());
	else
	if (offset == 2)
		return dynamic_cast<z80sio_device*>(machine().device("z80sio"))->control_read(0);
	else
//      return z80sio_c_r(machine().device("z80sio"), 1);
		return kay_kbd_c_r(machine());
}

WRITE8_MEMBER(kaypro_state::kaypro_sio_w)
{
	if (!offset)
		dynamic_cast<z80sio_device*>(machine().device("z80sio"))->data_write(0, data);
	else
	if (offset == 1)
//      z80sio_d_w(machine().device("z80sio"), 1, data);
		kay_kbd_d_w(machine(), data);
	else
	if (offset == 2)
		dynamic_cast<z80sio_device*>(machine().device("z80sio"))->control_write(0, data);
	else
		dynamic_cast<z80sio_device*>(machine().device("z80sio"))->control_write(1, data);
}


/*************************************************************************************

    Floppy DIsk

    If DRQ or IRQ is set, and cpu is halted, the NMI goes low.
    Since the HALT occurs last (and has no callback mechanism), we need to set
    a short delay, to give time for the processor to execute the HALT before NMI
    becomes active.

*************************************************************************************/

void kaypro_state::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	switch (id)
	{
	case TIMER_FLOPPY:
		if (m_maincpu->state_int(Z80_HALT))
			m_maincpu->set_input_line(INPUT_LINE_NMI, ASSERT_LINE);
		break;
	default:
		assert_always(FALSE, "Unknown id in kaypro_state::device_timer");
	}
}

WRITE_LINE_MEMBER( kaypro_state::kaypro_fdc_intrq_w )
{
	if (state)
		timer_set(attotime::from_usec(25), TIMER_FLOPPY);
	else
		m_maincpu->set_input_line(INPUT_LINE_NMI, CLEAR_LINE);
}

WRITE_LINE_MEMBER( kaypro_state::kaypro_fdc_drq_w )
{
	if (state)
		timer_set(attotime::from_usec(25), TIMER_FLOPPY);
	else
		m_maincpu->set_input_line(INPUT_LINE_NMI, CLEAR_LINE);

}

const wd17xx_interface kaypro_wd1793_interface =
{
	DEVCB_NULL,
	DEVCB_DRIVER_LINE_MEMBER(kaypro_state, kaypro_fdc_intrq_w),
	DEVCB_DRIVER_LINE_MEMBER(kaypro_state, kaypro_fdc_drq_w),
	{FLOPPY_0, FLOPPY_1, NULL, NULL}
};


/***********************************************************

    Machine

************************************************************/
MACHINE_START_MEMBER(kaypro_state,kayproii)
{
	m_pio_s->strobe_a(0);
}

MACHINE_RESET_MEMBER(kaypro_state,kayproii)
{
	MACHINE_RESET_CALL_MEMBER(kay_kbd);
}

MACHINE_RESET_MEMBER(kaypro_state,kaypro2x)
{
	address_space &space = m_maincpu->space(AS_PROGRAM);
	kaypro2x_system_port_w(space, 0, 0x80);
	MACHINE_RESET_CALL_MEMBER(kay_kbd);
}

/***********************************************************

    Quickload

    This loads a .COM file to address 0x100 then jumps
    there. Sometimes .COM has been renamed to .CPM to
    prevent windows going ballistic. These can be loaded
    as well.

************************************************************/

QUICKLOAD_LOAD_MEMBER( kaypro_state, kayproii )
{
	address_space &space = m_maincpu->space(AS_PROGRAM);
	UINT8 *RAM = memregion("rambank")->base();
	UINT16 i;
	UINT8 data;

	/* Load image to the TPA (Transient Program Area) */
	for (i = 0; i < quickload_size; i++)
	{
		if (image.fread( &data, 1) != 1) return IMAGE_INIT_FAIL;

		RAM[i+0x100] = data;
	}

	common_pio_system_w(space, 0, m_system_port & 0x7f);  // switch TPA in
	RAM[0x80]=0;                            // clear out command tail
	RAM[0x81]=0;
	m_maincpu->set_pc(0x100);                // start program
	return IMAGE_INIT_PASS;
}

QUICKLOAD_LOAD_MEMBER( kaypro_state, kaypro2x )
{
	address_space &space = m_maincpu->space(AS_PROGRAM);
	UINT8 *RAM = memregion("rambank")->base();
	UINT16 i;
	UINT8 data;

	for (i = 0; i < quickload_size; i++)
	{
		if (image.fread( &data, 1) != 1) return IMAGE_INIT_FAIL;

		RAM[i+0x100] = data;
	}

	kaypro2x_system_port_w(space, 0, m_system_port & 0x7f);
	RAM[0x80]=0;
	RAM[0x81]=0;
	m_maincpu->set_pc(0x100);
	return IMAGE_INIT_PASS;
}
