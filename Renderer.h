// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#ifndef XSTATUS_RENDERER_H
#define XSTATUS_RENDERER_H
#include "xdata.h"
namespace xstatus {
	class Renderer : public XData {
		public:
			Renderer(xcb_connection_t * xc) : XData(xc) {}
			virtual int draw(void) = 0;
	};
}
#endif//!XSTATUS_RENDERER_H

