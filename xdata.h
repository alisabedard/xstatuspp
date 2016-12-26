// Copyright 2016, Jeffrey E. Bedard
#ifndef XS_XDATA_H
#define XS_XDATA_H
#include <xcb/xcb.h>
namespace xstatus {
	xcb_window_t get_window(xcb_connection_t *  xc);
	xcb_colormap_t get_colormap(xcb_connection_t * xc);
	xcb_gcontext_t get_button_gc(xcb_connection_t * xc);
	xcb_gcontext_t get_gc(xcb_connection_t * xc);
	xcb_gcontext_t get_invert_gc(xcb_connection_t * xc);
	xcb_screen_t * get_screen(xcb_connection_t * xc);
	class XData {
		protected:
			xcb_connection_t * xc;
			xcb_window_t win;
			xcb_gcontext_t gc;
			xcb_screen_t * scr;
		public:
			XData(xcb_connection_t * xc)
				: xc(xc), win(get_window(xc)), gc(get_gc(xc)),
				scr(get_screen(xc))
		{}
	};
}
#endif//!XS_XDATA_H
