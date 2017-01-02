// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_UTIL_H
#define XSTATUS_UTIL_H
#include <xcb/xcb.h>
#include "Font.h"
namespace xstatus {
	void create_gc(xcb_connection_t * xc, const xcb_gcontext_t gc,
		const xcb_window_t win, const char * fg, const char * bg,
		const Font & f);
	// returns -1 on error
	int system_value(const char * filename);
	template <typename T>
		inline T min(T a, T b) { return a < b ? a : b; }
	template <typename T>
		inline T max(T a, T b) { return a > b ? a : b; }
}
#endif//XSTATUS_UTIL_H
