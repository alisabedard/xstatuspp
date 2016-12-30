// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_WINDOW_H
#define XSTATUS_WINDOW_H
#include <xcb/xcb.h>
namespace xstatus {
	class XData;
	class Window {
		private:
			bool created = false;
		protected:
			xcb_connection_t * xc;
			xcb_window_t window;
			xcb_rectangle_t geometry;
		public:
			Window(xcb_connection_t * xc);
			~Window(void);
			void create(const xcb_window_t parent,
				const xcb_rectangle_t & geometry,
				const uint8_t border_width,
				const uint32_t value_mask,
				const void * value_list);
			operator xcb_window_t(void) const { return window; }
			// Keep this accessor for subclasses:
			xcb_window_t get_window(void) const { return window; }
			static xcb_window_t create_main_window(XData * X);
			void map(void);
			void unmap(void);
			void destroy(void);
	};
}
#endif//!XSTATUS_WINDOW_H
