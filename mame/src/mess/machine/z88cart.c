/*********************************************************************

    z88cart.c

    Z88 cartridge slots emulation

*********************************************************************/

#include "emu.h"
#include "z88cart.h"
#include "emuopts.h"


/***************************************************************************
    PARAMETERS
***************************************************************************/

#define CLOSE_FLAP_TIME     attotime::from_msec(200)

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

const device_type Z88CART_SLOT = &device_creator<z88cart_slot_device>;


//**************************************************************************
//    Z88 cartridges Interface
//**************************************************************************

//-------------------------------------------------
//  device_z88cart_interface - constructor
//-------------------------------------------------

device_z88cart_interface::device_z88cart_interface(const machine_config &mconfig, device_t &device)
	: device_slot_card_interface(mconfig, device)
{
}


//-------------------------------------------------
//  ~device_z88cart_interface - destructor
//-------------------------------------------------

device_z88cart_interface::~device_z88cart_interface()
{
}


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  z88cart_slot_device - constructor
//-------------------------------------------------
z88cart_slot_device::z88cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
		device_t(mconfig, Z88CART_SLOT, "Z88 Cartridge Slot", tag, owner, clock),
		device_image_interface(mconfig, *this),
		device_slot_interface(mconfig, *this)
{
}

//-------------------------------------------------
//  z88cart_slot_device - destructor
//-------------------------------------------------

z88cart_slot_device::~z88cart_slot_device()
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void z88cart_slot_device::device_start()
{
	m_cart = dynamic_cast<device_z88cart_interface *>(get_card_device());

	// resolve callbacks
	m_out_flp_func.resolve(m_out_flp_cb, *this);

	m_flp_timer = timer_alloc(TIMER_FLP_CLEAR);
	m_flp_timer->reset();
}

//-------------------------------------------------
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void z88cart_slot_device::device_config_complete()
{
	// inherit a copy of the static data
	const z88cart_interface *intf = reinterpret_cast<const z88cart_interface *>(static_config());
	if (intf != NULL)
	{
		*static_cast<z88cart_interface *>(this) = *intf;
	}

	// or initialize to defaults if none provided
	else
	{
		memset(&m_out_flp_cb, 0, sizeof(m_out_flp_cb));
	}

	// set brief and instance name
	update_names();
}


//-------------------------------------------------
//  device_timer - handler timer events
//-------------------------------------------------

void z88cart_slot_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	if (id == TIMER_FLP_CLEAR)
	{
		// close the flap
		m_out_flp_func(CLEAR_LINE);
	}
}

/*-------------------------------------------------
    call load
-------------------------------------------------*/

bool z88cart_slot_device::call_load()
{
	if (m_cart)
	{
		offs_t read_length = 0;
		UINT8 *cart_base = m_cart->get_cart_base();

		if (cart_base != NULL)
		{
			if (software_entry() == NULL)
			{
				read_length = length();
				fread(cart_base + (m_cart->get_cart_size() - read_length), read_length);
			}
			else
			{
				read_length = get_software_region_length("rom");
				memcpy(cart_base + (m_cart->get_cart_size() - read_length), get_software_region("rom"), read_length);
			}
		}
		else
			return IMAGE_INIT_FAIL;
	}

	// open the flap
	m_out_flp_func(ASSERT_LINE);

	// setup the timer for close the flap
	m_flp_timer->adjust(CLOSE_FLAP_TIME);

	return IMAGE_INIT_PASS;
}


/*-------------------------------------------------
    call_unload
-------------------------------------------------*/

void z88cart_slot_device::call_unload()
{
	if (m_cart)
		memset(m_cart->get_cart_base(), 0xff, m_cart->get_cart_size());

	// open the flap
	m_out_flp_func(ASSERT_LINE);

	// setup the timer for close the flap
	m_flp_timer->adjust(CLOSE_FLAP_TIME);
}


/*-------------------------------------------------
    call softlist load
-------------------------------------------------*/

bool z88cart_slot_device::call_softlist_load(char *swlist, char *swname, rom_entry *start_entry)
{
	load_software_part_region(this, swlist, swname, start_entry );
	return TRUE;
}

/*-------------------------------------------------
    get default card software
-------------------------------------------------*/

const char * z88cart_slot_device::get_default_card_software(const machine_config &config, emu_options &options)
{
	return software_get_default_slot(config, options, this, "128krom");
}


/*-------------------------------------------------
    read
-------------------------------------------------*/

READ8_MEMBER(z88cart_slot_device::read)
{
	if (m_cart)
		return m_cart->read(space, offset);
	else
		return 0xff;
}


/*-------------------------------------------------
    write
-------------------------------------------------*/

WRITE8_MEMBER(z88cart_slot_device::write)
{
	if (m_cart)
		m_cart->write(space, offset, data);
}
