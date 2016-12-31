// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_LOAD_H
#define XSTATUS_LOAD_H
#include "BufferWidget.h"
#include "Widget.h"
namespace xstatus {
	class LoadBuffer : public Buffer {
		public:
			LoadBuffer(void);
	};
	class LoadWidget : public Widget {
		public:
			LoadWidget(xcb_connection_t * xc, Buffer & buffer,
				const Font & font, int offset);
			void draw(void);
	};
	class Load : public BufferWidget {
		public:
			Load(xcb_connection_t * xc, const Font & font,
				const int x);
			~Load(void);
	};
}
#endif//!XSTATUS_LOAD_H
