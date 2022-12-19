// Copyright 2017, Alisa Bedard
#ifndef XSTATUS_FONT_H
#define XSTATUS_FONT_H
#include <stdbool.h>
#include <xcb/xcb.h>
#include "Size.h"
namespace xstatus {
	typedef Size<uint8_t> FontSize;
	class Font {
		private:
			xcb_connection_t * xc;
			xcb_font_t fid;
			FontSize sz;
		public:
			Font(xcb_connection_t * xc)
				: xc(xc), fid(xcb_generate_id(xc))
			{}
			// Returns true if successful.
			bool open(const char * font_name);
			xcb_font_t get_font(void) const { return fid; }
			FontSize get_size(void) const { return sz; }
	};
}
#endif//!XSTATUS_FONT_H
