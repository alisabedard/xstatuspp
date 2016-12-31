// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#ifndef XSPP_WIDGET_H
#define XSPP_WIDGET_H
#include "Buffer.h"
#include "Font.h"
#include "Window.h"
#include "XData.h"
namespace xstatus {
	class WidgetInterface {
		public:
			virtual int get_next_offset(void) const = 0;
			virtual void draw(void) = 0;
	};
	class Widget : public Window, public XData, public WidgetInterface {
		protected:
			Buffer & buffer;
			const Font & font;
			int offset = 0;
			int width = 0;
		public:
			Widget(xcb_connection_t * xc, Buffer & buffer,
				const Font & font);
			virtual int get_next_offset(void) const;
			virtual void draw(void) {};
	};
}
#endif//!XSPP_WIDGET_H
