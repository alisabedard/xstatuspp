// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_CLOCK_H
#define XSTATUS_CLOCK_H
#include "font.h"
#include "xdata.h"
namespace xstatus {
	namespace clock {
		uint16_t draw(xcb_connection_t * xc, const Font & f);
	}
}
#endif//!XSTATUS_CLOCK_H
