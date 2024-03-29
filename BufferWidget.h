// Copyright 2017, Alisa Bedard <alisabedard@gmail.com>
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
			~BufferWidget(void)
			{
				delete buffer;
				delete widget;
			}
			operator int(void) const
			{ return widget->get_next_offset(); }
	};
}
#endif//!XSPP_BUFFER_WIDGET_H

