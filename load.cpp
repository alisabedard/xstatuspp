// Copyright 2016, Jeffrey E. Bedard
#include "load.h"
extern "C" {
#include "libjb/JBDim.h"
}
#include <cstdio>
#include <cstdlib>
#include "Buffer.h"
#include "config.h"
#include "font.h"
namespace {
	__attribute__((nonnull))
		static uint8_t get_load(char *  buf, const uint8_t sz)
		{
			double l;
			getloadavg(&l, 1);
			return snprintf(buf, sz, "%.2f", l);
		}
}
// Returns x offset for next item
__attribute__((nonnull))
uint16_t xstatus::load::draw(xcb_connection_t * xc, const uint16_t x,
	const JBDim font_size)
{
	class LoadBuffer : public Buffer {
		public:
			LoadBuffer(void) : Buffer(6)
			{
				size = get_load(buffer, size);
			}
	};
	LoadBuffer b;
	XData X(xc);
	xcb_image_text_8(xc, b, X.main_window, X.get_gc(),
		x, font_size.height, b.buffer);
	return x + font_size.width * b + XSTATUS_CONST_PAD;
}
