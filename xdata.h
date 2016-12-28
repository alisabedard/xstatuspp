// Copyright 2017, Jeffrey E. Bedard
#ifndef XS_XDATA_H
#define XS_XDATA_H
#include <xcb/xcb.h>
#include "window.h"
namespace xstatus {
	class XData {
		private:
			static void init(xcb_connection_t * xc);
			static bool xdata_init_done;
		public:
			Window & main_window;
			static xcb_connection_t * xc;
			static xcb_screen_t * screen;
			static xcb_gcontext_t gc, invert_gc, button_gc;
			static xcb_colormap_t colormap;
			XData(xcb_connection_t * xc);
	};
}
#endif//!XS_XDATA_H
