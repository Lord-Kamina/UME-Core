//============================================================
//
//  drawd3d.c - Win32 Direct3D HLSL-specific header
//
//============================================================
//
//  Copyright Aaron Giles
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or
//  without modification, are permitted provided that the
//  following conditions are met:
//
//    * Redistributions of source code must retain the above
//      copyright notice, this list of conditions and the
//      following disclaimer.
//    * Redistributions in binary form must reproduce the
//      above copyright notice, this list of conditions and
//      the following disclaimer in the documentation and/or
//      other materials provided with the distribution.
//    * Neither the name 'MAME' nor the names of its
//      contributors may be used to endorse or promote
//      products derived from this software without specific
//      prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY AARON GILES ''AS IS'' AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
//  EVENT SHALL AARON GILES BE LIABLE FOR ANY DIRECT,
//  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  DAMAGE (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
//  IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//============================================================

#ifndef __WIN_D3DHLSL__
#define __WIN_D3DHLSL__

#include "aviio.h"

//============================================================
//  CONSTANTS
//============================================================

#define HLSL_VECTOR         (1)
#define CRT_BLOOM           (1)

//============================================================
//  TYPE DEFINITIONS
//============================================================

namespace d3d
{
class render_target;
class cache_target;
class renderer;

/* hlsl_options is the information about runtime-mutable Direct3D HLSL options */
/* in the future this will be moved into an OSD/emu shared buffer */
struct hlsl_options
{
	bool                    params_dirty;
	float                   shadow_mask_alpha;
	char                    shadow_mask_texture[1024];
	int                     shadow_mask_count_x;
	int                     shadow_mask_count_y;
	float                   shadow_mask_u_size;
	float                   shadow_mask_v_size;
	float                   curvature;
	float                   pincushion;
	float                   scanline_alpha;
	float                   scanline_scale;
	float                   scanline_height;
	float                   scanline_bright_scale;
	float                   scanline_bright_offset;
	float                   scanline_offset;
	float                   defocus[4];
	float                   converge_x[3];
	float                   converge_y[3];
	float                   radial_converge_x[3];
	float                   radial_converge_y[3];
	float                   red_ratio[3];
	float                   grn_ratio[3];
	float                   blu_ratio[3];
	float                   offset[3];
	float                   scale[3];
	float                   power[3];
	float                   floor[3];
	float                   phosphor[3];
	float                   saturation;

	// NTSC
	bool                    yiq_enable;
	float                   yiq_cc;
	float                   yiq_a;
	float                   yiq_b;
	float                   yiq_o;
	float                   yiq_p;
	float                   yiq_n;
	float                   yiq_y;
	float                   yiq_i;
	float                   yiq_q;
	float                   yiq_scan_time;
	int                     yiq_phase_count;

	// Vectors
	float                   vector_length_scale;
	float                   vector_length_ratio;

	// Bloom
	float                   vector_bloom_scale;
	float                   raster_bloom_scale;
	float                   bloom_level0_weight;
	float                   bloom_level1_weight;
	float                   bloom_level2_weight;
	float                   bloom_level3_weight;
	float                   bloom_level4_weight;
	float                   bloom_level5_weight;
	float                   bloom_level6_weight;
	float                   bloom_level7_weight;
	float                   bloom_level8_weight;
	float                   bloom_level9_weight;
	float                   bloom_level10_weight;
};

class shaders
{
public:
	// construction/destruction
	shaders();
	~shaders();

	void init(base *d3dintf, win_window_info *window);

	bool enabled() { return master_enable; }
	void toggle();

	bool vector_enabled() { return master_enable && vector_enable && (bool)HLSL_VECTOR; }
	render_target* get_vector_target();
	void create_vector_target(render_primitive *prim);

	void begin_frame();
	void end_frame();

	void begin_draw();
	void end_draw();

	void init_effect_info(poly_info *poly);
	void render_quad(poly_info *poly, int vertnum);

	bool register_texture(texture_info *texture);
	bool register_prescaled_texture(texture_info *texture);
	bool add_render_target(renderer* d3d, texture_info* info, int width, int height, int xprescale, int yprescale);
	bool add_cache_target(renderer* d3d, texture_info* info, int width, int height, int xprescale, int yprescale, int screen_index);

	void window_save();
	void window_record();
	bool recording() { return avi_output_file != NULL; }

	void avi_update_snap(surface *surface);
	void render_snapshot(surface *surface);
	void record_texture();
	void init_fsfx_quad(void *vertbuf);

	void                    set_texture(texture_info *texture);
	render_target *         find_render_target(texture_info *info);
	void                    remove_render_target(texture_info *texture);
	void                    remove_render_target(int width, int height, UINT32 screen_index, UINT32 page_index);
	void                    remove_render_target(render_target *rt);

	int create_resources(bool reset);
	void delete_resources(bool reset);

	// slider-related functions
	slider_state *init_slider_list();

