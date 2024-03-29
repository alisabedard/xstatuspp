// Copyright 2017, Alisa Bedard
#include "Button.h"
#include "config.h"
#include "libjb/xcb.h"
#include "libjb/cpp.h"
#include "util.h"
using namespace std;
short xstatus::Button::instances = 0;
xcb_gcontext_t xstatus::Button::button_gc = 0;
xcb_gcontext_t xstatus::Button::get_button_gc(void)
{
	if (button_gc)
		return button_gc;
	else {
		button_gc = xcb_generate_id(X);
		xstatus::create_gc(X, button_gc, X, XSTATUS_BUTTON_FG,
			XSTATUS_BUTTON_BG, font);
		return button_gc;
	};
}
void xstatus::Button::draw(void)
{
	xcb_image_text_8(X, label.size(), window, get_button_gc(),
		XSTATUS_CONST_PAD, font_size.height, label.c_str());
}
void xstatus::Button::invert(void)
{
	xcb_rectangle_t r = geometry;
	r.x = r.y = 0;
	xcb_poly_fill_rectangle(X, window, X.get_invert_gc(), 1, &r);
	xcb_flush(X);
}
void xstatus::Button::set_geometry(void)
{
	const unsigned short w = font_size.width * label.size()
		+ font_size.width;
	const unsigned short h = font_size.height
		+ (XSTATUS_CONST_PAD >> 1);
	geometry = {x, 0, w, h};
}
void xstatus::Button::create_window(void)
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
	const pixel_t bg = jb_get_pixel(X, X.colormap, XSTATUS_BUTTON_BG);
	uint32_t v[] = {bg, EM};
	create(X.main_window, this->geometry, BORDER, VM, v);
}
xstatus::Button::Button(XData & X, const Font & f,
	const short x, std::string & label)
	: Window(X), X(X), font(f), x(x), font_size(f.get_size()),
	label(label)
{
	JB_LOG_ADD(Button, instances);
	create_window();
	draw();
}
xstatus::Button::~Button(void)
{
	JB_LOG_DEL(Button, instances);
	if (cb_data)
		delete[] cb_data;
}
