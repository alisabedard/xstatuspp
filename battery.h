// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_BATTERY_H
#define XSTATUS_BATTERY_H
#include <xcb/xcb.h>
#include "font.h"
namespace xstatus {
	namespace battery {
		void draw(xcb_connection_t * xc, const Font & f,
			const uint16_t start, const uint16_t end);
	}
}
#endif//!XSTATUS_BATTERY_H
