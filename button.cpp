// Copyright 2016, Jeffrey E. Bedard
extern "C" {
#include "button.h"
#include "config.h"
#include "font.h"
#include "libjb/xcb.h"
#include "xdata.h"
#include "window.h"
#include <stdlib.h>
#include <string.h>
}
static void draw(XSButton *  b)
{
	xcb_connection_t * xc = b->xc;
	xcb_image_text_8(xc, strlen(b->label), b->window,
		xstatus::get_button_gc(xc), XSTATUS_CONST_PAD,
		xstatus::get_font_size().height, b->label);
}
static void invert(XSButton *  b)
{
	xcb_connection_t * xc = b->xc;
	const xcb_window_t w = b->window;
	const xcb_gcontext_t gc = xstatus::get_invert_gc(xc);
	const struct JBDim f = xstatus::get_font_size();
	xcb_rectangle_t r = {0, 0, b->width, f.h};
	xcb_poly_fill_rectangle(xc, w, gc, 1, &r);
	xcb_flush(xc);
}
static pixel_t get_bg(xcb_connection_t *  xc)
{
	static pixel_t p; // cache the result
	return p ? p : (p = jb_get_pixel(xc, xstatus::get_colormap(xc),
		XSTATUS_BUTTON_BG));
}
static inline uint16_t get_width(uint8_t fw, const char * label)
{
	return fw * strlen(label) + fw;
}
static inline uint8_t get_height(uint8_t fh)
{
	return fh + (XSTATUS_CONST_PAD >> 1);
}
static xcb_rectangle_t get_geometry(XSButton * b)
{
	const struct JBDim f = xstatus::get_font_size();
	xcb_rectangle_t r = {b->x, 0, get_width(f.w, b->label),
		get_height(f.h)};
	b->width = r.width;
	return r;
}
static void create_window(XSButton * b)
{
	const xcb_window_t w = b->window;
	xcb_connection_t *  xc = b->xc;
	{ // g scope, vm scope, em scope
		enum {
			VM = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK,
			EM = XCB_EVENT_MASK_EXPOSURE
				| XCB_EVENT_MASK_BUTTON_PRESS
				| XCB_EVENT_MASK_ENTER_WINDOW
				| XCB_EVENT_MASK_LEAVE_WINDOW,
			CFP = XCB_COPY_FROM_PARENT,
			BORDER = 0
		};
		const xcb_rectangle_t g = get_geometry(b);
		uint32_t v[] = {get_bg(xc), EM};
		xcb_create_window(xc, CFP, w, xstatus::get_window(xc),
			g.x, g.y, g.width, g.height, BORDER,
			CFP, CFP, VM, v);
	}
	xcb_map_window(xc, w);
}
XSButton * xstatus_create_button(xcb_connection_t *  xc,
	const int16_t x, char * label)
{
	XSButton * b = new XSButton;
	b->window = xcb_generate_id(b->xc = xc);
	b->label = label;
	b->draw = draw;
	b->enter = invert;
	b->leave = invert;
	b->x = x;
	b->next = NULL;
	create_window(b);
	draw(b);
	return b;
}
