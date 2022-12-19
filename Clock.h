// Copyright 2017, Alisa Bedard
#ifndef XSTATUS_CLOCK_H
#define XSTATUS_CLOCK_H
#include "BufferWidget.h"
namespace xstatus {
	class Clock : public BufferWidget {
		public:
			Clock(xcb_connection_t * xc, const Font & f);
	};
}
#endif//!XSTATUS_CLOCK_H
