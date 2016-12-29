// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_LOAD_H
#define XSTATUS_LOAD_H
#include <xcb/xcb.h>
#include "font.h"
namespace xstatus {
	namespace load {
		// Returns x offset for next item
		int draw(xcb_connection_t * xc, const Font & f, const int x);
	}
}
#endif//!XSTATUS_LOAD_H
