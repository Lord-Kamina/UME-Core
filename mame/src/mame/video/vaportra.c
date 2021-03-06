/***************************************************************************

   Vapour Trail Video emulation - Bryan McPhail, mish@tendril.co.uk

****************************************************************************

    2 Data East 55 chips for playfields (same as Dark Seal, etc)
    1 Data East MXC-06 chip for sprites (same as Bad Dudes, etc)

***************************************************************************/

#include "emu.h"
#include "video/deco16ic.h"
#include "includes/vaportra.h"
#include "video/decmxc06.h"

/******************************************************************************/

WRITE16_MEMBER(vaportra_state::vaportra_priority_w)
{
	COMBINE_DATA(&m_priority[offset]);
}

/******************************************************************************/

void vaportra_state::update_24bitcol( int offset )
{
	UINT8 r, g, b;

	r = (m_generic_paletteram_16[offset] >> 0) & 0xff;
	g = (m_generic_paletteram_16[offset] >> 8) & 0xff;
	b = (m_generic_paletteram2_16[offset] >> 0) & 0xff;

	palette_set_color(machine(), offset, MAKE_RGB(r,g,b));
}

WRITE16_MEMBER(vaportra_state::vaportra_palette_24bit_rg_w)
{
	COMBINE_DATA(&m_generic_paletteram_16[offset]);
	update_24bitcol(offset);
}

WRITE16_MEMBER(vaportra_state::vaportra_palette_24bit_b_w)
{
	COMBINE_DATA(&m_generic_paletteram2_16[offset]);
	update_24bitcol(offset);
}

/******************************************************************************/


UINT32 vaportra_state::screen_update_vaportra(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	address_space &space = machine().driver_data()->generic_space();
	UINT16 flip = deco16ic_pf_control_r(m_deco_tilegen1, space, 0, 0xffff);
	int pri = m_priority[0] & 0x03;

	flip_screen_set(!BIT(flip, 7));
	deco16ic_pf_update(m_deco_tilegen1, 0, 0);
	deco16ic_pf_update(m_deco_tilegen2, 0, 0);

	machine().device<deco_mxc06_device>("spritegen")->set_pri_type(1); // force priorities to be handled in a different way for this driver for now

	/* Draw playfields */
	if (pri == 0)
	{
		deco16ic_tilemap_2_draw(m_deco_tilegen2, bitmap, cliprect, TILEMAP_DRAW_OPAQUE, 0);
		deco16ic_tilemap_1_draw(m_deco_tilegen2, bitmap, cliprect, 0, 0);
		machine().device<deco_mxc06_device>("spritegen")->draw_sprites(machine(), bitmap, cliprect, m_spriteram->buffer(), 0, m_priority[1], 0x0f);
		deco16ic_tilemap_2_draw(m_deco_tilegen1, bitmap, cliprect, 0, 0);
	}
	else if (pri == 1)
	{
		deco16ic_tilemap_1_draw(m_deco_tilegen2, bitmap, cliprect, TILEMAP_DRAW_OPAQUE, 0);
		deco16ic_tilemap_2_draw(m_deco_tilegen2, bitmap, cliprect, 0, 0);
		machine().device<deco_mxc06_device>("spritegen")->draw_sprites(machine(), bitmap, cliprect, m_spriteram->buffer(), 0, m_priority[1], 0x0f);
		deco16ic_tilemap_2_draw(m_deco_tilegen1, bitmap, cliprect, 0, 0);
	}
	else if (pri == 2)
	{
		deco16ic_tilemap_2_draw(m_deco_tilegen2, bitmap, cliprect, TILEMAP_DRAW_OPAQUE, 0);
		deco16ic_tilemap_2_draw(m_deco_tilegen1, bitmap, cliprect, 0, 0);
		machine().device<deco_mxc06_device>("spritegen")->draw_sprites(machine(), bitmap, cliprect, m_spriteram->buffer(), 0, m_priority[1], 0x0f);
		deco16ic_tilemap_1_draw(m_deco_tilegen2, bitmap, cliprect, 0, 0);
	}
	else
	{
		deco16ic_tilemap_1_draw(m_deco_tilegen2, bitmap, cliprect, TILEMAP_DRAW_OPAQUE, 0);
		deco16ic_tilemap_2_draw(m_deco_tilegen1, bitmap, cliprect, 0, 0);
		machine().device<deco_mxc06_device>("spritegen")->draw_sprites(machine(), bitmap, cliprect, m_spriteram->buffer(), 0, m_priority[1], 0x0f);
		deco16ic_tilemap_2_draw(m_deco_tilegen2, bitmap, cliprect, 0, 0);
	}

	machine().device<deco_mxc06_device>("spritegen")->draw_sprites(machine(), bitmap, cliprect, m_spriteram->buffer(), 1, m_priority[1], 0x0f);
	deco16ic_tilemap_1_draw(m_deco_tilegen1, bitmap, cliprect, 0, 0);
	return 0;
}
