// Copyright 2016, Jeffrey E. Bedard
#include "clock.h"
#include "libjb/JBDim.h"
#include "libjb/log.h"
#include "libjb/xcb.h"
#include <string>
#include "Buffer.h"
#include "config.h"
#include "Renderer.h"
#include "Widget.h"
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
				size = strftime(buffer, get_max_size(),
					XSTATUS_TIME_FORMAT,
					localtime(&current_time));
			}
	};
	class ClockWidget : public Widget {
		private:
			unsigned int screen_width;
		public:
			ClockWidget(xcb_connection_t * xc, Buffer & buffer,
				const Font & f)
				: Widget(xc, buffer, f),
				screen_width(screen->width_in_pixels) {}
			int get_next_offset(void) const {return offset;}
			void draw(void);
	};
	void ClockWidget::draw(void)
	{
		const size_t sz = buffer - 1;
		const JBDim f = font.get_size();
		width = f.w * sz;
		offset = screen_width - width;
		xcb_image_text_8(XData::xc, sz, main_window, get_gc(),
			offset, f.h, buffer);
	}
}
unsigned short clock::draw(xcb_connection_t * xc, const Font & f)
{
	Format c(XSTATUS_TIME_BUFFER_SIZE);
	ClockWidget r(xc, c, f);
	r.draw();
	return r.get_next_offset();
}
