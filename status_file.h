// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_STATUS_FILE_H
#define XSTATUS_STATUS_FILE_H
#include <xcb/xcb.h>
#include "libjb/JBDim.h"
namespace xstatus {
	namespace status_file {
		// Returns offset for next widget
		unsigned short draw(xcb_connection_t * xc,
			const unsigned short x_offset,
			const char * filename, const JBDim font_size);
	}
}
#endif//!XSTATUS_STATUS_FILE_H
