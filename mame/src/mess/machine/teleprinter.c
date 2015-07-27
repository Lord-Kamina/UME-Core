// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
#include "teleprinter.h"

#define KEYBOARD_TAG "keyboard"

static const UINT8 teleprinter_font[128*8] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x07,0x07,0x07,0x07,0x00,0x00,0x00,0x00,
	0x38,0x38,0x38,0x38,0x00,0x00,0x00,0x00,
	0x3f,0x3f,0x3f,0x3f,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x07,0x07,0x07,0x07,
	0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x38,0x38,0x38,0x38,0x07,0x07,0x07,0x07,
	0x3f,0x3f,0x3f,0x3f,0x07,0x07,0x07,0x07,
	0x00,0x00,0x00,0x00,0x38,0x38,0x38,0x38,
	0x07,0x07,0x07,0x07,0x38,0x38,0x38,0x38,
	0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,
	0x3f,0x3f,0x3f,0x3f,0x38,0x38,0x38,0x38,
	0x00,0x00,0x00,0x00,0x3f,0x3f,0x3f,0x3f,
	0x07,0x07,0x07,0x07,0x3f,0x3f,0x3f,0x3f,
	0x38,0x38,0x38,0x38,0x3f,0x3f,0x3f,0x3f,
	0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,
	0x00,0x00,0x00,0x00,0x2a,0x15,0x2a,0x15,
	0x2a,0x15,0x2a,0x15,0x00,0x00,0x00,0x00,
	0x3f,0x3f,0x3f,0x3f,0x2a,0x15,0x2a,0x15,
	0x2a,0x15,0x2a,0x15,0x3f,0x3f,0x3f,0x3f,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x08,0x08,0x08,0x08,0x08,0x00,0x08,0x00,
	0x14,0x14,0x14,0x00,0x00,0x00,0x00,0x00,
	0x14,0x14,0x3e,0x14,0x3e,0x14,0x14,0x00,
	0x08,0x3c,0x0a,0x1c,0x28,0x1e,0x08,0x00,
	0x06,0x26,0x10,0x08,0x04,0x32,0x30,0x00,
	0x08,0x14,0x14,0x0c,0x2a,0x12,0x2c,0x00,
	0x08,0x08,0x04,0x00,0x00,0x00,0x00,0x00,
	0x10,0x08,0x04,0x04,0x04,0x08,0x10,0x00,
	0x04,0x08,0x10,0x10,0x10,0x08,0x04,0x00,
	0x00,0x08,0x2a,0x1c,0x2a,0x08,0x00,0x00,
	0x00,0x08,0x08,0x3e,0x08,0x08,0x00,0x00,
	0x00,0x00,0x00,0x00,0x08,0x08,0x04,0x00,
	0x00,0x00,0x00,0x3e,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,
	0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00,
	0x1c,0x22,0x32,0x2a,0x26,0x22,0x1c,0x00,
	0x08,0x0c,0x08,0x08,0x08,0x08,0x1c,0x00,
	0x1c,0x22,0x20,0x18,0x04,0x02,0x3e,0x00,
	0x3e,0x20,0x10,0x18,0x20,0x22,0x1c,0x00,
	0x10,0x18,0x14,0x12,0x3e,0x10,0x10,0x00,
	0x3e,0x02,0x1e,0x20,0x20,0x22,0x1c,0x00,
	0x10,0x08,0x04,0x1c,0x22,0x22,0x1c,0x00,
	0x3e,0x20,0x10,0x08,0x04,0x04,0x04,0x00,
	0x1c,0x22,0x22,0x1c,0x22,0x22,0x1c,0x00,
	0x1c,0x22,0x22,0x1c,0x10,0x08,0x04,0x00,
	0x00,0x00,0x00,0x08,0x00,0x08,0x00,0x00,
	0x00,0x00,0x08,0x00,0x08,0x08,0x04,0x00,
	0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x00,
	0x00,0x00,0x3e,0x00,0x3e,0x00,0x00,0x00,
	0x04,0x08,0x10,0x20,0x10,0x08,0x04,0x00,
	0x1c,0x22,0x20,0x10,0x08,0x00,0x08,0x00,
	0x1c,0x22,0x32,0x2a,0x3a,0x02,0x3c,0x00,
	0x08,0x14,0x22,0x22,0x3e,0x22,0x22,0x00,
	0x1e,0x22,0x22,0x1e,0x22,0x22,0x1e,0x00,
	0x1c,0x22,0x02,0x02,0x02,0x22,0x1c,0x00,
	0x1e,0x24,0x24,0x24,0x24,0x24,0x1e,0x00,
	0x3e,0x02,0x02,0x1e,0x02,0x02,0x3e,0x00,
	0x3e,0x02,0x02,0x1e,0x02,0x02,0x02,0x00,
	0x1c,0x22,0x02,0x02,0x32,0x22,0x3c,0x00,
	0x22,0x22,0x22,0x3e,0x22,0x22,0x22,0x00,
	0x1c,0x08,0x08,0x08,0x08,0x08,0x1c,0x00,
	0x38,0x10,0x10,0x10,0x10,0x12,0x0c,0x00,
	0x22,0x12,0x0a,0x06,0x0a,0x12,0x22,0x00,
	0x02,0x02,0x02,0x02,0x02,0x02,0x3e,0x00,
	0x22,0x36,0x2a,0x2a,0x22,0x22,0x22,0x00,
	0x22,0x22,0x26,0x2a,0x32,0x22,0x22,0x00,
	0x1c,0x22,0x22,0x22,0x22,0x22,0x1c,0x00,
	0x1e,0x22,0x22,0x1e,0x02,0x02,0x02,0x00,
	0x1c,0x22,0x22,0x22,0x2a,0x12,0x2c,0x00,
	0x1e,0x22,0x22,0x1e,0x0a,0x12,0x22,0x00,
	0x1c,0x22,0x02,0x1c,0x20,0x22,0x1c,0x00,
	0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
	0x22,0x22,0x22,0x22,0x22,0x22,0x1c,0x00,
	0x22,0x22,0x22,0x14,0x14,0x08,0x08,0x00,
	0x22,0x22,0x22,0x2a,0x2a,0x2a,0x14,0x00,
	0x22,0x22,0x14,0x08,0x14,0x22,0x22,0x00,
	0x22,0x22,0x22,0x14,0x08,0x08,0x08,0x00,
	0x3e,0x20,0x10,0x08,0x04,0x02,0x3e,0x00,
	0x0e,0x02,0x02,0x02,0x02,0x02,0x0e,0x00,
	0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00,
	0x38,0x20,0x20,0x20,0x20,0x20,0x38,0x00,
	0x08,0x1c,0x2a,0x08,0x08,0x08,0x08,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x00,
	0x04,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1c,0x20,0x3c,0x22,0x3c,0x00,
	0x02,0x02,0x1e,0x22,0x22,0x22,0x1e,0x00,
	0x00,0x00,0x3c,0x02,0x02,0x02,0x3c,0x00,
	0x20,0x20,0x3c,0x22,0x22,0x22,0x3c,0x00,
	0x00,0x00,0x1c,0x22,0x3e,0x02,0x1c,0x00,
	0x18,0x04,0x0e,0x04,0x04,0x04,0x04,0x00,
	0x00,0x00,0x3c,0x22,0x22,0x3c,0x20,0x18,
	0x02,0x02,0x1e,0x22,0x22,0x22,0x22,0x00,
	0x08,0x00,0x0c,0x08,0x08,0x08,0x1c,0x00,
	0x10,0x00,0x18,0x10,0x10,0x10,0x12,0x0c,
	0x02,0x02,0x22,0x12,0x0e,0x16,0x22,0x00,
	0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x00,
	0x00,0x00,0x16,0x2a,0x2a,0x2a,0x2a,0x00,
	0x00,0x00,0x1a,0x26,0x22,0x22,0x22,0x00,
	0x00,0x00,0x1c,0x22,0x22,0x22,0x1c,0x00,
	0x00,0x00,0x1e,0x22,0x22,0x1e,0x02,0x02,
	0x00,0x00,0x3c,0x22,0x22,0x3c,0x20,0x20,
	0x00,0x00,0x34,0x0c,0x04,0x04,0x04,0x00,
	0x00,0x00,0x3c,0x02,0x1c,0x20,0x1e,0x00,
	0x08,0x08,0x1c,0x08,0x08,0x08,0x10,0x00,
	0x00,0x00,0x22,0x22,0x22,0x32,0x2c,0x00,
	0x00,0x00,0x22,0x22,0x22,0x14,0x08,0x00,
	0x00,0x00,0x22,0x22,0x2a,0x2a,0x14,0x00,
	0x00,0x00,0x22,0x14,0x08,0x14,0x22,0x00,
	0x00,0x00,0x22,0x22,0x14,0x08,0x04,0x02,
	0x00,0x00,0x3e,0x10,0x08,0x04,0x3e,0x00,
	0x10,0x08,0x08,0x04,0x08,0x08,0x10,0x00,
	0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
	0x04,0x08,0x08,0x10,0x08,0x08,0x04,0x00,
	0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x2a,0x15,0x2a,0x15,0x2a,0x15,0x2a,0x15
};

