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
#include "Renderer.h"
#include "xdata.h"
using namespace xstatus;
namespace {
	class Time {
		protected:
			time_t current_time;
		public:
			Time() { current_time = time(NULL); }
	};
	class Format : public Buffer, public Time {
		public:
			Format(size_t size)
				: Buffer(size)
			{
				size = strftime(buffer, size,
					XSTATUS_TIME_FORMAT,
					localtime(&current_time));
			}
	};
	class Widget : public Renderer {
		private:
			Buffer * c;
			const struct JBDim font_size;
		public:
			Widget(xcb_connection_t * xc, Buffer * c,
				const Font & f)
				: Renderer(xc), c(c),
				font_size(f.get_size())
			{}
			int draw(void);
	};
	int Widget::draw(void)
	{
		const size_t sz = c->get_size();
		int offset = scr->width_in_pixels - font_size.w * sz;
		xcb_image_text_8(xc, sz, win, gc, offset, font_size.h,
			c->buffer);
		return offset;
	}
}
uint16_t clock::draw(xcb_connection_t * xc, const Font & f)
{
	Format c(XSTATUS_TIME_BUFFER_SIZE);
	Widget r(xc, &c, f);
	return r.draw();
}
