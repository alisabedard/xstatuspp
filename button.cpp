// Copyright 2016, Jeffrey E. Bedard
#include "button.h"
extern "C" {
#include "libjb/JBDim.h"
#include "libjb/xcb.h"
}
#include <cstdlib>
#include <cstring>
#include "config.h"
#include "font.h"
#include "window.h"
#include "xdata.h"
using namespace std;
void XSButton::draw(void)
{
	xcb_image_text_8(xc, strlen(label), window,
		xstatus::get_button_gc(xc), XSTATUS_CONST_PAD,
		xstatus::get_font_size().height, label);
}
void XSButton::invert(void)
{
	xcb_rectangle_t r = geometry;
	r.x = r.y = 0;
	xcb_poly_fill_rectangle(xc, window,
		xstatus::get_invert_gc(xc), 1, &r);
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
void XSButton::set_geometry(void)
{
	const struct JBDim f = xstatus::get_font_size();
	xcb_rectangle_t r = {this->x, 0, get_width(f.w, this->label),
		get_height(f.h)};
	this->geometry = r;
}
void XSButton::create_window(void)
{
	class Values {
		private:
			enum {
				VM = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK,
				EM = XCB_EVENT_MASK_EXPOSURE
					| XCB_EVENT_MASK_BUTTON_PRESS
					| XCB_EVENT_MASK_ENTER_WINDOW
					| XCB_EVENT_MASK_LEAVE_WINDOW,
			};
			uint32_t v[2];
		public:
			Values(xcb_connection_t * xc)
			{

				v[0] = get_bg(xc);
				v[1] = EM;
			}
			uint32_t get_mask(void)
			{
				return VM;
			}
			const uint32_t * get_values(void) {return v;}
	};
	set_geometry();
	enum {
		CFP = XCB_COPY_FROM_PARENT,
		BORDER = 0
	};
	const xcb_rectangle_t g = this->geometry;
	Values v(xc);
	xcb_create_window(this->xc, CFP, this->window,
		xstatus::get_window(this->xc),
		g.x, g.y, g.width, g.height, BORDER,
		CFP, CFP, v.get_mask(), v.get_values());
	xcb_map_window(this->xc, this->window);
}
XSButton::XSButton(xcb_connection_t *  xc, const int16_t x, char * label)
	: next(NULL), xc(xc), label(strdup(label)), x(x)
{
	window = xcb_generate_id(xc);
	create_window();
	draw();
}
XSButton::~XSButton(void)
{
	xcb_destroy_window(xc, window);
	free(label);
}
