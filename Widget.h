// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#ifndef XSPP_WIDGET_H
#define XSPP_WIDGET_H
#include "Buffer.h"
#include "Renderer.h"
#include "Window.h"
namespace xstatus {
	class Widget : public Window, public Renderer {
		protected:
			int offset = 0;
			int width = 0;
		public:
			Widget(xcb_connection_t * xc, Buffer & buffer,
				const Font & font)
				: Renderer(xc, buffer, font),
				Window(xc) {}
			int get_next_offset(void) const
			{
				return offset + width;
			}
	};
}
#endif//!XSPP_WIDGET_H
