// Copyright 2016, Jeffrey E. Bedard
#ifndef XSTATUS_STATUS_FILE_H
#define XSTATUS_STATUS_FILE_H
#include <xcb/xcb.h>
namespace xstatus {
	namespace status_file {
		// Returns offset for next widget
		uint16_t draw(xcb_connection_t * xc, const uint16_t x_offset,
			const char *  filename);
	}
}
#endif//!XSTATUS_STATUS_FILE_H
