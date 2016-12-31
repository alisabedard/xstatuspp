// Copyright 2016, Jeffrey E. Bedard
#include "load.h"
extern "C" {
#include "libjb/JBDim.h"
}
#include <cstdio>
#include "Buffer.h"
#include "config.h"
#include "Font.h"
#include "Renderer.h"
#include "Widget.h"
using namespace xstatus;
namespace {
	static uint8_t get_load(char *  buf, const uint8_t sz)
	{
		double l;
		getloadavg(&l, 1);
		return snprintf(buf, sz, "%.2f", l);
	}
	class LoadBuffer : public Buffer {
		public:
			LoadBuffer(void)
				: Buffer(6)
			{ set_size(get_load(buffer, get_max_size())); }
	};
	class LoadWidget : public Widget{
		public:
			LoadWidget(xcb_connection_t * xc, Buffer & buffer,
				const Font & font, int offset)
				: Widget(xc, buffer, font)
			{this->offset = offset;}
			void draw(void);
	};
	void LoadWidget::draw(void)
	{
		const JBDim fs = font;
		xcb_image_text_8(*this, buffer, main_window, get_gc(),
			offset, fs.height, buffer);
		width = fs.width * buffer + XSTATUS_CONST_PAD;
	}
}
// Returns x offset for next item
int load::draw(xcb_connection_t * xc, const Font & f, const int x)
{
	LoadBuffer b;
	LoadWidget r(xc, b, f, x);
	r.draw();
	return r.get_next_offset();
}
