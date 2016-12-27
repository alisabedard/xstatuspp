// Copyright 2016, Jeffrey E. Bedard
#ifndef XSTATUS_TOOLBAR_H
#define XSTATUS_TOOLBAR_H
#include <list>
#include <stdint.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include "button.h"
#include "xdata.h"
namespace xstatus {
	class Toolbar : public XData {
		private:
			std::list<XSButton *> buttons;
			unsigned int offset;
			bool do_cb(const xcb_window_t ewin, bool &
				keep_going);

			bool iterate_buttons_member(const xcb_window_t ewin,
				void (XSButton::*func)(void));
		public:
			Toolbar(xcb_connection_t * xc);
			unsigned int get_offset(void) { return offset; }
			bool focus(const xcb_window_t event_window);
			// returns true if event was processed:
			bool button(const xcb_window_t event_window,
				bool & keep_going);
			// returns true if event was processed:
			bool expose(const xcb_window_t event_window);
			void btn(char * label, char * cb_data,
				bool (*cb)(XSButton *));
			void btn(char * label, char * cmd);
	};
}
#endif//!XSTATUS_TOOLBAR_H
