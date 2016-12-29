// Copyright 2017, Jeffrey E. Bedard
#include "button.h"
extern "C" {
#include "libjb/JBDim.h"
#include "libjb/log.h"
#include "libjb/xcb.h"
}
#include <string>
#include "config.h"
#include "font.h"
using namespace std;
void xstatus::XSButton::draw(void)
{
	xcb_image_text_8(xc, label->size(), window, XData(xc).button_gc,
		XSTATUS_CONST_PAD, font_size.height, label->c_str());
}
void xstatus::XSButton::invert(void)
{
	xcb_rectangle_t r = geometry;
	r.x = r.y = 0;
	xcb_poly_fill_rectangle(xc, window, XData(xc).invert_gc, 1, &r);
	xcb_flush(xc);
}
void xstatus::XSButton::set_geometry(void)
{
	JBDim & f = font_size;
	const uint16_t w = f.w * label->size() + f.w;
	const uint16_t h = f.h + (XSTATUS_CONST_PAD >> 1);
	geometry = {x, 0, w, h};
}
void xstatus::XSButton::create_window(void)
{
	enum {
		CFP = XCB_COPY_FROM_PARENT,
		BORDER = 0,
		VM = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK,
		EM = XCB_EVENT_MASK_EXPOSURE
			| XCB_EVENT_MASK_BUTTON_PRESS
			| XCB_EVENT_MASK_ENTER_WINDOW
			| XCB_EVENT_MASK_LEAVE_WINDOW
	};
	set_geometry();
	XData X(xc);
	const pixel_t bg = jb_get_pixel(xc, X.colormap,
		XSTATUS_BUTTON_BG);
	uint32_t v[] = {bg, EM};
	create(X.main_window, this->geometry, BORDER, VM, v);
}
xstatus::XSButton::XSButton(xcb_connection_t * xc, const Font & f,
	const int16_t x, char * label)
	: Window(xc), x(x), font_size(f.get_size()), label(new string(label))
{
	LOG("XSButton constructor");
	create_window();
	draw();
}
xstatus::XSButton::~XSButton(void)
{
	LOG("XSButton destructor");
	delete label;
}
