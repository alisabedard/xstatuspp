// Copyright 2016, Jeffrey E. Bedard
#ifndef XSTATUS_LOAD_H
#define XSTATUS_LOAD_H
#include "xdata.h"
namespace xstatus {
	namespace load {
		// Returns x offset for next item
		uint16_t draw(xcb_connection_t * xc,
			const uint16_t x) __attribute__((nonnull));
	}
}
#endif//!XSTATUS_LOAD_H
