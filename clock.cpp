// Copyright 2016, Jeffrey E. Bedard
#include "clock.h"
extern "C" {
#include "libjb/JBDim.h"
#include "libjb/log.h"
#include "libjb/xcb.h"
}
#include <string>
#include "config.h"
#include "font.h"
using namespace std;
namespace xstatus {
	class Buffer {
		public:
			char * buffer;
			Buffer(size_t sz)
			{
				buffer = new char [sz];
			}
			Buffer(const Buffer &obj) // copy
			{
				string s(obj.buffer);
				int i = s.size();
				buffer = new char [i];
				while (i >= 0) {
					--i;
					buffer[i] = obj.buffer[i];
				}
			}
			~Buffer(void)
			{
				delete buffer;
			}
	};
	class Time {
		protected:
			time_t current_time;
		public:
			Time()
			{
				current_time = time(NULL);
			}
	};
	class Clock : public Buffer, public Time {
		size_t size;
		public:
		Clock(size_t size)
			: Buffer(size), size(size)
		{}
		void format(void)
		{
			size = strftime(buffer, size,
				XSTATUS_TIME_FORMAT,
				localtime(&current_time));
		}
		size_t get_size(void) {return size;}
	};
	class Renderer {
		xcb_connection_t * xc;
		Clock * c;
		xcb_window_t win;
		xcb_gcontext_t gc;
		xcb_screen_t * scr;
		const struct JBDim font_size;
		public:
			Renderer(xcb_connection_t * xc, Clock * c)
				: xc(xc), c(c),
				win(get_window(xc)),
				gc(get_gc(xc)),
				scr(get_screen(xc)),
				font_size(get_font_size())
			{}
			int draw(void);
		};
	int Renderer::draw(void)
	{
		const size_t sz = c->get_size();
		int offset = scr->width_in_pixels - font_size.w * sz;
		xcb_image_text_8(xc, sz, win, gc, offset, font_size.h,
			c->buffer);
		return offset;
	}

	namespace clock {
		uint16_t draw(xcb_connection_t * xc)
		{
			Clock c(XSTATUS_TIME_BUFFER_SIZE);
			c.format();
			Renderer r(xc, &c);
			return r.draw();
		}
	}
}