teleprinter_device::teleprinter_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: generic_terminal_device(mconfig, TELEPRINTER, "Teleprinter", tag, owner, clock, "teleprinter", __FILE__)
{
}

void teleprinter_device::scroll_line()
{
	memmove(m_buffer,m_buffer+TELEPRINTER_WIDTH,(TELEPRINTER_HEIGHT-1)*TELEPRINTER_WIDTH);
	memset(m_buffer + TELEPRINTER_WIDTH*(TELEPRINTER_HEIGHT-1),0x20,TELEPRINTER_WIDTH);
}

void teleprinter_device::write_char(UINT8 data) {
	m_buffer[(TELEPRINTER_HEIGHT-1)*TELEPRINTER_WIDTH+m_x_pos] = data;
	m_x_pos++;
	if (m_x_pos >= TELEPRINTER_WIDTH)
	{
		m_x_pos = 0;
		scroll_line();
	}
}

void teleprinter_device::clear() {
	memset(m_buffer,0,TELEPRINTER_WIDTH*TELEPRINTER_HEIGHT);
	m_x_pos = 0;
}

void teleprinter_device::term_write(UINT8 data)
{
	switch(data) {
		case 10: m_x_pos = 0;
				scroll_line();
				break;
		case 13: m_x_pos = 0; break;
		case  9: m_x_pos = (m_x_pos & 0xf8) + 8;
				if (m_x_pos >= TELEPRINTER_WIDTH)
					m_x_pos = TELEPRINTER_WIDTH-1;

				break;
		case 16: break;
		default: write_char(data); break;
	}
}

