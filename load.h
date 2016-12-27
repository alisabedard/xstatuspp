// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_LOAD_H
#define XSTATUS_LOAD_H
#include "libjb/JBDim.h"
#include "xdata.h"
namespace xstatus {
	namespace load {
		// Returns x offset for next item
		uint16_t draw(xcb_connection_t * xc,
			const uint16_t x,
			const JBDim font_size) __attribute__((nonnull));
	}
}
#endif//!XSTATUS_LOAD_H
