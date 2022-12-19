// Copyright 2017, Alisa Bedard
#include "Temperature.h"
#include <iostream>
#include "config.h"
#include "util.h"
using namespace xstatus;
namespace {
	class TemperatureValue {
		private:
			int value;
			static bool has_error;
			void poll(void)
			{
				static const char sysfile[] =
					XSTATUS_SYSFILE_TEMPERATURE;
				value = system_value(sysfile);
				if (value < 0) {
					std::cerr << "Could not read "
						<< sysfile << '\n';
					has_error = true;
				}
			}
		public:
			TemperatureValue()
			{
				if (!has_error)
					poll();
			}
			operator float() const
			{
				float v = value;
				return v / 1000;
			}
			operator int() const
			{
				return value / 1000;
			}
			explicit operator bool() const { return ! has_error; }
	};
	bool TemperatureValue::has_error = false;
	class TemperatureBuffer : public Buffer {
		public:
			TemperatureBuffer(void);
	};
	TemperatureBuffer::TemperatureBuffer(void) : Buffer(5)
	{
		TemperatureValue t;
		set_size(t ? snprintf(buffer, get_max_size(), "%' '3dC",
			(int)t) : 0);
	}
	class FloatTemperatureBuffer : public Buffer {
		public:
			FloatTemperatureBuffer(void);
	};
	FloatTemperatureBuffer::FloatTemperatureBuffer(void) : Buffer(7)
	{
		TemperatureValue t;
		set_size(t ? snprintf(buffer, get_max_size(), "%.1fC",
			(float)t) : 0);
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
	widget = new TemperatureWidget(xc, *buffer, font, x);
	widget->draw();
}
