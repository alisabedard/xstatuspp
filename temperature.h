// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_TEMPERATURE_H
#define XSTATUS_TEMPERATURE_H
#include "BufferWidget.h"
namespace xstatus {
	class Temperature : public BufferWidget {
		public:
			Temperature(xcb_connection_t * xc, const Font & font,
				const int x);
	};
}
#endif//!XSTATUS_TEMPERATURE_H
