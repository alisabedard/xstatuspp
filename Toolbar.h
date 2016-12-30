// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_TOOLBAR_H
#define XSTATUS_TOOLBAR_H
#include <list>
#include "Button.h"
namespace xstatus {
	class Toolbar : public XData {
		private:
			static int instances;
			std::list<Button *> buttons;
			unsigned int offset;
			Font * font;
			bool do_cb(const xcb_window_t ewin, bool &
				keep_going);
			bool iterate_buttons_member(const xcb_window_t ewin,
				void (Button::*func)(void));
		public:
			Toolbar(xcb_connection_t * xc, Font * f);
			~Toolbar(void);
			unsigned int get_offset(void) { return offset; }
			bool focus(const xcb_window_t event_window);
			// returns true if event was processed:
			bool button(const xcb_window_t event_window,
				bool & keep_going);
			// returns true if event was processed:
			bool expose(const xcb_window_t event_window);
			void btn(const char label[], const char cb_data[],
				bool (*cb)(Button *));
			void btn(const char label[], const char cmd[]);
	};
}
#endif//!XSTATUS_TOOLBAR_H
