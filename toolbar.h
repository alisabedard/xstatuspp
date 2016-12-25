// Copyright 2016, Jeffrey E. Bedard
#ifndef XSTATUS_TOOLBAR_H
#define XSTATUS_TOOLBAR_H
#include <stdbool.h>
#include <xcb/xcb.h>
namespace xstatus {
	namespace toolbar {
		/* Returns x offset after all buttons added.  */
		uint16_t initialize(xcb_connection_t * xc);
		bool handle_button_enter(const xcb_window_t event_window);
		bool handle_button_leave(const xcb_window_t event_window);
		// returns true if event was processed:
		bool handle_button_press(const xcb_window_t event_window);
		// returns true if event was processed:
		bool handle_expose(const xcb_window_t event_window);
	}
}
#endif//!XSTATUS_TOOLBAR_H
