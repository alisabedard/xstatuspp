// Copyright 2016, Jeffrey E. Bedard
#ifndef XSTATUS_FONT_H
#define XSTATUS_FONT_H
//#include "libjb/JBDim.h"
#include <stdbool.h>
#include <xcb/xcb.h>
struct JBDim;
namespace xstatus {
	xcb_font_t get_font(xcb_connection_t * xc);
	struct JBDim get_font_size(void);
	// returns true if successful
	bool open_font(xcb_connection_t * xc, const char * fn);
}
#endif//!XSTATUS_FONT_H
