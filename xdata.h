// Copyright 2017, Jeffrey E. Bedard
#ifndef XS_XDATA_H
#define XS_XDATA_H
#include <xcb/xcb.h>
#include "window.h"
namespace xstatus {
	class XData {
		private:
			typedef xcb_connection_t xc_t;
			typedef xcb_gcontext_t gc_t;
			static void init(xc_t * xc);
			static bool xdata_init_done;
			// put here to keep read-only
			static gc_t gc, invert_gc, button_gc;
		public:
			Window & main_window;
			static xc_t * xc;
			static xcb_screen_t * screen;
			static xcb_colormap_t colormap;
			XData(xc_t * xc);
			operator xc_t*() const { return xc; }
			gc_t get_gc(void) const { return gc; }
			gc_t get_button_gc(void) const { return button_gc; }
			gc_t get_invert_gc(void) const { return invert_gc; }
	};
}
#endif//!XS_XDATA_H
