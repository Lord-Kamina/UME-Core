/*****************************************************************************
 *
 * video/vic4567.h
 *
 ****************************************************************************/

#ifndef __VIC4567_H__
#define __VIC4567_H__

#include "devcb.h"


/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

enum vic3_type
{
	VIC4567_NTSC,
	VIC4567_PAL
};

struct vic3_interface
{
	const char         *screen_tag;
	const char         *cpu_tag;

	vic3_type          vic_type;

	devcb_read8        x_cb;
	devcb_read8        y_cb;
	devcb_read8        button_cb;

	devcb_read8        dma_read;
	devcb_read8        dma_read_color;
	devcb_write_line   irq;

	devcb_write8       port_changed;

	devcb_read8        c64_mem_r;
};


#define SPRITE_BASE_X_SIZE      24
#define SPRITE_BASE_Y_SIZE      21

struct vic3_sprite
{
	int x, y;

	int repeat;                         /* expand, line once drawn */
	int line;                           /* 0 not painting, else painting */

	/* buffer for currently painted line */
	int paintedline[8];
	UINT8 bitmap[8][SPRITE_BASE_X_SIZE * 2 / 8 + 1  /*for simplier sprite collision detection*/];
};


/***************************************************************************
    CONSTANTS
***************************************************************************/

#define VIC6567_CLOCK       (1022700 /* = 8181600 / 8) */ )
#define VIC6569_CLOCK       ( 985248 /* = 7881984 / 8) */ )

#define VIC6567_CYCLESPERLINE   65
#define VIC6569_CYCLESPERLINE   63

#define VIC6567_LINES       263
#define VIC6569_LINES       312

#define VIC6567_VRETRACERATE    (59.8245100906698 /* = 1022700 / (65 * 263) */ )
#define VIC6569_VRETRACERATE    (50.1245421245421 /* =  985248 / (63 * 312) */ )

#define VIC6567_HRETRACERATE    (VIC6567_CLOCK / VIC6567_CYCLESPERLINE)
#define VIC6569_HRETRACERATE    (VIC6569_CLOCK / VIC6569_CYCLESPERLINE)

#define VIC2_HSIZE      320
#define VIC2_VSIZE      200

#define VIC6567_VISIBLELINES    235
#define VIC6569_VISIBLELINES    284

#define VIC6567_FIRST_DMA_LINE  0x30
#define VIC6569_FIRST_DMA_LINE  0x30

#define VIC6567_LAST_DMA_LINE   0xf7
#define VIC6569_LAST_DMA_LINE   0xf7

#define VIC6567_FIRST_DISP_LINE 0x29
#define VIC6569_FIRST_DISP_LINE 0x10

#define VIC6567_LAST_DISP_LINE  (VIC6567_FIRST_DISP_LINE + VIC6567_VISIBLELINES - 1)
#define VIC6569_LAST_DISP_LINE  (VIC6569_FIRST_DISP_LINE + VIC6569_VISIBLELINES - 1)

#define VIC6567_RASTER_2_EMU(a) ((a >= VIC6567_FIRST_DISP_LINE) ? (a - VIC6567_FIRST_DISP_LINE) : (a + 222))
#define VIC6569_RASTER_2_EMU(a) (a - VIC6569_FIRST_DISP_LINE)

#define VIC6567_FIRSTCOLUMN 50
#define VIC6569_FIRSTCOLUMN 50

#define VIC6567_VISIBLECOLUMNS  418
#define VIC6569_VISIBLECOLUMNS  403

#define VIC6567_X_2_EMU(a)  (a)
#define VIC6569_X_2_EMU(a)  (a)

#define VIC6567_STARTVISIBLELINES ((VIC6567_LINES - VIC6567_VISIBLELINES)/2)
#define VIC6569_STARTVISIBLELINES 16 /* ((VIC6569_LINES - VIC6569_VISIBLELINES)/2) */

#define VIC6567_FIRSTRASTERLINE 34
#define VIC6569_FIRSTRASTERLINE 0

#define VIC6567_COLUMNS 512
#define VIC6569_COLUMNS 504


#define VIC6567_STARTVISIBLECOLUMNS ((VIC6567_COLUMNS - VIC6567_VISIBLECOLUMNS)/2)
#define VIC6569_STARTVISIBLECOLUMNS ((VIC6569_COLUMNS - VIC6569_VISIBLECOLUMNS)/2)

#define VIC6567_FIRSTRASTERCOLUMNS 412
#define VIC6569_FIRSTRASTERCOLUMNS 404

#define VIC6569_FIRST_X 0x194
#define VIC6567_FIRST_X 0x19c

