// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_CLOCK_H
#define XSTATUS_CLOCK_H
#include "Font.h"
#include "XData.h"
namespace xstatus {
	namespace clock {
		unsigned short draw(xcb_connection_t * xc, const Font & f);
	}
}
#endif//!XSTATUS_CLOCK_H
