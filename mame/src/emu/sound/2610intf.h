#pragma once

#ifndef __2610INTF_H__
#define __2610INTF_H__

#include "emu.h"
#include "ay8910.h"

void ym2610_update_request(void *param);

#define MCFG_YM2610_IRQ_HANDLER(_devcb) \
	devcb = &ym2610_device::set_irq_handler(*device, DEVCB2_##_devcb);

class ym2610_device : public device_t,
									public device_sound_interface
{
public:
	ym2610_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	ym2610_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock);

	// static configuration helpers
	template<class _Object> static devcb2_base &set_irq_handler(device_t &device, _Object object) { return downcast<ym2610_device &>(device).m_irq_handler.set_callback(object); }

	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );

	void *_psg();
	void _IRQHandler(int irq);
	void _timer_handler(int c,int count,int clock);
	void _ym2610_update_request();

protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_post_load();
	virtual void device_stop();
	virtual void device_reset();

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

	void *          m_chip;

private:
	// internal state
	sound_stream *  m_stream;
	emu_timer *     m_timer[2];
	void *          m_psg;
	devcb2_write_line m_irq_handler;
};

extern const device_type YM2610;

class ym2610b_device : public ym2610_device
{
public:
	ym2610b_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
};

extern const device_type YM2610B;


#endif /* __2610INTF_H__ */