#define VIC6569_FIRST_VISIBLE_X 0x1e0
#define VIC6567_FIRST_VISIBLE_X 0x1e8

#define VIC6569_MAX_X 0x1f7
#define VIC6567_MAX_X 0x1ff

#define VIC6569_LAST_VISIBLE_X 0x17c
#define VIC6567_LAST_VISIBLE_X 0x184

#define VIC6569_LAST_X 0x193
#define VIC6567_LAST_X 0x19b

/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

class vic3_device : public device_t,
					public vic3_interface
{
public:
	vic3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~vic3_device() {}

	DECLARE_WRITE8_MEMBER(port_w);
	DECLARE_WRITE8_MEMBER(palette_w);
	DECLARE_READ8_MEMBER(port_r);

	void raster_interrupt_gen();
	UINT32 video_update(bitmap_ind16 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();

private:
	// internal state

	inline int getforeground(int y, int x);
	inline int getforeground16(int y, int x);
	void set_interrupt(int mask);
	void clear_interrupt(int mask);
	void draw_character(int ybegin, int yend, int ch, int yoff, int xoff, UINT16 *color, int start_x, int end_x);
	void draw_character_multi(int ybegin, int yend, int ch, int yoff, int xoff, int start_x, int end_x);
	void draw_bitmap(int ybegin, int yend, int ch, int yoff, int xoff, int start_x, int end_x);
	void draw_bitmap_multi(int ybegin, int yend, int ch, int yoff, int xoff, int start_x, int end_x);
	void draw_sprite_code(int y, int xbegin, int code, int color, int start_x, int end_x);
	void draw_sprite_code_multi(int y, int xbegin, int code, int prior, int start_x, int end_x);
	void sprite_collision(int nr, int y, int x, int mask);
	void draw_sprite(int nr, int yoff, int ybegin, int yend, int start_x, int end_x);
	void draw_sprite_multi(int nr, int yoff, int ybegin, int yend, int start_x, int end_x);
	void drawlines(int first, int last, int start_x, int end_x);
	void vic2_drawlines(int first, int last, int start_x, int end_x);
	void interlace_draw_block(int x, int y, int offset);
	void draw_block(int x, int y, int offset);
	void draw_bitplanes();

	TIMER_CALLBACK_MEMBER(timer_timeout);

	vic3_type  m_type;

	screen_device *m_main_screen;         // screen which sets bitmap properties

	device_t *m_cpu;

	UINT8 m_reg[0x80];
	int m_on;                             /* rastering of the screen */

	int m_lines;

	UINT16 m_chargenaddr, m_videoaddr, m_bitmapaddr;

	bitmap_ind16 *m_bitmap;
	int m_x_begin, m_x_end;
	int m_y_begin, m_y_end;

	UINT16 m_c64_bitmap[2], m_bitmapmulti[4], m_mono[2], m_multi[4], m_ecmcolor[2], m_colors[4], m_spritemulti[4];

	int m_lastline, m_rasterline;

	int m_interlace;
	int m_columns, m_rows;

	/* background/foreground for sprite collision */
	UINT8 *m_screen[216], m_shift[216];

	/* convert multicolor byte to background/foreground for sprite collision */
	UINT8 m_foreground[256];
	UINT16 m_expandx[256];
	UINT16 m_expandx_multi[256];

	/* converts sprite multicolor info to info for background collision checking */
	UINT8 m_multi_collision[256];

	vic3_sprite m_sprites[8];

	/* DMA */
	devcb_resolved_read8    m_dma_read;
	devcb_resolved_read8    m_dma_read_color;

	/* IRQ */
	devcb_resolved_write_line m_interrupt;

	/* Port Changed */
	devcb_resolved_write8   m_port_changed;

	/* lightpen */
	devcb_resolved_read8 m_lightpen_button_cb;
	devcb_resolved_read8 m_lightpen_x_cb;
	devcb_resolved_read8 m_lightpen_y_cb;

	/* C64 memory access */
	devcb_resolved_read8      m_c64_mem_r;

	/* palette - vic3 specific items (the ones above are used for VIC II as well) */
	UINT8 m_palette_red[0x100];
	UINT8 m_palette_green[0x100];
	UINT8 m_palette_blue[0x100];
	int m_palette_dirty;
};

extern const device_type VIC3;


#define MCFG_VIC3_ADD(_tag, _interface) \
	MCFG_DEVICE_ADD(_tag, VIC3, 0) \
	MCFG_DEVICE_CONFIG(_interface)



#endif /* __VIC4567_H__ */
