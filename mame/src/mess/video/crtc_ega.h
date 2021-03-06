/**********************************************************************

    IBM EGA CRT Controller emulation

**********************************************************************/

#ifndef __CRTC_EGA__
#define __CRTC_EGA__

#include "emu.h"

#define CRTC_EGA_INTERFACE(name) \
	const crtc_ega_interface (name) =

#define MCFG_CRTC_EGA_ADD(_tag, _clock, _intrf) \
	MCFG_DEVICE_ADD(_tag, CRTC_EGA, _clock) \
	MCFG_DEVICE_CONFIG(_intrf)


class crtc_ega_device;

/* callback definitions */
typedef void * (*crtc_ega_begin_update_func)(crtc_ega_device *device, bitmap_ind16 &bitmap, const rectangle &cliprect);
#define CRTC_EGA_BEGIN_UPDATE(name) void *name(crtc_ega_device *device, bitmap_ind16 &bitmap, const rectangle &cliprect)

typedef void (*crtc_ega_update_row_func)(crtc_ega_device *device, bitmap_ind16 &bitmap,
										const rectangle &cliprect, UINT16 ma, UINT8 ra,
										UINT16 y, UINT8 x_count, INT8 cursor_x, void *param);
#define CRTC_EGA_UPDATE_ROW(name)       void name(crtc_ega_device *device, bitmap_ind16 &bitmap,    \
												const rectangle &cliprect, UINT16 ma, UINT8 ra,                 \
												UINT16 y, UINT8 x_count, INT8 cursor_x, void *param)

typedef void (*crtc_ega_end_update_func)(crtc_ega_device *device, bitmap_ind16 &bitmap, const rectangle &cliprect, void *param);
#define CRTC_EGA_END_UPDATE(name)       void name(crtc_ega_device *device, bitmap_ind16 &bitmap, const rectangle &cliprect, void *param)


/* interface */
struct crtc_ega_interface
{
	const char *m_screen_tag;       /* screen we are acting on */
	int m_hpixels_per_column;       /* number of pixels per video memory address */

	/* if specified, this gets called before any pixel update,
	   optionally return a pointer that will be passed to the
	   update and tear down callbacks */
	crtc_ega_begin_update_func      m_begin_update;

	/* this gets called for every row, the driver must output
	   x_count * hpixels_per_column pixels.
	   cursor_x indicates the character position where the cursor is, or -1
	   if there is no cursor on this row */
	crtc_ega_update_row_func        m_update_row;

	/* if specified, this gets called after all row updating is complete */
	crtc_ega_end_update_func            m_end_update;

	/* if specified, this gets called for every change of the disply enable signal */
	devcb_write_line    m_out_de_func;

	/* if specified, this gets called for every change of the HSYNC signal */
	devcb_write_line    m_out_hsync_func;

	/* if specified, this gets called for every change of the VSYNC signal */
	devcb_write_line    m_out_vsync_func;

	devcb_write_line    m_out_vblank_func;
};


