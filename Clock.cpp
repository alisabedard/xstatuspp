// Copyright 2016, Jeffrey E. Bedard
#include "Clock.h"
#include "config.h"
#include "Widget.h"
using namespace xstatus;
class Time {
	protected:
		time_t current_time;
	public:
		Time() { current_time = time(NULL); }
};
class Format : public Buffer, public Time {
	public:
		Format(void)
			: Buffer(XSTATUS_TIME_BUFFER_SIZE)
		{
			set_size(strftime(buffer, get_max_size(),
				XSTATUS_TIME_FORMAT,
				localtime(&current_time)));
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
	const size_t sz = buffer;
	const JBDim f = font.get_size();
	width = f.w * sz;
	offset = screen_width - width;
	xcb_image_text_8(XData::xc, sz, main_window, get_gc(),
		offset, f.h, buffer);
}
Clock::Clock(xcb_connection_t * xc, const Font & f)
{
	buffer = new Format();
	widget = new ClockWidget(xc, *buffer, f);
	widget->draw();
}
