// Copyright 2017, Jeffrey E. Bedard
#include "Temperature.h"
#include <iostream>
#include "config.h"
#include "util.h"
using namespace xstatus;
namespace {
	int get_temp_raw(void)
	{
		return system_value(XSTATUS_SYSFILE_TEMPERATURE);
	}
	int get_temp(void)
	{
		// may only fail once:
		static bool get_temp_failed;
		if (get_temp_failed)
			return -1;
		// type must hold at least 100000, signed
		int temp = get_temp_raw();
		if (temp < 0) {
			std::cerr << "Could not read " <<
				XSTATUS_SYSFILE_TEMPERATURE << '\n';
			get_temp_failed = true;
			return -1;
		}
		return temp / 1000;
	}
	class TemperatureBuffer : public Buffer {
		public:
			TemperatureBuffer(void);
	};
	TemperatureBuffer::TemperatureBuffer(void) : Buffer(4)
	{
		const uint8_t temp = get_temp();
		set_size(temp ? snprintf(buffer, get_max_size(), "%dC", temp)
			: 0);
	}
	class TemperatureWidget : public Widget {
		public:
			TemperatureWidget(xcb_connection_t * xc,
				Buffer & buffer, const Font & font,
				int offset = 0)
				: Widget(xc, buffer, font)
			{
				this->offset = offset;
			}
			void draw(void);
	};
	void TemperatureWidget::draw(void)
	{
		const unsigned int sz = buffer;
		const FontSize f = font.get_size();
		xcb_image_text_8(XData::xc, sz, main_window,
			get_gc(), offset, f.height, buffer);
		this->width = f.width * sz;
	}
}
Temperature::Temperature(xcb_connection_t * xc, const Font & font, const int x)
{
	buffer = new TemperatureBuffer();
	widget = new TemperatureWidget(xc, *buffer, font, x +
		XSTATUS_CONST_PAD);
	widget->draw();
}
