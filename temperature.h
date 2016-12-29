// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_TEMPERATURE_H
#define XSTATUS_TEMPERATURE_H
#include <xcb/xcb.h>
#include "font.h"
namespace xstatus {
	namespace temperature {
		// Returns x offset for next item
		int draw(xcb_connection_t * xc,
			const unsigned short offset, const Font & font);
	}
}
#endif//!XSTATUS_TEMPERATURE_H
