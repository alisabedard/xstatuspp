// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_WINDOW_H
#define XSTATUS_WINDOW_H
#include <xcb/xcb.h>
namespace xstatus {
	namespace window {
		__attribute__((nonnull)) void create(xcb_connection_t * xc);
	}
}
#endif//!XSTATUS_WINDOW_H
