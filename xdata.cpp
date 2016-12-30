// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#include "xdata.h"
extern "C" {
#include "libjb/xcb.h"
}
#include "Window.h"
using namespace xstatus;
namespace {
	xstatus::Window & get_main_window_class(xcb_connection_t * xc)
	{
		static xstatus::Window w(xc);
		return w;
	}
}
xcb_connection_t * XData::xc = nullptr;
xcb_screen_t * XData::screen = nullptr;
typedef xcb_gcontext_t gc;
gc XData::gc, XData::invert_gc;
xcb_colormap_t XData::colormap;
bool XData::xdata_init_done = false;
void XData::init(xcb_connection_t * xc)
{
	XData::xc = xc;
	XData::gc = xcb_generate_id(xc);
	XData::invert_gc = xcb_generate_id(xc);
	XData::screen = jb_get_xcb_screen(xc);
	XData::colormap = XData::screen->default_colormap;
	XData::xdata_init_done = true;
}
XData::XData(xcb_connection_t * xc)
	: main_window(get_main_window_class(xc))
{
	if (!xdata_init_done)
		XData::init(xc);
}
