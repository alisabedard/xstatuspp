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
#include "Renderer.h"
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
	class ClockWidget : public Renderer {
		public:
			ClockWidget(xcb_connection_t * xc, Buffer & buffer,
				const Font & f)
				: Renderer(xc, buffer, f) {}
			int draw(void);
	};
	int ClockWidget::draw(void)
	{
		const unsigned int sz = buffer - 1;
		const JBDim f = font.get_size();
		int offset = screen->width_in_pixels - f.w * sz;
		xcb_image_text_8(xc, sz, main_window, get_gc(), offset,
			f.h, buffer);
		return offset;
	}
}
unsigned short clock::draw(xcb_connection_t * xc, const Font & f)
{
	Format c(XSTATUS_TIME_BUFFER_SIZE);
	ClockWidget r(xc, c, f);
	return r.draw();
}
