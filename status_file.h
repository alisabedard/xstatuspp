// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_STATUSBAR_H
#define XSTATUS_STATUSBAR_H
#include "BufferWidget.h"
namespace xstatus {
	class Statusbar : public BufferWidget {
		public:
			Statusbar(xcb_connection_t * xc, const Font & font,
				const int x, const char * filename);
	};
}
#endif//!XSTATUS_STATUSBAR_H
