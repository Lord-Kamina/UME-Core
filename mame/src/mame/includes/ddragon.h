/*************************************************************************

    Double Dragon & Double Dragon II (but also China Gate)

*************************************************************************/
#include "sound/msm5205.h"

class ddragon_state : public driver_device
{
public:
	ddragon_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_rambase(*this, "rambase"),
		m_bgvideoram(*this, "bgvideoram"),
		m_fgvideoram(*this, "fgvideoram"),
		m_spriteram(*this, "spriteram"),
		m_scrollx_lo(*this, "scrollx_lo"),
		m_scrolly_lo(*this, "scrolly_lo"),
		m_darktowr_mcu_ports(*this, "darktowr_mcu"),
		m_maincpu(*this, "maincpu"),
		m_soundcpu(*this, "soundcpu"),
		m_subcpu(*this, "sub"),
		m_adpcm1(*this, "adpcm1"),
		m_adpcm2(*this, "adpcm2") { }

	/* memory pointers */
	optional_shared_ptr<UINT8> m_rambase;
	required_shared_ptr<UINT8> m_bgvideoram;
	required_shared_ptr<UINT8> m_fgvideoram;
	required_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_scrollx_lo;
	required_shared_ptr<UINT8> m_scrolly_lo;
	optional_shared_ptr<UINT8> m_darktowr_mcu_ports;
//  UINT8 *        m_paletteram;  // currently this uses generic palette handling
//  UINT8 *        m_paletteram_2;    // currently this uses generic palette handling

	/* video-related */
	tilemap_t        *m_fg_tilemap;
	tilemap_t        *m_bg_tilemap;
	UINT8          m_technos_video_hw;
	UINT8          m_scrollx_hi;
	UINT8          m_scrolly_hi;

	/* misc */
	UINT8          m_dd_sub_cpu_busy;
	UINT8          m_sprite_irq;
	UINT8          m_sound_irq;
	UINT8          m_ym_irq;
	UINT8          m_adpcm_sound_irq;
	UINT32         m_adpcm_pos[2];
	UINT32         m_adpcm_end[2];
	UINT8          m_adpcm_idle[2];
	int            m_adpcm_data[2];

	/* for Sai Yu Gou Ma Roku */
	int            m_adpcm_addr;
	int            m_i8748_P1;
	int            m_i8748_P2;
	int            m_pcm_shift;
	int            m_pcm_nibble;
	int            m_mcu_command;
#if 0
	int            m_m5205_clk;
#endif

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_soundcpu;
	optional_device<cpu_device> m_subcpu;
	optional_device<msm5205_device> m_adpcm1;
	optional_device<msm5205_device> m_adpcm2;
	DECLARE_WRITE_LINE_MEMBER(irq_handler);
	DECLARE_WRITE8_MEMBER(ddragon_bgvideoram_w);
	DECLARE_WRITE8_MEMBER(ddragon_fgvideoram_w);
	DECLARE_CUSTOM_INPUT_MEMBER(sub_cpu_busy);
	DECLARE_WRITE8_MEMBER(ddragon_bankswitch_w);
	DECLARE_WRITE8_MEMBER(toffy_bankswitch_w);
	DECLARE_READ8_MEMBER(darktowr_mcu_bank_r);
	DECLARE_WRITE8_MEMBER(darktowr_mcu_bank_w);
	DECLARE_WRITE8_MEMBER(darktowr_bankswitch_w);
	DECLARE_WRITE8_MEMBER(ddragon_interrupt_w);
	DECLARE_WRITE8_MEMBER(ddragon2_sub_irq_ack_w);
	DECLARE_WRITE8_MEMBER(ddragon2_sub_irq_w);
	DECLARE_WRITE8_MEMBER(darktowr_mcu_w);
	DECLARE_READ8_MEMBER(ddragon_hd63701_internal_registers_r);
	DECLARE_WRITE8_MEMBER(ddragon_hd63701_internal_registers_w);
	DECLARE_READ8_MEMBER(ddragon_spriteram_r);
	DECLARE_WRITE8_MEMBER(ddragon_spriteram_w);
	DECLARE_WRITE8_MEMBER(dd_adpcm_w);
	DECLARE_READ8_MEMBER(dd_adpcm_status_r);
	DECLARE_WRITE8_MEMBER(ddragonba_port_w);
	DECLARE_DRIVER_INIT(toffy);
	DECLARE_DRIVER_INIT(darktowr);
	DECLARE_DRIVER_INIT(ddragon2);
	DECLARE_DRIVER_INIT(ddragon);
	DECLARE_DRIVER_INIT(ddragon6809);
	TILEMAP_MAPPER_MEMBER(background_scan);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_16color_tile_info);
	DECLARE_MACHINE_START(ddragon);
	DECLARE_MACHINE_RESET(ddragon);
	DECLARE_VIDEO_START(ddragon);
	UINT32 screen_update_ddragon(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_DEVICE_CALLBACK_MEMBER(ddragon_scanline);
	void draw_sprites(  bitmap_ind16 &bitmap,const rectangle &cliprect );
	int scanline_to_vcount( int scanline );
	void dd_adpcm_int(msm5205_device *device, int chip);
	DECLARE_WRITE_LINE_MEMBER(dd_adpcm_int_1);
	DECLARE_WRITE_LINE_MEMBER(dd_adpcm_int_2);
};
