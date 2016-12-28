// Copyright 2017, Jeffrey E. Bedard
#include "temperature.h"
extern "C" {
#include "libjb/JBDim.h"
}
#include <cstdio>
#include "config.h"
#include "Buffer.h"
#include "Renderer.h"
#include "util.h"
using namespace xstatus;
namespace {
	int32_t get_temp_raw(void)
	{
		return system_value(XSTATUS_SYSFILE_TEMPERATURE);
	}
	uint8_t get_temp(void)
	{
		// may only fail once:
		static bool get_temp_failed;
		if (get_temp_failed)
			return 0; // 0 indicates unsupported
		// type must hold at least 100000, signed
		int32_t temp = get_temp_raw();
		if (temp == -1) { // could not open system file
			get_temp_failed = true;
			return 0;
		}
		return temp / 1000;
	}
	class TempBuf : public Buffer {
		private:
			void format(void)
			{
				const uint8_t temp = get_temp();
				size = temp ? snprintf(buffer, size, "%dC",
					temp) : 0;
			}
		public:
			TempBuf(void) : Buffer(4) {
				format();
			}
	};
	class TempRenderer : public Renderer {
		private:
			JBDim f;
			Buffer * b;
			int x;
		public:
			TempRenderer(xcb_connection_t * xc, Buffer * b, int x,
				const JBDim font_size)
				: Renderer(xc), f(font_size), b(b), x(x) {}
			int draw(void)
			{
				const size_t sz = b->get_size();
				xcb_image_text_8(xc, sz, win, gc, x, f.h,
					b->buffer);
				return x + f.w * sz;
			}
	};
}
// Returns x offset for next item
uint16_t temperature::draw(xcb_connection_t * xc, const uint16_t offset,
	const JBDim font_size)
{
	TempBuf b;
	TempRenderer r(xc, &b, offset + XSTATUS_CONST_PAD, font_size);
	return r.draw();
}
