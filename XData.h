// Copyright 2017, Jeffrey E. Bedard
#ifndef XS_XDATA_H
#define XS_XDATA_H
#include <xcb/xcb.h>
#include "Window.h"
namespace xstatus {
	class XData {
		private:
			typedef xcb_connection_t xc_t;
			static void init(xc_t * xc);
			static bool xdata_init_done;
			// put here to keep read-only
			static xcb_gcontext_t gc, invert_gc, button_gc;
		public:
			Window & main_window;
			static xc_t * xc;
			static xcb_screen_t * screen;
			static xcb_colormap_t colormap;
			XData(xc_t * xc);
			xcb_gcontext_t get_gc(void) const { return gc; }
			xcb_gcontext_t get_invert_gc(void) const
			{ return invert_gc; }
			// convenience conversion accessors:
			operator xc_t*() const { return xc; }
			operator xcb_screen_t *() const { return screen; }
			operator xcb_window_t() const { return main_window; }
	};
}
#endif//!XS_XDATA_H
