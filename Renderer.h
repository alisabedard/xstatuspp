// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#ifndef XSTATUS_RENDERER_H
#define XSTATUS_RENDERER_H
#include "font.h"
#include "xdata.h"
namespace xstatus {
	class Renderer : public XData {
		protected:
			Buffer & buffer;
			const Font & font;
		public:
			Renderer(xcb_connection_t * xc, Buffer & buffer, const
				Font & font)
				: XData(xc), buffer(buffer), font(font) {}
			virtual int draw(void) = 0;
	};
}
#endif//!XSTATUS_RENDERER_H

