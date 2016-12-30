// Copyright 2016, Jeffrey E. Bedard
#include "Window.h"
extern "C" {
#include "libjb/xcb.h"
}
#include "config.h"
#include "XData.h"
using namespace xstatus;
namespace {
	int16_t get_y(const unsigned short screen_height)
	{
		return screen_height - XSTATUS_CONST_HEIGHT -
			XSTATUS_CONST_BORDER;
	}
	pixel_t get_bg(xcb_connection_t * xc,
		xcb_screen_t * s)
	{
		return jb_get_pixel(xc, s->default_colormap,
			XSTATUS_PANEL_BACKGROUND);
	}
	xcb_rectangle_t get_geometry(xcb_screen_t * s)
	{
		return (xcb_rectangle_t){0, get_y(s->height_in_pixels),
			s->width_in_pixels, XSTATUS_CONST_HEIGHT};
	}
}
Window::Window(xcb_connection_t * xc)
	: xc(xc), window(xcb_generate_id(xc)) {}
Window::~Window(void)
{
	destroy();
}
void Window::create(const xcb_window_t parent, const xcb_rectangle_t &
	geometry, const uint8_t border_width, const uint32_t value_mask, const
	void * value_list)
{
	enum { CFP = XCB_COPY_FROM_PARENT };
	const xcb_rectangle_t & g = geometry;
	xcb_create_window(xc, CFP, window, parent, g.x, g.y, g.width,
		g.height, border_width, CFP, CFP, value_mask, value_list);
	xcb_map_window(xc, window);
	created = true;
}
xcb_window_t Window::create_main_window(XData * X)
{
	enum {
		VM = XCB_CW_BACK_PIXEL | XCB_CW_OVERRIDE_REDIRECT
			| XCB_CW_EVENT_MASK, BRD = XSTATUS_CONST_BORDER,
		EM = XCB_EVENT_MASK_EXPOSURE, CFP = XCB_COPY_FROM_PARENT
	};
	Window & w = X->main_window;
	xcb_screen_t * s = X->screen;
	uint32_t v[] = {get_bg(*X, s), true, EM};
	w.create(s->root, get_geometry(s), BRD, VM, v);
	return w;
}
void Window::map(void)
{
	xcb_map_window(xc, window);
}
void Window::unmap(void)
{
	xcb_unmap_window(xc, window);
}
void Window::destroy(void)
{
	if (created) {
		xcb_destroy_window(xc, window);
		created = false;
	}
}
