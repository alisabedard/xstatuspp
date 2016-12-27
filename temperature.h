// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_TEMPERATURE_H
#define XSTATUS_TEMPERATURE_H
#include <xcb/xcb.h>
#include "libjb/JBDim.h"
namespace xstatus {
	namespace temperature {
		// Returns x offset for next item
		uint16_t draw(xcb_connection_t * xc,
			const uint16_t offset, const JBDim font_size);
	}
}
#endif//!XSTATUS_TEMPERATURE_H
