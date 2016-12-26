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
		static uint8_t format(char *  buf, const uint8_t sz)
		{
			double l;
			getloadavg(&l, 1);
			return snprintf(buf, sz, "%.2f", l);
		}
}
// Returns x offset for next item
__attribute__((nonnull))
uint16_t xstatus::load::draw(xcb_connection_t * xc, const uint16_t x)
{
	const struct JBDim f = get_font_size();
	class LoadBuffer : public Buffer {
		public:
			LoadBuffer(void) : Buffer(6)
			{
				size = format(buffer, size);
			}
	};
	LoadBuffer b;
	xcb_image_text_8(xc, b.get_size(), xstatus::get_window(xc),
		xstatus::get_gc(xc), x, f.h, b.buffer);
	return x + f.w * b.get_size() + XSTATUS_CONST_PAD;
}
