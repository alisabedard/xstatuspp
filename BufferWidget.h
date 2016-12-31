// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#ifndef XSPP_BUFFER_WIDGET_H
#define XSPP_BUFFER_WIDGET_H
#include "Widget.h"
namespace xstatus {
	class Buffer;
	class BufferWidget {
		protected:
			Buffer * buffer;
			Widget * widget;
		public:
			operator int(void) const
			{ return widget->get_next_offset(); }
	};
}
#endif//!XSPP_BUFFER_WIDGET_H

