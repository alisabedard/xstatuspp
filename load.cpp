// Copyright 2016, Jeffrey E. Bedard
#include "load.h"
extern "C" {
#include "libjb/JBDim.h"
}
#include <cstdio>
#include <cstdlib>
#include "config.h"
#include "font.h"
__attribute__((nonnull))
static uint8_t format(char *  buf, const uint8_t sz)
{
	double l;
	getloadavg(&l, 1);
	return snprintf(buf, sz, "%.2f", l);
}
// Returns x offset for next item
__attribute__((nonnull))
uint16_t xstatus_draw_load(xcb_connection_t * xc, const uint16_t x)
{
	const struct JBDim f = xstatus::get_font_size();
	uint8_t sz=6;
	{ // buf scope
		char buf[sz];
		sz = format(buf, sz);
		xcb_image_text_8(xc, sz, xstatus::get_window(xc),
			xstatus::get_gc(xc), x, f.h, buf);
	}
	return x + f.w * sz + XSTATUS_CONST_PAD;
}
