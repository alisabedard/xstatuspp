// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_STATUS_FILE_H
#define XSTATUS_STATUS_FILE_H
#include <xcb/xcb.h>
#include "Font.h"
namespace xstatus {
	namespace status_file {
		// Returns offset for next widget
		unsigned short draw(xcb_connection_t * xc,
			const int x_offset, const char * filename,
			const Font & font);
	}
}
#endif//!XSTATUS_STATUS_FILE_H
