// Copyright 2017, Jeffrey E. Bedard
#include "button.h"
extern "C" {
#include "libjb/log.h"
#include "libjb/xcb.h"
}
#include "config.h"
#include "util.h"
using namespace std;
xcb_gcontext_t xstatus::XSButton::button_gc = 0;
xcb_gcontext_t xstatus::XSButton::get_button_gc(void)
{
	if (button_gc)
		return button_gc;
	else {
		button_gc = xcb_generate_id(X);
		xstatus::create_gc(xc, button_gc, X, XSTATUS_BUTTON_FG,
			XSTATUS_BUTTON_BG, font);
		return button_gc;
	};
}
void xstatus::XSButton::draw(void)
{
	xcb_image_text_8(xc, label->size(), window, get_button_gc(),
		XSTATUS_CONST_PAD, font_size.height, label->c_str());
}
void xstatus::XSButton::invert(void)
{
	xcb_rectangle_t r = geometry;
	r.x = r.y = 0;
	xcb_poly_fill_rectangle(xc, window, X.get_invert_gc(), 1, &r);
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
	const pixel_t bg = jb_get_pixel(xc, X.colormap, XSTATUS_BUTTON_BG);
	uint32_t v[] = {bg, EM};
	create(X.main_window, this->geometry, BORDER, VM, v);
}
xstatus::XSButton::XSButton(XData & X, const Font & f,
	const int16_t x, char * label)
	: Window(X), X(X), font(f), x(x), font_size(f.get_size()),
	label(new string(label))
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
