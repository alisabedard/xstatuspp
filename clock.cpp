// Copyright 2016, Jeffrey E. Bedard
#include "clock.h"
extern "C" {
#include "libjb/JBDim.h"
#include "libjb/log.h"
#include "libjb/xcb.h"
}
#include <string>
#include "Buffer.h"
#include "config.h"
#include "font.h"
using namespace xstatus;
namespace {
	class Time {
		protected:
			time_t current_time;
		public:
			Time() { current_time = time(NULL); }
	};
	class Clock : public Buffer, public Time {
		public:
			Clock(size_t size)
				: Buffer(size)
			{}
			void format(void)
			{
				size = strftime(buffer, size,
					XSTATUS_TIME_FORMAT,
					localtime(&current_time));
			}
	};
	class Renderer {
		xcb_connection_t * xc;
		Buffer * c;
		xcb_window_t win;
		xcb_gcontext_t gc;
		xcb_screen_t * scr;
		const struct JBDim font_size;
		public:
		Renderer(xcb_connection_t * xc, Buffer * c);
		int draw(void);
	};
	Renderer::Renderer(xcb_connection_t * xc, Buffer * c)
		: xc(xc), c(c),
		win(get_window(xc)),
		gc(get_gc(xc)),
		scr(get_screen(xc)),
		font_size(get_font_size())
	{}
	int Renderer::draw(void)
	{
		const size_t sz = c->get_size();
		int offset = scr->width_in_pixels - font_size.w * sz;
		xcb_image_text_8(xc, sz, win, gc, offset, font_size.h,
			c->buffer);
		return offset;
	}
}
uint16_t clock::draw(xcb_connection_t * xc)
{
	Clock c(XSTATUS_TIME_BUFFER_SIZE);
	c.format();
	Renderer r(xc, &c);
	return r.draw();
}