class crtc_ega_device : public device_t,
						public crtc_ega_interface
{
public:
	crtc_ega_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	/* select one of the registers for reading or writing */
	DECLARE_WRITE8_MEMBER( address_w );

	/* read from the currently selected register */
	DECLARE_READ8_MEMBER( register_r );

	/* write to the currently selected register */
	DECLARE_WRITE8_MEMBER( register_w );

	/* return the current value on the MA0-MA15 pins */
	UINT16 get_ma();

	/* return the current value on the RA0-RA4 pins */
	UINT8 get_ra();

	/* simulates the LO->HI clocking of the light pen pin */
	void assert_light_pen_input();

	/* set the clock of the chip */
	void set_clock(int clock);

	/* set number of pixels per video memory address */
	void set_hpixels_per_column(int hpixels_per_column);

	/* updates the screen -- this will call begin_update(), */
	/* followed by update_row() reapeatedly and after all row */
	/* updating is complete, end_update() */
	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();
	virtual void device_post_load();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

private:
	screen_device *m_screen;

	devcb_resolved_write_line   m_res_out_de_func;
	devcb_resolved_write_line   m_res_out_cur_func;
	devcb_resolved_write_line   m_res_out_hsync_func;
	devcb_resolved_write_line   m_res_out_vsync_func;
	devcb_resolved_write_line   m_res_out_vblank_func;

	/* ega/vga register file */
	UINT8   m_horiz_char_total; /* 0x00 */
	UINT8   m_horiz_disp;           /* 0x01 */
	UINT8   m_horiz_blank_start;    /* 0x02 */
	UINT8   m_horiz_blank_end;  /* 0x03/0x05 */
	UINT8   m_ena_vert_access;  /* 0x03 */
	UINT8   m_de_skew;          /* 0x03 */
	UINT8   m_horiz_retr_start; /* 0x04 */
	UINT8   m_horiz_retr_end;       /* 0x05 */
	UINT8   m_horiz_retr_skew;  /* 0x05 */
	UINT16  m_vert_total;           /* 0x06/0x07 */
	UINT8   m_preset_row_scan;  /* 0x08 */
	UINT8   m_byte_panning;     /* 0x08 */
	UINT8   m_max_ras_addr;     /* 0x09 */
	UINT8   m_scan_doubling;        /* 0x09 */
	UINT8   m_cursor_start_ras; /* 0x0a */
	UINT8   m_cursor_disable;       /* 0x0a */
	UINT8   m_cursor_end_ras;       /* 0x0b */
	UINT8   m_cursor_skew;      /* 0x0b */
	UINT16  m_disp_start_addr;  /* 0x0c/0x0d */
	UINT16  m_cursor_addr;      /* 0x0e/0x0f */
	UINT16  m_light_pen_addr;       /* 0x10/0x11 */
	UINT16  m_vert_retr_start;  /* 0x10/0x07 */
	UINT8   m_vert_retr_end;        /* 0x11 */
	UINT8   m_protect;          /* 0x11 */
	UINT8   m_bandwidth;            /* 0x11 */
	UINT16  m_vert_disp_end;        /* 0x12/0x07 */
	UINT8   m_offset;               /* 0x13 */
	UINT8   m_underline_loc;        /* 0x14 */
	UINT16  m_vert_blank_start; /* 0x15/0x07/0x09 */
	UINT8   m_vert_blank_end;       /* 0x16 */
	UINT8   m_mode_control;     /* 0x17 */
	UINT16  m_line_compare;     /* 0x18/0x07/0x09 */

	/* other internal state */
	UINT8   m_register_address_latch;
	bool    m_cursor_state; /* 0 = off, 1 = on */
	UINT8   m_cursor_blink_count;

	/* output signals */
	int     m_cur;
	int     m_hsync;
	int     m_vsync;
	int     m_vblank;
	int     m_de;

	/* internal counters */
	UINT8   m_character_counter;
	UINT8   m_hsync_width_counter;
	UINT16  m_line_counter;
	UINT8   m_raster_counter;
	UINT8   m_vsync_width_counter;
	bool    m_line_enable_ff;       /* Internal flip flop which is set when the line_counter is reset and reset when vert_disp is reached */
	UINT8   m_vsync_ff;
	UINT8   m_adjust_active;
	UINT16  m_line_address;
	INT16   m_cursor_x;

	/* timers */
	static const device_timer_id TIMER_LINE = 0;
	static const device_timer_id TIMER_DE_OFF = 1;
	static const device_timer_id TIMER_CUR_ON = 2;
	static const device_timer_id TIMER_CUR_OFF = 3;
	static const device_timer_id TIMER_HSYNC_ON = 4;
	static const device_timer_id TIMER_HSYNC_OFF = 5;
	static const device_timer_id TIMER_LIGHT_PEN_LATCH = 6;

	emu_timer *m_line_timer;
	emu_timer *m_de_off_timer;
	emu_timer *m_cur_on_timer;
	emu_timer *m_cur_off_timer;
	emu_timer *m_hsync_on_timer;
	emu_timer *m_hsync_off_timer;
	emu_timer *m_light_pen_latch_timer;

	/* computed values - do NOT state save these! */
	UINT16  m_horiz_pix_total;
	UINT16  m_vert_pix_total;
	UINT16  m_max_visible_x;
	UINT16  m_max_visible_y;
	UINT16  m_hsync_on_pos;
	UINT16  m_hsync_off_pos;
	UINT16  m_vsync_on_pos;
	UINT16  m_vsync_off_pos;
	UINT16  m_current_disp_addr;    /* the display address currently drawn */
	UINT8   m_light_pen_latched;
	bool    m_has_valid_parameters;

	void recompute_parameters(bool postload);
	void update_counters();
	void set_de(int state);
	void set_hsync(int state);
	void set_vsync(int state);
	void set_vblank(int state);
	void set_cur(int state);
	void handle_line_timer();
	void update_cursor_state();
};

extern const device_type CRTC_EGA;

#endif
