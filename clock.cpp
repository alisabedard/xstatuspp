// Copyright 2016, Jeffrey E. Bedard
#include "clock.h"
extern "C" {
#include "libjb/JBDim.h"
#include "libjb/log.h"
#include "libjb/xcb.h"
}
#include "config.h"
#include "font.h"
namespace xstatus {
	static uint16_t get_offset(xcb_connection_t *  xc,
		const uint16_t font_width, const size_t sz)
	{
		return xstatus::get_screen(xc)->width_in_pixels
			- font_width * sz;
	}
	static uint8_t format(char * buf, uint8_t sz)
	{
		time_t t = time(NULL);
		 return strftime(buf, sz, XSTATUS_TIME_FORMAT, localtime(&t));
	}
	static uint16_t draw_for_font_size(xcb_connection_t *  xc,
		const struct JBDim font_size, char * buf, const uint8_t sz)
	{
		uint16_t offset = get_offset(xc, font_size.w, sz);
		xcb_image_text_8(xc, sz, xstatus::get_window(xc),
			xstatus::get_gc(xc), offset, font_size.h, buf);
		return offset;
	}
	namespace clock {
		uint16_t draw(xcb_connection_t * xc)
		{
			uint8_t sz = XSTATUS_TIME_BUFFER_SIZE;
			char buf[sz];
			sz = format(buf, sz);
			LOG("size: %d, string: %s\n", sz, buf);
			return draw_for_font_size(xc,
				xstatus::get_font_size(), buf, sz);
		}
	}
}
