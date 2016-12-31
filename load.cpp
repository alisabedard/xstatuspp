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
}
LoadBuffer::LoadBuffer(void) : Buffer(6)
{
	set_size(get_load(buffer, get_max_size()));
}
void LoadWidget::draw(void)
{
	const JBDim fs = font;
	xcb_image_text_8(*this, buffer, main_window, get_gc(),
		offset, fs.height, buffer);
	width = fs.width * buffer + XSTATUS_CONST_PAD;
}
LoadWidget::LoadWidget(xcb_connection_t * xc, Buffer & buffer, const Font &
	font, int offset) : Widget(xc, buffer, font)
{
	this->offset = offset;
}
Load::Load(xcb_connection_t * xc, const Font & font, const int x)
{
	buffer = new LoadBuffer();
	widget = new LoadWidget(xc, *buffer, font, x);
	widget->draw();
}
Load::~Load(void)
{
	delete buffer;
	delete widget;
}
