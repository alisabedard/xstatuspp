// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_LOAD_H
#define XSTATUS_LOAD_H
#include "BufferWidget.h"
namespace xstatus {
	class Load : public BufferWidget {
		public:
			Load(xcb_connection_t * xc, const Font & font,
				const int x);
	};
}
#endif//!XSTATUS_LOAD_H