/***************************************************************************
    VIDEO HARDWARE
***************************************************************************/
UINT32 teleprinter_device::tp_update(screen_device &device, bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
	UINT8 code;
	int y, c, x, b;

	for (y = 0; y < TELEPRINTER_HEIGHT; y++)
	{
		for (c = 0; c < 8; c++)
		{
			int horpos = 0;
			for (x = 0; x < TELEPRINTER_WIDTH; x++)
			{
				code = teleprinter_font[(m_buffer[y*TELEPRINTER_WIDTH + x]  & 0x7f) *8 + c];
				for (b = 0; b < 8; b++)
				{
					bitmap.pix32(y*8 + c, horpos++) =  (code >> b) & 0x01 ? 0 : 0x00ffffff;
				}
			}
		}
	}
	return 0;
}

/***************************************************************************
    VIDEO HARDWARE
***************************************************************************/
MACHINE_CONFIG_FRAGMENT( generic_teleprinter )
	MCFG_SCREEN_ADD(TELEPRINTER_SCREEN_TAG, RASTER)
	MCFG_SCREEN_REFRESH_RATE(50)
	MCFG_SCREEN_VBLANK_TIME(ATTOSECONDS_IN_USEC(2500)) /* not accurate */
	MCFG_SCREEN_SIZE(TELEPRINTER_WIDTH*8, TELEPRINTER_HEIGHT*8)
	MCFG_SCREEN_VISIBLE_AREA(0, TELEPRINTER_WIDTH*8-1, 0, TELEPRINTER_HEIGHT*8-1)
	MCFG_SCREEN_UPDATE_DEVICE(DEVICE_SELF, teleprinter_device, tp_update)
	MCFG_DEVICE_ADD(KEYBOARD_TAG, GENERIC_KEYBOARD, 0)
	MCFG_GENERIC_KEYBOARD_CB(WRITE8(generic_terminal_device, kbd_put))
MACHINE_CONFIG_END

machine_config_constructor teleprinter_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME(generic_teleprinter);
}

/*-------------------------------------------------
    device_reset - device-specific reset
-------------------------------------------------*/

void teleprinter_device::device_reset()
{
	clear();
	generic_terminal_device::device_reset();
}

const device_type TELEPRINTER = &device_creator<teleprinter_device>;
