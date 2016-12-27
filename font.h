// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_FONT_H
#define XSTATUS_FONT_H
#include <stdbool.h>
#include <xcb/xcb.h>
#include "libjb/JBDim.h"
namespace xstatus {
	class Font {
		private:
			xcb_connection_t * xc;
			xcb_font_t fid;
			JBDim sz = {{0}, {0}};
		public:
			Font(xcb_connection_t * xc)
				: xc(xc), fid(xcb_generate_id(xc))
			{}
			// Returns true if successful.
			bool open(const char * font_name);
			xcb_font_t get_font(void) const { return fid; }
			JBDim get_size(void) const { return sz; }
	};
}
#endif//!XSTATUS_FONT_H
