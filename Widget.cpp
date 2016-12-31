// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#include "Widget.h"
using namespace xstatus;
Widget::Widget(xcb_connection_t * xc, Buffer & buffer, const Font & font)
	: Window(xc), XData(xc), font(font), buffer(buffer)
{
}
int Widget::get_next_offset(void) const
{
	return offset + width;
}