	struct slider_desc
	{
		const char *        name;
		int                 minval;
		int                 defval;
		int                 maxval;
		int                 step;
		INT32 (*adjustor)(running_machine &, void *, astring *, INT32);
	};

private:
	void                    blit(surface *dst, texture *src, surface *new_dst,
									D3DPRIMITIVETYPE prim_type, UINT32 prim_index, UINT32 prim_count,
									int dstw, int dsth);
	void                    blit(surface *dst, texture *src, surface *new_dst,
									D3DPRIMITIVETYPE prim_type, UINT32 prim_index, UINT32 prim_count);
	void                    enumerate_screens();

	void                    end_avi_recording();
	void                    begin_avi_recording(const char *name);

	bool                    register_texture(texture_info *texture, int width, int height, int xscale, int yscale);

	render_target*          find_render_target(int width, int height, UINT32 screen_index, UINT32 page_index);
	cache_target *          find_cache_target(UINT32 screen_index, int width, int height);
	void                    remove_cache_target(cache_target *cache);

	base *                  d3dintf;                    // D3D interface
	win_window_info *       window;                     // D3D window info

	bool                    master_enable;              // overall enable flag
	bool                    vector_enable;              // vector post-processing enable flag
	bool                    paused;                     // whether or not rendering is currently paused
	int                     num_screens;                // number of emulated physical screens
	int                     curr_screen;                // current screen for render target operations
	int                     curr_frame;                 // current frame (0/1) of a screen for render target operations
	int                     lastidx;                    // index of the last-encountered target
	bool                    write_ini;                  // enable external ini saving
	bool                    read_ini;                   // enable external ini loading
	int                     prescale_force_x;           // prescale force x
	int                     prescale_force_y;           // prescale force y
	int                     prescale_size_x;            // prescale size x
	int                     prescale_size_y;            // prescale size y
	int                     preset;                     // preset, if relevant
	bitmap_argb32           shadow_bitmap;              // shadow mask bitmap for post-processing shader
	texture_info *          shadow_texture;             // shadow mask texture for post-processing shader
	hlsl_options *          options;                    // current uniform state
	D3DPRIMITIVETYPE        vecbuf_type;
	UINT32                  vecbuf_index;
	UINT32                  vecbuf_count;

	avi_file *              avi_output_file;            // AVI file
	bitmap_rgb32            avi_snap;                   // AVI snapshot
	int                     avi_frame;                  // AVI frame
	attotime                avi_frame_period;           // AVI frame period
	attotime                avi_next_frame_time;        // AVI next frame time
	surface *               avi_copy_surface;           // AVI destination surface in system memory
	texture *               avi_copy_texture;           // AVI destination texture in system memory
	surface *               avi_final_target;           // AVI upscaled surface
	texture *               avi_final_texture;          // AVI upscaled texture

	surface *               black_surface;              // black dummy surface
	texture *               black_texture;              // black dummy texture

	bool                    render_snap;                // whether or not to take HLSL post-render snapshot
	bool                    snap_rendered;              // whether we just rendered our HLSL post-render shot or not
	surface *               snap_copy_target;           // snapshot destination surface in system memory
	texture *               snap_copy_texture;          // snapshot destination surface in system memory
	surface *               snap_target;                // snapshot upscaled surface
	texture *               snap_texture;               // snapshot upscaled texture
	int                     snap_width;                 // snapshot width
	int                     snap_height;                // snapshot height
	bool                    lines_pending;              // whether or not we have lines to flush on the next quad

	bool                    initialized;                // whether or not we're initialize

	// HLSL effects
	surface *               backbuffer;                 // pointer to our device's backbuffer
	effect *                curr_effect;                // pointer to the currently active effect object
	effect *                default_effect;             // pointer to the primary-effect object
	effect *                prescale_effect;            // pointer to the prescale-effect object
	effect *                post_effect;                // pointer to the post-effect object
	effect *                pincushion_effect;          // pointer to the pincushion-effect object
	effect *                focus_effect;               // pointer to the focus-effect object
	effect *                phosphor_effect;            // pointer to the phosphor-effect object
	effect *                deconverge_effect;          // pointer to the deconvergence-effect object
	effect *                color_effect;               // pointer to the color-effect object
	effect *                yiq_encode_effect;          // pointer to the YIQ encoder effect object
	effect *                yiq_decode_effect;          // pointer to the YIQ decoder effect object
#if (HLSL_VECTOR || CRT_BLOOM)
	effect *                bloom_effect;               // pointer to the bloom composite effect
	effect *                downsample_effect;          // pointer to the bloom downsample effect
#endif
#if (HLSL_VECTOR)
	effect *                vector_effect;              // pointer to the vector-effect object
#endif
	vertex *                fsfx_vertices;              // pointer to our full-screen-quad object

public:
	render_target *         targethead;
	cache_target *          cachehead;

	static slider_desc      s_sliders[];
	static hlsl_options     s_hlsl_presets[4];
};

};

#endif
