// Copyright 2017, Jeffrey E. Bedard
#include "temperature.h"
extern "C" {
#include "libjb/JBDim.h"
}
#include <iostream>
#include "config.h"
#include "Buffer.h"
#include "Renderer.h"
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
		private:
			void format(void);
		public:
			TemperatureBuffer(void) : Buffer(4) { format(); }
	};
	void TemperatureBuffer::format(void)
	{
		const uint8_t temp = get_temp();
		size = temp ? snprintf(buffer, size, "%dC",
			temp) : 0;
	}
	class TemperatureRenderer : public Renderer {
		private:
			JBDim f;
			Buffer * b;
			int x;
		public:
			TemperatureRenderer(xcb_connection_t * xc, Buffer * b,
				int x, const JBDim & font_size)
				: Renderer(xc), f(font_size), b(b), x(x) {}
			int draw(void);
	};
	int TemperatureRenderer::draw(void)
	{
		const unsigned int sz = *b;
		xcb_image_text_8(xc, sz, main_window,
			get_gc(), x, f.h, b->buffer);
		return x + f.w * sz;
	}
}
// Returns x offset for next item
unsigned short temperature::draw(xcb_connection_t * xc,
	const unsigned short offset, const JBDim & font_size)
{
	TemperatureBuffer b;
	TemperatureRenderer r(xc, &b, offset + XSTATUS_CONST_PAD, font_size);
	return r.draw();
}
