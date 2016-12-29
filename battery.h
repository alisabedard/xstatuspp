// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_BATTERY_H
#define XSTATUS_BATTERY_H
#include <xcb/xcb.h>
#include "font.h"
namespace xstatus {
	namespace battery {
		void draw(xcb_connection_t * xc, const Font & f,
			const unsigned short start, const unsigned short end);
	}
}
#endif//!XSTATUS_BATTERY_H
